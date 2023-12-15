#ifndef LCK_H
#define LCK_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct LCK : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	LCK();

	void Op(Process_4380* executingProcess) override;
};
#endif // !LCK_H
