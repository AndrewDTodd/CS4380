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
	//***************

	//Jump **********
	new BGT(),
	new BLT(),
	new BNZ(),
	new BRZ(),
	new JMP_L(),
	new JMR(),
	//***************

	//Logical *******
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
	//***************

	//TRP ***********
	new TRP()
	//***************
};

ISA_4380::ISA_4380(): ISA<int32_t, Process_4380>(instructions, 27)
{
}