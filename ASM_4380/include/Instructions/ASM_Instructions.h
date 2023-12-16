#ifndef ASM_INSTRUCTIONS_H
#define ASM_INSTRUCTIONS_H

//Arithmetic
#include "Arth_INS/ADD_INS.h"
#include "Arth_INS/ADI_INS.h"
#include "Arth_INS/DIVI_INS.h"
#include "Arth_INS/DIV_INS.h"
#include "Arth_INS/MULI_INS.h"
#include "Arth_INS/MUL_INS.h"
#include "Arth_INS/SUB_INS.h"

//Compare
#include "Comp_INS/CMPI_INS.h"
#include "Comp_INS/CMP_INS.h"

//Heap
#include "Heap_INS/ALCI_INS.h"
#include "Heap_INS/ALLC_INS.h"
#include "Heap_INS/FREE_INS.h"

//Jump
#include "Jump_INS/BAL_INS.h"
#include "Jump_INS/BGT_INS.h"
#include "Jump_INS/BLT_INS.h"
#include "Jump_INS/BNZ_INS.h"
#include "Jump_INS/BRZ_INS.h"
#include "Jump_INS/JMP_INS.h"
#include "Jump_INS/JMR_INS.h"

//Logical
#include "Logical_INS/AND_INS.h"
#include "Logical_INS/NOT_INS.h"
#include "Logical_INS/OR_INS.h"

//Move
#include "Move_INS/LDA_INS.h"
#include "Move_INS/LDB_INS.h"
#include "Move_INS/LDR_INS.h"
#include "Move_INS/MOVI_INS.h"
#include "Move_INS/MOV_INS.h"
#include "Move_INS/STB_INS.h"
#include "Move_INS/STR_INS.h"

//Multi_Thread
#include "Multi_Thread_INS/BLK_INS.h"
#include "Multi_Thread_INS/END_INS.h"
#include "Multi_Thread_INS/LCK_INS.h"
#include "Multi_Thread_INS/RUN_INS.h"
#include "Multi_Thread_INS/ULK_INS.h"

//Stack
#include "Stack_INS/PEEK_INS.h"
#include "Stack_INS/POP_INS.h"
#include "Stack_INS/PUSH_INS.h"

//TRP
#include "TRP_INS/TRP_INS.h"

#endif // !ASM_INSTRUCTIONS_H
