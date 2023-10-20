#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <vector>
#include <unordered_map>
#include <utility>
#include <cstdint>
#include <shared_mutex>
#include <memory>

struct ASMDirective;
struct ASMInstruction;

namespace ASMFramework
{
	struct Workpiece
	{
		std::shared_mutex _sharedMutex;

		std::unordered_map<std::string, uint64_t> _symbolTable;

		std::vector<const ASMDirective*> _dataSegmentDir;
		std::vector<uint8_t> _dataSegmentBin;

		//pair key is segment label, which can be "" for unlabled code segment
		std::vector<std::pair<std::string, std::vector<const ASMInstruction*>>> _codeSegmentItems;
		std::vector<std::pair<std::string, std::vector<uint8_t>>> _codeSegmentBin;
	};
}
#endif // !WORKPIECE_H
