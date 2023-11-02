#ifndef BNZ_H
#define BNZ_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BNZ : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BNZ();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BNZ_H