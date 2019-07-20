# 07/19/2019
# Author: Yu Zeng
# This is a regression test against golden

import re
import os

dirs = ['registerInstructions']
goldenPath = '/workspace/research/ILA/x86/K2ILA/docs/x86_ila_golden/'
ilaPath = '/workspace/research/ILA/x86/K2ILA/x86_ila/semantics/'

def main():
    for d in dirs:
        for fileName in os.listdir(goldenPath + d):
            print(fileName)
            m = re.search(r'(.+)\.cc', fileName)
            os.system('py3 /workspace/research/ILA/x86/K2ILA/src/translate.py '+m.group(1)+'.k')
            os.system('diff '+goldenPath+d+'/'+fileName+' '+ilaPath+d+'/'+fileName)

