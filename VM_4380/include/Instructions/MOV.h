#ifndef MOV_H
#define MOV_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

#include "../Process_4380.h"

struct MOV : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	MOV();

	void Op(Process_4380* executingProcess) override;
};
#endif //!MOV_H
