#ifndef MOV_H
#define MOV_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct MOV : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	MOV();

	void Op(Process_4380* executingProcess) override;
};
#endif //!MOV_H
