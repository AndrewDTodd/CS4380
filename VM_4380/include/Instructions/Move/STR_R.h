#ifndef STR_R_H
#define STR_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct STR_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	STR_R();

	void Op(Process_4380* executingProcess) override;
};
#endif // !STR_R_H
