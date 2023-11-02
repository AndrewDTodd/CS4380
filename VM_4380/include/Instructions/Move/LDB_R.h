#ifndef LDB_R_H
#define LDB_R_H

#include <Instruction.h>

#include <cstdint>

class Process_4380;

struct LDB_R : public VMFramework::Instruction<int32_t, Process_4380>
{
public:
	LDB_R();

	void Op(Process_4380* executingProcess) override;
};
#endif //!LDB_R_H
