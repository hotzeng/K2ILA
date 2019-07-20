# 07/03/2019
# Author: Yu Zeng
# The translation script

import sys
import re
import os
import logging
from util.tree import BTree
from collections import defaultdict

# debug enabler
PARSE_DEBUG = False
WRITE_DEBUG = False

def to_imme(expr):
# convert bv, BvConst to int type
    if re.search(r'bv', expr):
        m = re.search(r'^\s*bv\((\d+)\)', expr)
        return m.group(1)
    elif re.search(r'BvConst', expr):
        m = re.search(r'^\s*BvConst\((\d+),\s*(\d+)\)', expr)
        return m.group(1) 
    else:
        logging.error('Cannot convert to int!')

def is_flag(expr):
    if expr == 'CF' or \
            expr == 'PF' or \
            expr == 'AF' or \
            expr == 'ZF' or \
            expr == 'SF' or \
            expr == 'OF':
                return True
    else:
        return False

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


def pick_top_comma(params):
    params = list(params)
    parenthesesNo = 0
    for i in range(len(params)):
        if params[i] == '(':
            parenthesesNo += 1
        elif params[i] == ')':
            parenthesesNo -= 1
        elif params[i] == ',':
            if parenthesesNo == 0:
                params[i] = '|'

    return ''.join(params)


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
    assert bracketNo == 0, "Wrong de-bracket, expr:" + expr
    return ''.join(exprList)


# Attention: *Bool expressions should have higher priority over *MInt
def parse_expr(expr, root=None, isEqual=0):

    if PARSE_DEBUG:
        print(expr)

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

    elif re.search(r' ==bool ', expr):
        m = re.search(r'(.+) ==bool (.+)', expr)
        root = set_root(root, '==Bool')
        root.set_children_no(2)
        root.children[0] = parse_expr(m.group(1), root.children[0])
        root.children[1] = parse_expr(m.group(2), root.children[1])

    elif re.search(r'^\s*(\()?#ifMInt', expr):
        m = re.search(r'^\s*(\()?#ifMInt (.+) #then (.+) #else (.+) #fi(\))?', expr)
        ifExpr = de_bracket(m.group(2))
        thenExpr = de_bracket(m.group(3))
        elseExpr = de_bracket(m.group(4))
        root = set_root(root, 'if')
        root.set_children_no(3)
        root.children[0] = parse_expr(ifExpr,   root.children[0])
        root.children[1] = parse_expr(thenExpr, root.children[1])
        root.children[2] = parse_expr(elseExpr, root.children[2])

    # if this is an expr
    elif re.search(r'^\s*(\w+)MInt\((.+)\)', expr):
        m = re.search(r'^\s*(\w+)MInt\((.+)\)', expr)
        op = m.group(1)
        params = m.group(2)
        isEqual = 0
        if op == 'eq':
            isEqual = 1
        # instantiate the tree
        root = set_root(root, op)

        # replace ',' with '|' to extract children 
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        # parse children
        root.set_children_no(len(children))
        for i in range(len(children)):
            root.children[i] = parse_expr(children[i], root.children[i], isEqual)

    elif re.search(r'^\s*div_remainder_\w+', expr):
        m = re.search(r'^\s*div_remainder_\w+\((.+)\)$', expr)
        params = m.group(1)
        root = set_root(root, 'urem')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    elif re.search(r'^\s*div_quotient_\w+', expr):
        m = re.search(r'^\s*div_quotient_\w+\((.+)\)$', expr)
        params = m.group(1)        
        root = set_root(root, 'div')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    elif re.search(r'^\s*handleImmediateWithSignExtend', expr):
        m = re.search(r'^\s*handleImmediateWithSignExtend\((.+)\)', expr)
        params = m.group(1)
        root = set_root(root, 'sext')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 3, 'Wrong number of children'
        root.set_children_no(3)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])
        root.children[2] = parse_expr(children[2], root.children[2])

    elif re.search(r'^\s*ror', expr):
        m = re.search(r'^\s*ror\((.+)\)', expr)
        params = m.group(1)
        root = set_root(root, 'ror')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    # if this is a reg
    elif re.search(r'^\s*getParentValue', expr):
        m = re.search(r'^\s*getParentValue\(%?(\S+), RSMap\)', expr)
        root = set_root(root, m.group(1))

    # if this is a flag
    elif re.search(r'^\s*getFlag', expr):
        m = re.search(r'^\s*getFlag\("(\w+)", RSMap\)', expr)
        root = set_root(root, 'flag_'+m.group(1))

    # if this is a digital number
    elif re.fullmatch(r'\s*\d+', expr):
        root = set_root(root, repr(expr))

    elif re.fullmatch(r'\s*Imm32\s*', expr):
        root = set_root(root, repr(expr))

    # if this is a machine integer
    elif re.search(r'^\s*mi\((\d+),\s*(\d+)\)', expr):
        m = re.search(r'\s*mi\((\d+),\s*(\d+)\)', expr)
        width = m.group(1)
        value = m.group(2)
        if isEqual == 0:
            root = set_root(root, 'bv('+value+')')
        else:
            root = set_root(root, 'BvConst('+value+', '+width+')')

    else:
        logging.error('Not supported keyword: '+repr(expr))
        return None
    #TODO: More 'elif' to be added
    return root


def write_expr(root):

    if WRITE_DEBUG:
        print(root)

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
        return '~ (' + write_expr(root.children[0]) + ')'

    elif repr(root) == 'and':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') & (' + write_expr(root.children[1]) + ')'
    
    elif repr(root) == 'eq':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') == (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'add':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') + (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'mul':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') * (' + write_expr(root.children[1]) + ')'        

    elif repr(root) == 'div':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') / (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'urem':
        assert len(root.children) == 2
        return 'URem(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'or':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') | (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'xor':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') ^ (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'uge':
        assert len(root.children) == 2
        return '!Ult(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[0]) + ')'

    # TODO: merge the *Bool and *MInt operators??
    elif repr(root) == 'notBool':
        assert len(root.children) == 1
        return '~ (' + write_expr(root.children[0]) + ')'

    elif repr(root) == 'xorBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') ^ (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'andBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') & (' + write_expr(root.children[1]) + ')'

    elif repr(root) == '==Bool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') == (' + write_expr(root.children[1]) + ')'

    elif re.fullmatch(r'\s*R\d+', repr(root)):
        return repr(root)

    elif re.fullmatch(r'\s*bv\(\d+\)', repr(root)):
        return repr(root)

    elif re.fullmatch(r'\s*BvConst\(\d+, \d+\)\s*', repr(root)):
        return repr(root)

    elif re.fullmatch(r'flag_\w+', repr(root)):
        m = re.fullmatch(r'flag_(\w+)', repr(root))
        return m.group(1)

    elif re.fullmatch(r'Imm32', repr(root)):
        return repr(root)

    elif re.fullmatch(r'if', repr(root)):
        toWrite = "Ite("+write_expr(root.children[0])+', '+write_expr(root.children[1])+', '+write_expr(root.children[2])+')'
        return toWrite

    elif re.fullmatch(r'sext', repr(root)):
        toWrite = 'SExt(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[2]) + ', ' + ')'
        return toWrite

    elif re.fullmatch(r'ror', repr(root)):
        toWrite = 'RRotate(' + write_expr(root.children[0]) + ', ' + to_imme(write_expr(root.children[1])) + ')'
        return toWrite
        #toWrite = 'Concat(' + 'Extract(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + '-1, ' + '0), ' + 'Extract(' + write_expr(root.children[0]) + ', ' +  + write_expr(root.children[1]) +'))'

    else:
        logging.error('Not a supported expression: '+repr(root))
    #TODO: More 'elif' to be added


def translate(expr):
    tree = parse_expr(expr)
    if tree == None:
        return ''
    return write_expr(tree)


def process_require(readPath, fileName):
    fRead = open(readPath+'/'+fileName, "r")
    fWrite = open(readPath+'/'+fileName+'_new', "w")
    fReadLines = fRead.readlines()
    regs = []
    updates = defaultdict(list)
    conditions = []
    for line in fReadLines:
        if re.search(r'\|->', line):
            m = re.search(r'(\S+) \|-> (.+)', line)
            reg = m.group(1)
            update = m.group(2)
            if !(reg in updates):
                regs.append(reg)
            updates[reg].append(update)
        elif re.search(r'requires', line):
            m = re.search(r'^\s*requires (.+)$', line)
            conditions.append(m.group(1))


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
            if re.search("module", line):
                phase = 1
                fWrite.write("auto instr = model.NewInstr(\""+instName+"\");\n")                

        # if in module
        if phase == 1:
            if re.search("<k>", line):
                phase = 2

        # if in <k>
        if phase == 2:
            if re.search("<regstate>", line):
                phase = 3

        # if in <regstate>
        if phase == 3:
            if re.search(r'endmodule', line):
                phase = 4
                continue
            if re.search(r'<k>', line):
                phase = 2
                continue
            p = re.compile(r'(\S+) \|-> (.+)')
            res = p.search(line)
            if res == None:
                continue
            reg = res.group(1)
            update = res.group(2)

            # parse reg
            if re.search(r'^"(\w+)"$', reg):
                m = re.search(r'^"(\w+)"$', reg)
                regPrint = m.group(1)
                if is_flag(regPrint) == False:
                    isReg = 1
            elif reg[0:13] == 'convToRegKeys':
                m = re.search(r'convToRegKeys\((\w+)\)', reg)
                regPrint = m.group(1)
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
                if tree == None:
                    return
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
            return True

if __name__ == "__main__":
    process_file(sys.argv[1], sys.argv[2], sys.argv[3])
