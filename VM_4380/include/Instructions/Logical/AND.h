#ifndef AND_H
#define AND_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct AND : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	AND();

	void Op(Process_4380* executingProcess) override;
};
#endif // !AND_H
