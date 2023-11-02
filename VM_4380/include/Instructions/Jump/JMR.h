#ifndef JMR_H
#define JMR_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct JMR : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	JMR();

	void Op(Process_4380* executingProcess) override;
};
#endif //!JMR_H
