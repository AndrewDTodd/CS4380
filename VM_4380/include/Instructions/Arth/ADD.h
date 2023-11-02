#ifndef ADD_H
#define ADD_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct ADD : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	ADD();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ADD_H
