#ifndef BGT_H
#define BGT_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct BGT : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	BGT();

	void Op(Process_4380* executingProcess) override;
};
#endif //!BGT_H