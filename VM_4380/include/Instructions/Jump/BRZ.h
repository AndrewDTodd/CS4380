#ifndef BRZ_H
#define BRZ_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BRZ : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BRZ();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BRZ_H