#ifndef ASM_DIRECTIVE_H
#define ASM_DIRECTIVE_H

#include <stdexcept>
#include <vector>
#include <regex>
#include <string>

#include "Workpiece.h"

#include "rootConfig.h"

namespace ASMFramework
{
	struct ASMDirective
	{
	protected:
		ASMDirective(std::string&& mnemonic);

		static const std::regex decimalPattern;
		static const std::regex hexPattern;
		static const std::regex asciiPattern;
		static const std::regex stringPattern;

		template<std::integral InputType, std::integral TargetType>
		static inline void SerializeToBuffer(const InputType& value, Workpiece* const& workpiece)
		{
			if constexpr (is_little_endian)
			{
				//Target is little-endian already
				TargetType castValue = static_cast<TargetType>(value);
				const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&castValue);
				for (size_t i = 0; i < sizeof(TargetType); i++)
				{
					workpiece->_dataSegmentBin.push_back(bytes[i]);
				}
			}
			else
			{
				TargetType castValue = static_cast<TargetType>(value);
				//Target is big-endian
				for (size_t i = 0; i < sizeof(TargetType); i++)
				{
					workpiece->_dataSegmentBin.push_back((castValue >> (i * 8)) & 0xFF);
				}
			}
		}

	public:
		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembler does not yet support this Directive";
			}
		};

		const std::string _mnemonic;

		virtual size_t Implementation(Workpiece* const& workpiece, const std::vector<std::string>& args) const = 0;
	};
}
#endif // !ASM_DIRECTIVE_H
