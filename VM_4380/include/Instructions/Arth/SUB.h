#ifndef SUB_H
#define SUB_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct SUB : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	SUB();

	void Op(Process_4380* executingProcess) override;
};
#endif //!SUB_H
