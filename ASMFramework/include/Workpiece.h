#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <vector>
#include <list>
#include <unordered_map>
#include <utility>
#include <cstdint>
#include <shared_mutex>
#include <memory>
#include <concepts>

namespace ASMFramework
{
	struct ASMDirective;
	struct ASMInstruction;

	struct DataSegmentItem
	{
		size_t _lineNum;
		const ASMDirective* _directive;
		std::vector<std::string> _dirArgs;
		std::string _lineComment;
	};

	struct CodeSegmentItem
	{
		size_t _lineNum;
		const ASMInstruction* _instruction;
		std::vector<std::string> _instrArgs;
		std::string _lineComment;
	};

	struct Workpiece
	{
		std::shared_mutex _sharedMutex;

		std::unordered_map<std::string, size_t> _symbolTable;
		//std::unordered_map<std::string, uint64_t> _symbolTable;
		std::unordered_map<std::string, std::vector<std::pair<std::vector<uint8_t>*, size_t>>> _unresolvedLabels;
		//std::unordered_map<std::string, std::vector<void*>> _unresolvedLabels;

		//key is directive label, which can be "" for unlabled directive
		std::vector<std::pair<std::string, DataSegmentItem>> _dataSegmentItems;
		std::vector<uint8_t> _dataSegmentBin;

		//key is segment label, which can be "" for unlabled code segment
		std::vector<std::pair<std::string, std::vector<CodeSegmentItem>>> _codeSegmentItems;
		std::list<std::pair<std::string, std::vector<uint8_t>>> _codeSegmentBins;
	};
}
#endif // !WORKPIECE_H
