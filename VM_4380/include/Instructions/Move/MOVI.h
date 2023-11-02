#ifndef MOVI_H
#define MOVI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct MOVI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	MOVI();

	void Op(Process_4380* executingProcess) override;
};
#endif //!MOVI_H
