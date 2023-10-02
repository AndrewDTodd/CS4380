#ifndef ADD_H
#define ADD_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

#include "../Process_4380.h"

struct ADD : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	ADD();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ADD_H
