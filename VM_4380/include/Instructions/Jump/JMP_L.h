#ifndef JMP_L_H
#define JMP_L_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct JMP_L : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	JMP_L();

	void Op(Process_4380* executingProcess) override;
};
#endif //!JMP_L_H
