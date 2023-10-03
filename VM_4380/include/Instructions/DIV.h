#ifndef DIV_H
#define DIV_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

class Process_4380;

struct DIV : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	DIV();

	void Op(Process_4380* executingProcess) override;
};
#endif // !DIV_H
