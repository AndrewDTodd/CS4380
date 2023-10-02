#ifndef LDB_L_H
#define LDB_L_H

#include "../../../VMFramework/include/Instruction.h"

#include <cstdint>

#include "../Process_4380.h"

struct LDB_L : public VMFramework::Instruction<int32_t, int32_t, Process_4380>
{
public:
	LDB_L();

	void Op(Process_4380* executingProcess) override;
};
#endif //!LDB_L_H
