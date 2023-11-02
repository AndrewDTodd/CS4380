#ifndef DIVI_H
#define DIVI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct DIVI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	DIVI();

	void Op(Process_4380* executingProcess) override;
};
#endif // !DIVI_H
