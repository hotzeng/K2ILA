# 07/03/2019
# Author: Yu Zeng
# only applicable to pure-reg operations 

import re
import os
import logging
from util.tree import BTree

def set_root(root, expression):
    if root == None:
        root = BTree(name=expression)
    else:
        root.set_name(expression)
    return root


def parse_expr(expr, root=None):

    m = re.search(r'^\s*(\w+)MInt\((.+)\)', expr)
    # if this is an expr
    if m != None:
        op = m.group(1)
        if op == 'extract':
            print('extract!')
        params = list(m.group(2))
        # instantiate the tree
        root = set_root(root, op)
        #if root == None:
        #    root = BTree(name=op)
        #else:
        #    root.set_name(op)

        assert root != None
        # replace , with |
        parenthesesNo = 0
        for i in range(len(params)):
            if params[i] == '(':
                parenthesesNo = parenthesesNo + 1
            elif params[i] == ')':
                parenthesesNo = parenthesesNo - 1
            elif params[i] == ',':
                if parenthesesNo == 0:
                    params[i] = '|'

        params = ''.join(params)
        children = re.split(r'\|', params)
        # parse children
        root.set_children_no(len(children))
        for i in range(len(children)):
            root.children[i] = parse_expr(children[i], root.children[i])

    # if this is a reg
    elif re.search(r'^\s+getParentValue', expr):
        m = re.search(r'^\s+getParentValue\((R\d+), RSMap\)', expr)
        if root == None:
            root = BTree(name=m.group(1))
        else:
            root.set_name(m.group(1))

    # if this is a digital number
    elif re.fullmatch(r'\s*\d+', expr):
        if root == None:
            root = BTree(name=expr)
        else:
            root.set_name(expr)

    # if this is a machine integer
    elif re.fullmatch(r'\s*mi\((\d+), (\d+)\)', expr):
        m = re.search(r'\s*mi\((\d+), (\d+)\)', expr)
        width = m.group(1)
        value = m.group(2)
        root = set_root(root, 'bv('+value+', '+width+')')

    #TODO: More 'elif' to be added
    return root


def write_expr(root):

    # using depth-first search to construct the expression
    if repr(root) == 'extract':
        assert len(root.children) == 3
        # FIXME: 63 or 31?
        return repr(root.children[0]) + '(' + str(63-int(repr(root.children[1]))) + ', ' + str(63-int(repr(root.children[2]))+1) + ')'

    elif repr(root) == 'neg':
        assert len(root.children) == 1
        return '~'+write_expr(root.children[0])

    elif repr(root) == 'and':
        assert len(root.children) == 2
        return write_expr(root.children[0])+' & '+write_expr(root.children[1])
    
    elif repr(root) == 'eq':
        assert len(root.children) == 2
        return write_expr(root.children[0])+" == "+write_expr(root.children[1])

    elif re.fullmatch(r'\s*R\d+', repr(root)):
        return repr(root)

    elif re.fullmatch(r'\s*bv\(\d+, \d+\)', repr(root)):
        return repr(root)
    else:
        logging.error('Not a supported expression:'+repr(root))
    #TODO: More 'elif' to be added


def translate(expr):
    tree = parse_expr(expr)
    return write_expr(tree)

def main():

    # read part
    # some states:
    # 0: not start
    # 1: in module
    # 2: in <k>
    # 3: in <regstate>
    # 4: out of <regstate>, finished
    phase = 0
    instName = None

    # read in all the files in ../x86_k
    readPath = '../x86_k'
    writePath = '../x86_ila'
    for fileName in os.listdir(readPath):
        fRead = open(readPath+'/'+fileName, "r")
        m = re.search(r'^(.+)\.k$', fileName)
        fWriteName = m.group(1)+'.cc'
        fWrite = open(writePath+'/'+fWriteName, "w")
        fReadLines = fRead.readlines()
        for line in fReadLines:
            if phase == 0:
                exist = re.search("module", line)
                if exist:
                    phase = 1
                    m = re.search("module (\S+)", line)
                    instName = m.group(1)
                    fWrite.write("auto instr = model.NewInstr("+instName+")\n")                

            # if in module
            if phase == 1:
                exist = re.search("<k>", line)
                if exist:
                    phase = 2

            # if in <k>
            if phase == 2:
                exist = re.search("<regstate>", line)
                if exist:
                    phase = 3

            # if in <regstate>
            if phase == 3:
                exist = re.search(r'</regstate>', line)
                if exist:
                    phase = 4
                    continue
                p = re.compile(r'(\S+) \|-> (.+)')
                res = p.search(line)
                if res == None:
                    continue
                reg = res.group(1)
                update = res.group(2)

                # parse reg
                if reg[0] == '"':
                    regPrint = reg[1] + reg[2]
                elif reg[0:13] == 'convToRegKeys':
                    regPrint = reg[14:16]

                # parse update
                if update == '(undefMInt)':
                    continue
                # if update is a machine integer
                elif update[0:2] == 'mi':
                    m = re.search(r'mi\((\d+), (\d+)\)', update)
                    if m == None:
                        logging.error('Not a valid machine integer!!')
                    bitWidth = m.group(1)
                    value = m.group(2)
                    fWrite.write("instr.SetUpdate("+regPrint+", bv("+value+", "+bitWidth+"))\n")
                # if update is an expression
                elif re.search(r'^\w+MInt', update):
                    tree = BTree(name=None)
                    tree = parse_expr(update, tree)
                    fWrite.write("instr.SetUpdate("+regPrint+", ")
                    toWrite = write_expr(tree)
                    fWrite.write(toWrite+')\n')
        
                # if update is if statement
                elif re.search(r'^\s*\(#ifMInt', update):
                    m = re.search(r'^\s*\(#ifMInt (.+) #then (.+) #else (.+) #fi\)', update)
                    if m == None:
                        logging.error('If statement is not matched!!')
                    ifExpr = m.group(1)
                    thenExpr = m.group(2)
                    elseExpr = m.group(3)
                    fWrite.write("instr.SetUpdate("+regPrint+", ")
                    toWrite = "Ite( "+translate(ifExpr)+', '+translate(thenExpr)+', '+translate(elseExpr)+'))\n'
                    fWrite.write(toWrite)

                    #while m = re.search(r'^\s*(\w+)MInt\( (\w+)MInt\((.*)\)|getParentValue\((.*)\)|(mi.*)(, )', update):

            if phase == 4:
                fWrite.write('RECORD_INST("'+instName+'");\n')
                fWrite.close()
                fRead.close()
                break


if __name__ == "__main__":
    main()
