#ifndef ALLC_R_H
#define ALLC_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct ALLC_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	ALLC_R();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ALLC_R_H
