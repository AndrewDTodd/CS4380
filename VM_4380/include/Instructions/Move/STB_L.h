#ifndef STB_L_H
#define STB_L_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct STB_L : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	STB_L();

	void Op(Process_4380* executingProcess) override;
};
#endif // !STB_L_H
