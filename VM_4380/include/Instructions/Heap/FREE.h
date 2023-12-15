#ifndef FREE_H
#define FREE_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct FREE : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	FREE();

	void Op(Process_4380* executingProcess) override;
};
#endif // !FREE_H
