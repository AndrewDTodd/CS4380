#include "../include/ISA_4380.h"

#include "../include/Instruction.h"
#include "../include/Process_4380.h"

#include <cstdint>

using namespace VMFramework;

Instruction<int32_t, Process_4380>* instructions[] =
{
	new ADD(),
	new DIV(),
	new JMP_L(),
	new LDB_L(),
	new LDR_L(),
	new MOV(),
	new STB_L(),
	new STR_L(),
	new MUL(),
	new SUB(),
	new TRP()
};

ISA_4380::ISA_4380(): ISA<int32_t, Process_4380>(instructions, 11)
{
}