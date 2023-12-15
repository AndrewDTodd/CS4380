#ifndef BAL_R_H
#define BAL_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BAL_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BAL_R();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BAL_R_H
