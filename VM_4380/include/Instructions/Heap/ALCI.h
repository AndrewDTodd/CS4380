#ifndef ALCI_H
#define ALCI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct ALCI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	ALCI();

	void Op(Process_4380* executingProcess) override;
};
#endif // !ALCI_H
