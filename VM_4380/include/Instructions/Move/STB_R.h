#ifndef STB_R_H
#define STB_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct STB_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	STB_R();

	void Op(Process_4380* executingProcess) override;
};
#endif // !STB_R_H
