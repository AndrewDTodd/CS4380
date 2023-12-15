#ifndef BAL_L_H
#define BAL_L_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BAL_L : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BAL_L();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BAL_L_H
