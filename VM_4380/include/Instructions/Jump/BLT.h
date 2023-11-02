#ifndef BLT_H
#define BLT_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BLT : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BLT();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BLT_H