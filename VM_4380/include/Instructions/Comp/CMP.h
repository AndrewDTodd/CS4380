#ifndef CMP_H
#define CMP_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct CMP : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	CMP();

	void Op(Process_4380* executingProcess) override;
};
#endif //!CMP_H
