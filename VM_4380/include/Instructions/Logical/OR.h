#ifndef OR_H
#define OR_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct OR : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	OR();

	void Op(Process_4380* executingProcess) override;
};
#endif // !OR_H
