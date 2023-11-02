#ifndef LDA_H
#define LDA_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct LDA : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	LDA();

	void Op(Process_4380* executingProcess) override;
};
#endif // !LDA_H
