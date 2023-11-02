#ifndef CMPI_H
#define CMPI_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct CMPI : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	CMPI();

	void Op(Process_4380* executingProcess) override;
};
#endif //!CMPI_H
