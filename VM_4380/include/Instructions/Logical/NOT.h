#ifndef NOT_H
#define NOT_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct NOT : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	NOT();

	void Op(Process_4380* executingProcess) override;
};
#endif // !NOT_H
