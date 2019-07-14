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


def toInt(expr):
    m = re.search('\d+', expr)
    return m.group(0)


def de_bracket(expr):
# if there is a opening bracket at the beginning, remove the closing bracket at the end
    m = re.search(r'^\s*\(', expr)
    if m != None:
        m2 = re.search(r'^\s*\((.*)\)\s*$', expr)
        return m2.group(1)
    else:
        return expr


def de_nest_bool(expr):
# find the top-level bool expr
    exprList = list(expr)
    bracketNo = 0
    for i in range(len(exprList)):
        if exprList[i] == '(':
            bracketNo += 1
        elif exprList[i] == ')':
            bracketNo -= 1
        elif len(exprList) - i >= 4 and \
             ''.join(exprList[i:i+4]) == 'Bool' and bracketNo == 0:
                exprList[i] = 'b'
    if bracketNo != 0:
        print("Wrong de-bracket!")
    assert bracketNo == 0
    return ''.join(exprList)


# Attention: *Bool expressions should have higher priority over *MInt
def parse_expr(expr, root=None, isEqual=0):

    expr = de_bracket(expr)
    expr = de_nest_bool(expr)

    #""" *bool is the top-level expr, *Bool is not """
    if re.search(r'^\s*notbool ', expr):
        m = re.search(r'^\s*notbool (.+)', expr)
        root = set_root(root, 'notBool')
        root.set_children_no(1)
        root.children[0] = parse_expr(m.group(1), root.children[0])

    elif re.search(r' andbool ', expr):
        m = re.search(r'(.+) andbool (.+)', expr)
        root = set_root(root, 'andBool')
        root.set_children_no(2)
        root.children[0] = parse_expr(m.group(1), root.children[0])
        root.children[1] = parse_expr(m.group(2), root.children[1])
 

    elif re.search(r' xorbool ', expr):
        m = re.search(r'(.+) xorbool (.+)', expr)
        root = set_root(root, 'xorBool')
        root.set_children_no(2)
        root.children[0] = parse_expr(m.group(1), root.children[0])
        root.children[1] = parse_expr(m.group(2), root.children[1])

    # if this is an expr
    elif re.search(r'^\s*(\w+)MInt\((.+)\)', expr):
        m = re.search(r'^\s*(\w+)MInt\((.+)\)', expr)
        op = m.group(1)
        params = list(m.group(2))
        isEqual = 0
        if op == 'eq':
            isEqual = 1
        # instantiate the tree
        root = set_root(root, op)

        assert root != None
        # replace ',' with '|' to extract children 
        parenthesesNo = 0
        for i in range(len(params)):
            if params[i] == '(':
                parenthesesNo += 1
            elif params[i] == ')':
                parenthesesNo -= 1
            elif params[i] == ',':
                if parenthesesNo == 0:
                    params[i] = '|'

        params = ''.join(params)
        children = re.split(r'\|', params)
        # parse children
        root.set_children_no(len(children))
        for i in range(len(children)):
            root.children[i] = parse_expr(children[i], root.children[i], isEqual)

    # if this is a reg
    elif re.search(r'^\s+getParentValue', expr):
        m = re.search(r'^\s+getParentValue\((R\d+), RSMap\)', expr)
        if root == None:
            root = BTree(name=m.group(1))
        else:
            root.set_name(m.group(1))

    # if this is a digital number
    elif re.fullmatch(r'\s*\d+', expr):
        root = set_root(root, repr(expr))

    # if this is a machine integer
    elif re.search(r'^\s*mi\((\d+), (\d+)\)', expr):
        m = re.search(r'\s*mi\((\d+), (\d+)\)', expr)
        width = m.group(1)
        value = m.group(2)
        if isEqual == 0:
            root = set_root(root, 'bv('+value+')')
        else:
            root = set_root(root, 'BvConst('+value+', '+width+')')

    else:
        logging.error('Not supported keyword: '+repr(expr))
    #TODO: More 'elif' to be added
    return root


def write_expr(root):

    # using depth-first search to construct the expression
    if repr(root) == 'extract':
        assert len(root.children) == 3
        # FIXME: 63 or 31?
        return repr(root.children[0]) + '(' + str(63-int(toInt(repr(root.children[1])))) + ', ' + str(63-int(toInt(repr(root.children[2])))+1) + ')'

    elif repr(root) == 'concatenate':
        assert len(root.children) == 2
        return 'Concat(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'neg':
        assert len(root.children) == 1
        return '~' + write_expr(root.children[0])

    elif repr(root) == 'and':
        assert len(root.children) == 2
        return write_expr(root.children[0]) + ' & ' + write_expr(root.children[1])
    
    elif repr(root) == 'eq':
        assert len(root.children) == 2
        return write_expr(root.children[0]) + " == " + write_expr(root.children[1])

    # TODO: merge the *Bool and *MInt operators??
    elif repr(root) == 'notBool':
        assert len(root.children) == 1
        return '~ (' + write_expr(root.children[0]) + ')'

    elif repr(root) == 'xorBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') ^ (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'andBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ' & ' + write_expr(root.children[1]) + ')'

    elif re.fullmatch(r'\s*R\d+', repr(root)):
        return repr(root)

    elif re.fullmatch(r'\s*bv\(\d+\)', repr(root)):
        return repr(root)

    elif re.fullmatch(r'\s*BvConst\(\d+, \d+\)\s*', repr(root)):
        return repr(root)

    else:
        logging.error('Not a supported expression: '+repr(root))
    #TODO: More 'elif' to be added


def translate(expr):
    tree = parse_expr(expr)
    return write_expr(tree)


def process_file(readPath, writePath, fileName):
    fRead = open(readPath+'/'+fileName, "r")
    m = re.search(r'^(.+)\.k$', fileName)
    fWriteName = m.group(1)+'.cc'
    instName = m.group(1)
    fWrite = open(writePath+'/'+fWriteName, "w")
    fReadLines = fRead.readlines()
    phase = 0    
    updateRIP = 0
    for line in fReadLines:
        isReg = 0
        if phase == 0:
            exist = re.search("module", line)
            if exist:
                phase = 1
                fWrite.write("auto instr = model.NewInstr(\""+instName+"\");\n")                

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
                isReg = 1

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
                if isReg == 0:
                    fWrite.write("instr.SetUpdate("+regPrint+", bv("+value+"));\n")
                else:
                    fWrite.write("UPDATE_R("+regPrint+", bv("+value+"));\n")
            # if update is an expression
            elif re.search(r'^\w+MInt', update):
                tree = BTree(name=None)
                tree = parse_expr(update, tree)
                if isReg == 0:
                    fWrite.write("instr.SetUpdate("+regPrint+", ")
                else:
                    fWrite.write("UPDATE_R("+regPrint+", ")
                toWrite = write_expr(tree)
                fWrite.write(toWrite+');\n')
    
            # if update is if statement
            elif re.search(r'^\s*\(#ifMInt', update):
                m = re.search(r'^\s*\(#ifMInt (.+) #then (.+) #else (.+) #fi\)', update)
                if m == None:
                    logging.error('If statement is not matched!!')
                ifExpr = de_bracket(m.group(1))
                thenExpr = de_bracket(m.group(2))
                elseExpr = de_bracket(m.group(3))
                if isReg == 0:                    
                    fWrite.write("instr.SetUpdate("+regPrint+", ")
                else:
                    fWrite.write("UPDATE_R("+regPrint+", ")
                toWrite = "Ite( "+translate(ifExpr)+', '+translate(thenExpr)+', '+translate(elseExpr)+'));\n'
                fWrite.write(toWrite)

                #while m = re.search(r'^\s*(\w+)MInt\( (\w+)MInt\((.*)\)|getParentValue\((.*)\)|(mi.*)(, )', update):

        if phase == 4:
            if updateRIP == 0:
                fWrite.write("instr.SetUpdate(rip, nxt_rip);\n")
            fWrite.write('RECORD_INST("'+instName+'");\n')
            fWrite.close()
            fRead.close()
            break


def main():

    # read part
    # some states:
    # 0: not start
    # 1: in module
    # 2: in <k>
    # 3: in <regstate>
    # 4: out of <regstate>, finished
    instName = None

    # read in all the files in ../x86_k
    # FIXME: Change the readPath and writePath to operate on different files!
    readPath = '../x86_k/semantics/registerInstructions'
    writePath = '../x86_ila/semantics/registerInstructions'
    fileName = None
    # FIXME: specify the file name if you want to run on only one file
    fileName = 'andb_r8_rh.k'
    if fileName != None:
        process_file(readPath, writePath, fileName)
    else:
        for fileName in os.listdir(readPath):
            process_file(readPath, writePath, fileName)


if __name__ == "__main__":
    main()
