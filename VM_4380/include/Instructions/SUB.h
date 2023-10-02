#ifndef SUB_H
#define SUB_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

#include "../Process_4380.h"

struct SUB : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	SUB();

	void Op(Process_4380* executingProcess) override;
};
#endif //!SUB_H