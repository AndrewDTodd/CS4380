#ifndef ADDI_H
#define ADDI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct ADDI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	ADDI();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ADDI_H
