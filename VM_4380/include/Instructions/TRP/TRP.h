#ifndef TRP_H
#define TRP_H

#include <Instruction.h>

#include <cstdint>
#include <regex>

class Process_4380;

struct TRP : public VMFramework::Instruction<int32_t, Process_4380>
{
private:
	static const std::regex hexPattern;
	static const std::regex asciiPattern;

public:
	TRP();

	void Op(Process_4380* executingProcess) override;
};
#endif //!TRP_H
