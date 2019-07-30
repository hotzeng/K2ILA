cd /workspace/research/ILA/x86/K2ILA/x86_k/semantics
cd registerInstructions
for fileName in ./*.k; do
  if ["$fileName" = $1]; 
  then
    #vim $1
    gvim $fileName
    exit
  fi
done

#cd ../immediateInstructions
#for fileName in ./*.k; do
#  if $fileName == $1 
#  then
#    vim $1
#    exit
#  fi
#done
#
#cd ../memoryInstructions
#for fileName in ./*.k; do
#  if $fileName == $1
#  then
#    vim $1
#    exit
#  fi
#done
#
#cd ../pseudoTestInstructions
#for fileName in ./*.k; do
#  if $fileName == $1 
#  then
#    vim $1
#    exit
#  fi
#done
#
#cd ../systemInstructions
#for fileName in ./*.k; do
#  if $fileName == $1 
#  then
#    vim $1
#    exit
#  fi
#done

