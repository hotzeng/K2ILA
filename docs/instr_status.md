When you are sure one instruction model is correct, change its state to 'DONE'
Also, put the correct ILA model in 'x86\_ila\_golden' folder!
This is necessary because later changes to the script may modify previous generated ILA model, and we need to check all the models against golden every time.

## Register Instructions
Instructions | Status | Author
-------------|--------|-------
andnq\_r64\_r64\_64 | DONE  | Yu
andb\_r8\_rh        | TODO  |
blsil\_r32\_r32     | TODO  |
cmovael\_r32\_r32   | TODO  |
divb\_r8            | TODO  |
mulb\_rh            | TODO  |
orb\_r8\_r8         | TODO  |
rorl\_r32\_one      | TODO  |


## Immediate Instructions
Instructions | Status | Author
-------------|--------|-------
addl\_eax\_imm32    | TODO  |
cmpq\_r64\_label    | TODO  |
testl\_r32\_imm32   | TODO  |

## Memory Instructions
Instructions | Status | Author
-------------|--------|-------
addq\_m64\_imm32    | TODO  |
blsil\_r32\_m32     | TODO  |
cmpxchgl\_m32\_r32  | TODO  |

## System Instructions
Instructions | Status | Author
-------------|--------|-------
callq\_label        | TODO  |
ja\_label           | TODO  |
loop\_rel8          | TODO  |
popq\_r64           | TODO  |
retq                | TODO  |
