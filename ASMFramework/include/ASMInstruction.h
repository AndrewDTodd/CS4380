#ifndef ASM_INSTRUCTION_H
#define ASM_INSTRUCTION_H

#include <string>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <concepts>
#include <regex>

#include "Workpiece.h"

#include "rootConfig.h"

namespace ASMFramework
{
	struct ASMInstruction
	{
	protected:
		ASMInstruction(std::string&& mnemonic);

		static const std::regex registerPattern;

		template<std::integral InputType, std::integral TargetType>
		static inline void SerializeToBuffer(const InputType& value, std::vector<uint8_t>& buffer)
		{
			if constexpr (is_little_endian)
			{
				//Target is little-endian already
				const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&static_cast<TargetType>(value));
				for (size_t i = 0; i < sizeof(TargetType); i++)
				{
					buffer.push_back(bytes[i]);
				}
			}
			else
			{
				TargetType castValue = static_cast<TargetType>(value);
				//Target is big-endian
				for (size_t i = 0; i < sizeof(TargetType); i++)
				{
					buffer.push_back((castValue >> (i * 8)) & 0xFF);
				}
			}
		}

	public:
		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembler does not yet support this Instruction";
			}
		};

		const std::string _mnemonic;

		virtual size_t Implementation(std::vector<uint8_t>& buffer, Workpiece* const& workpiece, const std::vector<std::string>& args) const = 0;
	};
}
#endif // !INSTRUCTION_H
