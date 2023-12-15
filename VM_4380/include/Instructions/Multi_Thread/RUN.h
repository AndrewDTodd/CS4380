#ifndef RUN_H
#define RUN_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct RUN : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	RUN();

	void Op(Process_4380* executingProcess) override;
};
#endif // !RUN_H
