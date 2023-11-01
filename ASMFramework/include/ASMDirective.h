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
		static const std::regex asciiEscape;
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

		/// <summary>
		/// Called by passes to preform the directives work on the workpiece
		/// </summary>
		/// <param name="workpiece">The Workpiece instance being worked on</param>
		/// <param name="args">A vector containing the arguments that were tokenized for the directive</param>
		/// <returns>The number of bytes written to the workpiece's directives binary container</returns>
		/// <exception cref="std::runtime_error Thrown by the directive if the operation cannot be completed properly"/>
		/// <exception cref="ASMDirective::NotImplemented Thrown by the directive to signify that its tooling is not implemented, and therefore the directive is unsupported at this time"/>
		virtual size_t Implementation(Workpiece* const& workpiece, const std::vector<std::string>& args) const = 0;
	};
}
#endif // !ASM_DIRECTIVE_H
