#ifndef LDR_L_H
#define LDR_L_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

#include "../Process_4380.h"

struct LDR_L : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	LDR_L();

	void Op(Process_4380* executingProcess) override;
};
#endif //!LDR_L_H
