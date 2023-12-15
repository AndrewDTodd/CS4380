#include "../include/ISA_4380.h"

#include "../include/Instruction.h"
#include "../include/Process_4380.h"

#include <cstdint>

using namespace VMFramework;

Instruction<int32_t, Process_4380>* instructions[] =
{
	//Arth **********
	new ADD(),
	new ADDI(),
	new DIV(),
	new DIVI(),
	new MUL(),
	new MULI(),
	new SUB(),
	//***************

	//Comp **********
	new CMP(),
	new CMPI(),
	//***************

	//Heap **********
	new ALCI(),
	new ALLC_L(),
	new ALLC_R(),
	new FREE(),
	//***************

	//Jump **********
	new BAL_L(),
	new BAL_R(),
	new BGT(),
	new BLT(),
	new BNZ(),
	new BRZ(),
	new JMP_L(),
	new JMR(),
	//***************

	//Logical *******
	new AND(),
	new NOT(),
	new OR(),
	//***************

	//Move **********
	new LDA(),
	new LDB_L(),
	new LDB_R(),
	new LDR_L(),
	new LDR_R(),
	new MOV(),
	new MOVI(),
	new STB_L(),
	new STB_R(),
	new STR_L(),
	new STR_R(),
	//***************

	//Multi_Thread **
	new BLK(),
	new END(),
	new LCK(),
	new RUN(),
	new ULK(),
	//***************

	//Stack *********
	new PEEK(),
	new POP(),
	new PUSH(),
	//***************

	//TRP ***********
	new TRP()
	//***************
};

ISA_4380::ISA_4380(): ISA<int32_t, Process_4380>(instructions, 44)
{
}