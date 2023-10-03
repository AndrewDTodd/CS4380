#ifndef MUL_H
#define MUL_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

class Process_4380;

struct MUL : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	MUL();

	void Op(Process_4380* executingProcess) override;
};
#endif //!MUL_H