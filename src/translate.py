# 07/03/2019
# Author: Yu Zeng
# The translation script

import sys
import re
import os
import logging
import subprocess
from util.tree import BTree
from translate_single_file import process_file

MULTI_PROCESS = True

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
    #readPath = '../x86_k/semantics/immediateInstructions'
    #writePath = '../x86_ila/semantics/immediateInstructions'
    readPath = '../x86_k/semantics/immediateInstructions'
    writePath = '../x86_ila/semantics/immediateInstructions'
    passedFiles = '/workspace/research/ILA/x86/K2ILA/src/results/passed.txt'
    failedFiles = '/workspace/research/ILA/x86/K2ILA/src/results/failed.txt'
    fileName = None
    # FIXME: specify the file name if you want to run on only one file
    #fileName = 'cmpq_r64_label.k'
    if len(sys.argv) > 1:
        fileName = sys.argv[1]
    if fileName != None:
        process_file(readPath, writePath, fileName)
    else:
        passFile = open(passedFiles, 'w')
        failFile = open(failedFiles, 'w')
        for fileName in os.listdir(readPath):
            if re.search(r'xmm', fileName) or re.search(r'ymm', fileName) or re.search(r'swp', fileName) or re.search(r'swo', fileName):
                continue
            if MULTI_PROCESS == False:
                process_file(readPath, writePath, fileName)
                print(fileName)
            else:
                out = subprocess.run(['python3', 'translate_single_file.py', readPath, writePath, fileName])
                if out.returncode == 0:
                    print('Done')
                    passFile.write(fileName+'\n')
                else:
                    print('Error')
                    failFile.write(fileName+'\n')                    


if __name__ == "__main__":
    main()
