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

# helper functions
def to_imme(expr):
# convert bv, BvConst to int type
    if re.search(r'^\s*bv', expr):
        m = re.search(r'^\s*bv\((\d+)\)', expr)
        return m.group(1)
    elif re.search(r'^\s*BvConst', expr):
        m = re.search(r'^\s*BvConst\((\d+),\s*(\d+)\)', expr)
        return m.group(1) 
    else:
        return expr


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


def to_int(expr):
    m = re.search('\d+', expr)
    return int(m.group(0))


# if the opening ( is for 'ifMInt', do NOT remove it
def de_bracket(expr):
    # first, check if the opening '(' corresponds to the closing ')'
    expr = list(expr)
    parenthesesNo = 0
    cleanParenthTimes = 0
    noIsZero = True
    noIsZeroLast = True
    for i in range(len(expr)):
        noIsZeroLast = noIsZero
        if expr[i] == '(':
            parenthesesNo += 1
        elif expr[i] == ')':
            parenthesesNo -= 1
        if parenthesesNo != 0:
            noIsZero = False
        else:
            noIsZero = True
        if noIsZero == True and noIsZeroLast == False:
            cleanParenthTimes += 1

    expr = ''.join(expr)
    assert cleanParenthTimes >= 0
    if cleanParenthTimes > 1:
        return expr

    m = re.search(r'^\s*\((.*)\)\s*$', expr)
    findIf = re.search(r'^\s*\(#ifMInt', expr)
    if m != None and findIf == None:
        return m.group(1)
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
    # if begins with ifMInt, then just return
    if re.search(r'^\s*(\()?[iI]fMInt', expr):
        return expr
    exprList = list(expr)
    bracketNo = 0
    for i in range(len(exprList)):
        if exprList[i] == '(':
            bracketNo += 1
        elif exprList[i] == ')':
            bracketNo -= 1
        elif len(exprList) - i >= 4 and \
             ''.join(exprList[i:i+4]) == 'Bool' and \
             bracketNo == 0 and ''.join(exprList[i-5:i]) != 'undef':
                exprList[i] = 'b'
    if bracketNo != 0:
        print('wrong de-bracket')
    assert bracketNo == 0, "Wrong de-bracket, expr:" + expr
    return ''.join(exprList)


def de_nest_if(expr):
# find the top-level if-then-else, convert to capital case
    m = re.search(r'^\s*(\(#ifMInt.+)', expr)
    if m == None:
        return expr
    expr = m.group(1)
    pendingIf = 0
    exprList = list(expr)
    exprList[2] = 'I'
    for i in range(len(exprList)):
        if ''.join(exprList[i:i+6]) == 'ifMInt':
            pendingIf += 1
        elif ''.join(exprList[i:i+2]) == 'fi':
            if pendingIf > 0:
                pendingIf -= 1
            else:
                exprList[i] = 'F'
        elif ''.join(exprList[i:i+4]) == 'then' and pendingIf == 0:
            exprList[i] = 'T'
        elif ''.join(exprList[i:i+4]) == 'else' and pendingIf == 0:
            exprList[i] = 'E'            

    expr = ''.join(exprList)
    return expr


# Main functions:
# Attention: *Bool expressions should have higher priority over *MInt
def parse_expr(expr, root=None, isEqual=0):

    if PARSE_DEBUG:
        print(expr)

    expr = de_bracket(expr)
    expr = de_nest_bool(expr)
    expr = de_nest_if(expr)

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

    elif re.search(r' orbool ', expr):
        m = re.search(r'(.+) orbool (.+)', expr)
        root = set_root(root, 'orBool')
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

    elif re.search(r' =/=bool ', expr):
        m = re.search(r'(.+) =/=bool (.+)', expr)
        root = set_root(root, '=/=Bool')
        root.set_children_no(2)
        root.children[0] = parse_expr(m.group(1), root.children[0])
        root.children[1] = parse_expr(m.group(2), root.children[1])

    elif re.search(r'^\s*(\()?#IfMInt', expr):
        m = re.search(r'^\s*(\()?#IfMInt (.+) #Then (.+) #Else (.+) #Fi(\))?', expr)
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

    elif re.search(r'^\s*i?div_remainder_\w+', expr):
        m = re.search(r'^\s*i?div_remainder_\w+\((.+)\)$', expr)
        params = m.group(1)
        root = set_root(root, 'urem')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    elif re.search(r'^\s*i?div_quotient_\w+', expr):
        m = re.search(r'^\s*i?div_quotient_\w+\((.+)\)$', expr)
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

    elif re.search(r'^\s*rol', expr):
        m = re.search(r'^\s*rol\((.+)\)', expr)
        params = m.group(1)
        root = set_root(root, 'rol')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    elif re.search(r'^\s*sameRegisters', expr):
        m = re.search(r'^\s*sameRegisters\((.+)\)', expr)
        params = m.group(1)
        root = set_root(root, 'sameRegisters')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    # if this is a reg
    elif re.search(r'^\s*getParentValue', expr):
        m = re.search(r'^\s*getParentValue\((%?\S+), RSMap\)', expr)
        root = set_root(root, m.group(1))

    # if this is a reg
    elif re.search(r'^\s*getRegisterValue', expr):
        m = re.search(r'^\s*getRegisterValue\((%?\S+), RSMap\)', expr)
        root = set_root(root, m.group(1))

    elif re.search(r'^\s*R\d+', expr):
        m = re.search(r'^\s*(R\d+)', expr)
        root = set_root(root, m.group(1))

    elif re.search(r'^\s*(%\w+)', expr):
        m = re.search(r'^\s*%(\w+)', expr)
        root = set_root(root, m.group(1))

    # if this is a flag
    elif re.search(r'^\s*getFlag', expr):
        m = re.search(r'^\s*getFlag\("(\w+)", RSMap\)', expr)
        root = set_root(root, 'flag_'+m.group(1))

    # if this is a digital number
    elif re.fullmatch(r'\s*\d+', expr):
        m = re.search(r'\s*(\d+)', expr)
        root = set_root(root, m.group(1))

    elif re.fullmatch(r'\s*Imm32\s*', expr):
        root = set_root(root, repr(expr))

    elif re.fullmatch(r'\s*false\s*', expr):
        root = set_root(root, 'false')

    elif re.fullmatch(r'\s*true\s*', expr):
        root = set_root(root, 'true')

    # if this is a machine integer
    elif re.search(r'^\s*mi\((.+)\)', expr):
        m = re.search(r'\s*mi\((.+)\)', expr)
        #width = m.group(1)
        #value = m.group(2)
        params = m.group(1)
        if isEqual == 0:
            root = set_root(root, 'mi_ne')
        else:
            root = set_root(root, 'mi_eq')
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        root.set_children_no(2)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])

    elif re.search(r'scanReverse|scanForward', expr):
        m = re.search(r'\s*(scanReverse|scanForward)\((.+)\)', expr)
        root = set_root(root, m.group(1))
        params = m.group(2)
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 3, 'Wrong number of children'
        root.set_children_no(3)
        root.children[0] = parse_expr(children[0], root.children[0])
        root.children[1] = parse_expr(children[1], root.children[1])
        root.children[2] = parse_expr(children[2], root.children[2])

    elif re.search(r'undefBool', expr):
        root = set_root(root, 'undefBool')

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
        return 'Extract(' + write_expr(root.children[0]) + ', ' + str(63-int(to_int(write_expr(root.children[1])))) + ', ' + str(63-int(to_int(write_expr(root.children[2])))+1) + ')'

    elif repr(root) == 'concatenate':
        assert len(root.children) == 2
        return 'Concat(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'scanReverse':
        assert len(root.children) == 3
        return 'scanReverse(' + write_expr(root.children[0]) + ', ' + str(to_int(write_expr(root.children[2])) - to_int(write_expr(root.children[1])) - 1) + ', ' + write_expr(root.children[2]) + ')'

    elif repr(root) == 'scanForward':
        assert len(root.children) == 3
        return 'scanForward(' + write_expr(root.children[0]) + ', ' + str(to_int(write_expr(root.children[2])) - to_int(write_expr(root.children[1])) - 1) + ', ' + write_expr(root.children[2]) + ')'

    elif repr(root) == 'mi_ne':
        assert len(root.children) == 2
        return 'bv(' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'mi_eq':
        assert len(root.children) == 2
        return 'BvConst(' + write_expr(root.children[1]) + ', ' + write_expr(root.children[0]) + ')'

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

    elif repr(root) == 'sub':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') - (' + write_expr(root.children[1]) + ')'

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
        return '!Ult(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'ult':
        assert len(root.children) == 2
        return 'Ult(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'shiftLeft':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') << (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'aShiftRight':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') >> (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'lshr':
        assert len(root.children) == 2
        return 'Lshr(' + write_expr(root.children[0]) + ', ' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'uvalue':
        assert len(root.children) == 1
        return 'ZExt(' + write_expr(root.children[0]) + ', ' + str(cal_width(root)) + ')'

    elif repr(root) == 'svalue':
        assert len(root.children) == 1
        return 'SExt(' + write_expr(root.children[0]) + ', ' + str(cal_width(root)) + ')'

    # TODO: merge the *Bool and *MInt operators??
    elif repr(root) == 'notBool':
        assert len(root.children) == 1
        expr =  write_expr(root.children[0])
        if not isinstance(expr, str):
            print("Wrong expr")
        return '~ (' + expr + ')'

    elif repr(root) == 'xorBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') ^ (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'andBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') & (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'orBool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') | (' + write_expr(root.children[1]) + ')'

    elif repr(root) == '==Bool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') == (' + write_expr(root.children[1]) + ')'

    elif repr(root) == '=/=Bool':
        assert len(root.children) == 2
        return '(' + write_expr(root.children[0]) + ') != (' + write_expr(root.children[1]) + ')'

    elif repr(root) == 'undefBool':
        return 'NewBvVar(undef, 1)'

    elif repr(root) == 'false':
        return 'BoolConst(false)'

    elif repr(root) == 'true':
        return 'BoolConst(true)'

    elif re.fullmatch(r'\s*R\d+', repr(root)):
        return repr(root)

    elif re.fullmatch(r'^\s*%?\w+x', repr(root)):
        m = re.search(r'^\s*%?(\w+x)\s*$', repr(root))
        return m.group(1)

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

    elif re.fullmatch(r'rol', repr(root)):
        toWrite = 'LRotate(' + write_expr(root.children[0]) + ', ' + to_imme(write_expr(root.children[1])) + ')'
        return toWrite

    elif re.fullmatch(r'sameRegisters', repr(root)):
        expr1 = write_expr(root.children[0])
        expr2 = write_expr(root.children[1])
        if not isinstance(expr1, str):
            print("Wrong expr1")
        if not isinstance(expr2, str):
            print("Wrong expr2")
        toWrite = '(' + expr1 + ') == (' + expr2 + ')'
        return toWrite

    elif re.fullmatch(r'^\d+$', repr(root)):
        return repr(root)
        
    else:
        logging.error('Not a supported expression: '+repr(root))
    #TODO: More 'elif' to be added


def cal_width(root):
    if repr(root) == 'uvalue' or repr(root) == 'svalue':
        return cal_width(root.children[0])
    elif repr(root) == 'mi_eq' or repr(root) == 'mi_ne':
        return to_int(repr(root.children[0]))
    elif repr(root) == 'concatenate':
        return cal_width(root.children[0]) + cal_width(root.children[1])
    elif re.fullmatch(r'\d+', repr(root)):
        return to_int(repr(root))
    elif repr(root) == 'lshr' or \
            repr(root) == 'add' or \
            repr(root) == 'sub' or \
            repr(root) == 'and' or \
            repr(root) == 'lshr' or \
            repr(root) == 'or' or \
            repr(root) == 'xor' or \
            repr(root) == 'neg' or \
            repr(root) == 'shiftLeft' or \
            repr(root) == 'aShiftRight':
                return cal_width(root.children[0])
    elif repr(root) == 'extract':
        return cal_width(root.children[2]) - cal_width(root.children[1])

            
    elif len(root.children) > 0:
        maxWidth = 0
        for child in root.children:
            localWidth = cal_width(child)
            if localWidth != None:
                maxWidth = max(maxWidth, localWidth)
        if maxWidth == 0:
            return None
        else:
            return maxWidth
    else:
        return None


def translate_expr(expr):
    tree = parse_expr(expr)
    if tree == None:
        return ''
    return write_expr(tree)


# this function is currently integrated into the process_file function
def process_require(readPath, fileName):
    fRead = open(readPath+'/'+fileName, "r")
    fReadLines = fRead.readlines()
    regs = []
    updates = defaultdict(list)
    conditions = []
    for line in fReadLines:
        if re.search(r'\|->', line):
            m = re.search(r'(\S+) \|-> (.+)', line)
            reg = m.group(1)
            update = m.group(2)
            if reg not in updates:
                regs.append(reg)
            updates[reg].append(update)
        elif re.search(r'requires', line):
            m = re.search(r'^\s*requires (.+)$', line)
            conditions.append(m.group(1))


def translate_update(update, fWrite=None):

    toWrite = None
    if update == '(undefMInt)':
        return 'undef'
    # if update is a machine integer
    elif update[0:2] == 'mi':
        m = re.search(r'mi\((.+)\)', update)
        if m == None:
            logging.error('Not a valid machine integer!! '+update+'\n')
        params = m.group(1)
        params = pick_top_comma(params)
        children = re.split(r'\|', params)
        assert len(children) == 2, 'Wrong number of children'
        bitWidth = children[0]
        value = children[1]
        toWrite = "bv("+translate_expr(value)+")"

    # if update is an expression
    elif re.search(r'^\w+MInt', update):
        tree = BTree(name=None)
        tree = parse_expr(update, tree)
        if tree == None:
            return
        toWrite = write_expr(tree);
    
    # if update is if statement
    elif re.search(r'^\s*\(#ifMInt', update):
        update = de_bracket(update)
        update = de_nest_if(update)
        m = re.search(r'^\s*(\()?#IfMInt (.+) #Then (.+) #Else (.+) #Fi(\))?', update)
        if m == None:
            logging.error('If statement is not matched!!')
        ifExpr = de_bracket(m.group(2))
        thenExpr = de_bracket(m.group(3))
        elseExpr = de_bracket(m.group(4))
        toWrite = "Ite( "+translate_expr(ifExpr)+', '+translate_expr(thenExpr)+', '+translate_expr(elseExpr)+')'
       
    else:
        toWrite = translate_expr(update)

    if fWrite != None:        
        fWrite.write(toWrite)
    else:
        return toWrite


def translate_reg(reg, isReg, fWrite):
# return reg name
    if re.search(r'^"(\w+)"$', reg):
        m = re.search(r'^"(\w+)"$', reg)
        regPrint = m.group(1)
        if is_flag(regPrint) == False:
            isReg = 1

    elif reg[0:13] == 'convToRegKeys':
        m = re.search(r'convToRegKeys\((\w+)\)', reg)
        regPrint = m.group(1)
        isReg = 1

    if isReg == 0:
        fWrite.write("instr.SetUpdate("+regPrint+", ")
    else:
        fWrite.write("UPDATE_R("+regPrint+", ")

    return regPrint


def process_file(readPath, writePath, fileName):

    # file operations
    fRead = open(readPath+'/'+fileName, "r")
    m = re.search(r'^(.+)\.k$', fileName)
    fWriteName = m.group(1)+'.cc'
    instName = m.group(1)
    fWrite = open(writePath+'/'+fWriteName, "w")
    fReadLines = fRead.readlines()
    
    # flags and data structures
    updateRIP = 0
    regs = []
    updateDict = defaultdict(list)
    conditions = []
    lastLineIsRegState = False

    # collect updates from file
    for line in fReadLines:
        if re.search(r'\|->', line):
            m = re.search(r'(\S+) \|-> (.+)', line)
            reg = m.group(1)
            update = m.group(2)
            if reg not in updateDict:
                regs.append(reg)
            updateDict[reg].append(update)
        elif re.search(r'</regstate>', line):
            lastLineIsRegState = True
        elif re.search(r'requires', line) and lastLineIsRegState:
            m = re.search(r'^\s*requires (.+)$', line)
            conditions.append(m.group(1))
            lastLineIsRegState = False

    fWrite.write('auto instr = model.NewInstr(' + '"'+ instName + '"' + ');\n')
    # parse updateDict data structure and write to file
    for reg in regs:
        if reg == 'PC' or reg == 'pc':
            updateRIP = 1
        isReg = 0

        # parse reg
        regName = translate_reg(reg, isReg, fWrite) # need to add one closing bracket
        isReg = 0 if is_flag(regName) else 1
        updateList = updateDict[reg]
        listLen = len(updateList)

        for idx, update in enumerate(updateList):
            translatedUpdate = translate_update(update)
            if translatedUpdate == 'undef':
                translatedUpdate = 'NewBvVar('+ regName +', '+ (str(64) if isReg == 1 else str(1)) +')'
            if translatedUpdate == None:
                print('wrong translatedUpdate')
            if idx < listLen - 1:
                fWrite.write("Ite( "+ translate_expr(conditions[idx]) + ', ' + translatedUpdate + ', ' )
            else:
                fWrite.write(translatedUpdate)

        for i in range(len(updateList)-1):
            fWrite.write(')')
        fWrite.write(');\n')
            
    if updateRIP == 0:
        fWrite.write("instr.SetUpdate(rip, nxt_rip);\n")
    fWrite.write('RECORD_INST("'+instName+'");\n')
    fWrite.close()
    fRead.close()
    return True


if __name__ == "__main__":
    process_file(sys.argv[1], sys.argv[2], sys.argv[3])
