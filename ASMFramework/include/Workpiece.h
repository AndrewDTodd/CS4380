#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <vector>
#include <unordered_map>
#include <utility>

#include <cstdint>

struct Directive;
struct Instruction;

namespace ASMFramework
{
	struct Workpiece
	{
		const std::unordered_map<std::string, uint64_t> _symbolTable;

		const std::vector<Directive> _dataSegmentDir;
		const std::vector<uint8_t> _dataSegmentBin;

		const std::vector<std::pair<std::string, std::vector<Instruction>>> _codeSegmentItems;
		const std::vector<std::pair<std::string, std::vector<uint8_t>>> _codeSegmentBin;
	};
}
#endif // !WORKPIECE_H
