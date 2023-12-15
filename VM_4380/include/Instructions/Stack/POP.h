#ifndef POP_H
#define POP_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct POP : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	POP();

	void Op(Process_4380* executingProcess) override;
};
#endif // !POP_H
