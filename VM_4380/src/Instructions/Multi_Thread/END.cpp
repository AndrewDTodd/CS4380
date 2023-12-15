#include "../../../include/Instructions/Multi_Thread/END.h"

#include "../../../include/Process_4380.h"

END::END() : Instruction(28)
{}

void END::Op(Process_4380* executingProcess)
{
	throw NotImplemented();
}