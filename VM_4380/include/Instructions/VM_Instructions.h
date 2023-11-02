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

//Jump
#include "Jump/BGT.h"
#include "Jump/BLT.h"
#include "Jump/BNZ.h"
#include "Jump/BRZ.h"
#include "Jump/JMP_L.h"
#include "Jump/JMR.h"

//Logical

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

//TRP
#include "TRP/TRP.h"

#endif //!VM_INSTRUCTIONS_H
