#ifndef END_H
#define END_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct END : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	END();

	void Op(Process_4380* executingProcess) override;
};
#endif // !END_H
