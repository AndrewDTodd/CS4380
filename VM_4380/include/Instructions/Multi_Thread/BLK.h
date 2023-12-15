#ifndef BLK_H
#define BLK_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BLK : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BLK();

	void Op(Process_4380* executingProcess) override;
};
#endif // !BLK_H
