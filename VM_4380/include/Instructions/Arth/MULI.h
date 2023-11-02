#ifndef MULI_H
#define MULI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct MULI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	MULI();

	void Op(Process_4380* executingProcess) override;
};
#endif //!MULI_H