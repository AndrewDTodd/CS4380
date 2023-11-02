#ifndef LDR_R_H
#define LDR_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct LDR_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	LDR_R();

	void Op(Process_4380* executingProcess) override;
};
#endif //!LDR_R_H
