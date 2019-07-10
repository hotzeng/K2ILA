# TODO list for x86 ILA model
## Translating x86 ISA k-semantics to ILA model
There are 3155 instructions with k-semantics. We need to write translation scripts for them. Also, some improvements need to be done, for example, add 'pc' update to all instructions, add some implicit states to some instructions(string modifying instructions). 

The x86 ISA k-semantics mainly contain two parts: the semantics of individual instructions(in the /semantics/\*Instructions folders), and semantics of execution environment(the x86-\*.k files).

The status of instructions can be found in file instr\_status.md. You can find all the k-semantics [here](https://github.com/kframework/X86-64-semantics/tree/master/semantics): 

## Translating x86 decoding k-semantics to ILA model
The UIUC's group has formalized the Intel's XED decoding algorithm, and we also need to translate that into ILA model since decoding is part of the ILA models. Their work has not been published, so email me if you want to read their draft paper.

## System-level and concurrenty instructions
These instructions do not have k-semantics yet, and we need to wtite their ILA models by ourself. To do these we need to model paging, segmentation, caches, etc. 
