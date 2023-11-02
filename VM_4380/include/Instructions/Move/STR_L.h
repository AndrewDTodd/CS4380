#ifndef STR_L_H
#define STR_L_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct STR_L : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	STR_L();

	void Op(Process_4380* executingProcess) override;
};
#endif // !STR_L_H
