#ifndef ALLC_L_H
#define ALLC_L_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct ALLC_L : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	ALLC_L();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ALLC_L_H
