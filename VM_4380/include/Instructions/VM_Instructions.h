#ifndef VM_INSTRUCTIONS_H
#define VM_INSTRUCTIONS_H

//Arithmetic
#include "Arth/ADD.h"
#include "Arth/ADDI.h"
#include "Arth/DIV.h"
#include "Arth/DIVI.h"
#include "Arth/MUL.h"
#include "Arth/MULI.h"
#include "Arth/SUB.h"

//Compare
#include "Comp/CMP.h"
#include "Comp/CMPI.h"

//Heap
#include "Heap/ALCI.h"
#include "Heap/ALLC_L.h"
#include "Heap/ALLC_R.h"
#include "Heap/FREE.h"

//Jump
#include "Jump/BAL_L.h"
#include "Jump/BAL_R.h"
#include "Jump/BGT.h"
#include "Jump/BLT.h"
#include "Jump/BNZ.h"
#include "Jump/BRZ.h"
#include "Jump/JMP_L.h"
#include "Jump/JMR.h"

//Logical
#include "Logical/AND.h"
#include "Logical/NOT.h"
#include "Logical/OR.h"

//Move
#include "Move/LDA.h"
#include "Move/LDB_L.h"
#include "Move/LDB_R.h"
#include "Move/LDR_L.h"
#include "Move/LDR_R.h"
#include "Move/MOV.h"
#include "Move/MOVI.h"
#include "Move/STB_L.h"
#include "Move/STB_R.h"
#include "Move/STR_L.h"
#include "Move/STR_R.h"

//Multi_Thread
#include "Multi_Thread/BLK.h"
#include "Multi_Thread/END.h"
#include "Multi_Thread/LCK.h"
#include "Multi_Thread/RUN.h"
#include "Multi_Thread/ULK.h"

//Stack
#include "Stack/PEEK.h"
#include "Stack/POP.h"
#include "Stack/PUSH.h"

//TRP
#include "TRP/TRP.h"

#endif //!VM_INSTRUCTIONS_H
