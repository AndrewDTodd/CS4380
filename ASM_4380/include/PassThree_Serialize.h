#ifndef PASS_THREE_SERIALIZE_H
#define PASS_THREE_SERIALIZE_H

#include <Pass.h>

#include <filesystem>
#include <cstdint>
#include <fstream>

class PassThree_Serialize : public ASMFramework::Pass
{
private:
	size_t SerializeInitialPC(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const;

	size_t SerializeDataSegment(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const;

	size_t SerializeCodeSegment(std::ofstream& fileStream, ASMFramework::Workpiece* const& workpiece) const;

public:
	void Execute(ASMFramework::Workpiece* const& workpiece, const std::filesystem::path& filePath, const ASMFramework::LanguageDefinition* const& langDef) const override;
};
#endif // !PASS_THREE_SERIALIZE_H
