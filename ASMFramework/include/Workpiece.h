#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <vector>
#include <unordered_map>
#include <utility>
#include <cstdint>
#include <shared_mutex>
#include <memory>

namespace ASMFramework
{
	struct ASMDirective;
	struct ASMInstruction;

	struct DataSegmentItem
	{
		const ASMDirective* const& _directive;
		std::vector<std::string> _dirArgs;
		std::string _lineComment;
	};

	struct CodeSegmentItem
	{
		const ASMInstruction* const& _instruction;
		std::vector<std::string> _instrArgs;
		std::string _lineComment;
	};

	struct Workpiece
	{
		std::shared_mutex _sharedMutex;

		std::unordered_map<std::string, uint64_t> _symbolTable;

		//key is directive label, which can be "" for unlabled directive
		std::vector<std::pair<std::string, DataSegmentItem>> _dataSegmentItems;
		std::vector<uint8_t> _dataSegmentBin;

		//key is segment label, which can be "" for unlabled code segment
		std::vector<std::pair<std::string, std::vector<CodeSegmentItem>>> _codeSegmentItems;
		std::vector<std::pair<std::string, std::vector<uint8_t>>> _codeSegmentBin;
	};
}
#endif // !WORKPIECE_H
