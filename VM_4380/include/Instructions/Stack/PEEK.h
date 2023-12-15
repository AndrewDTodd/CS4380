#ifndef PEEK_H
#define PEEK_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct PEEK : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	PEEK();

	void Op(Process_4380* executingProcess) override;
};
#endif // !PEEK_H
