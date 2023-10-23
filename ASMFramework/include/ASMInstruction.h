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
		static const std::regex decimalPattern;
		static const std::regex hexPattern;
		static const std::regex asciiPattern;

		static inline uint64_t& GetLabelOffset(const std::string& labelName, Workpiece* const& workpiece)
		{
			try
			{
				return workpiece->_symbolTable.at(labelName);
			}
			//If the label argument of JMP isnt in the symbol table we must assume the assembly contains an invalid label name
			catch (const std::out_of_range& rangeEx)
			{
				throw std::runtime_error("The label - \"" + labelName + "\" - is undefined (not contained within the sybol table)");
			}
		}

		static inline void AddUnresolvedLabel(const std::string& labelName, std::vector<uint8_t>& buffer, Workpiece* const& workpiece)
		{
			size_t buffOffset = buffer.size() - sizeof(int32_t);

			workpiece->_unresolvedLabels[labelName].push_back(reinterpret_cast<void*>(buffer.data() + buffOffset));
		}

		template<std::integral TargetType, std::integral... InputType>
		static inline void SerializeToBuffer(std::vector<uint8_t>& buffer, const InputType&... value)
		{
			if constexpr (is_little_endian)
			{
				//Target is little-endian already
				/*const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&static_cast<TargetType>(value));
				for (size_t i = 0; i < sizeof(TargetType); i++)
				{
					buffer.push_back(bytes[i]);
				}*/

				(([&buffer, &value]()
				{
						TargetType castValue = static_cast<TargetType>(value);
						const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&castValue);
						for (size_t i = 0; i < sizeof(TargetType); i++)
						{
							buffer.push_back(bytes[i]);
						}
				}()), ...);
			}
			else
			{
				//TargetType castValue = static_cast<TargetType>(value);
				////Target is big-endian
				//for (size_t i = 0; i < sizeof(TargetType); i++)
				//{
				//	buffer.push_back((castValue >> (i * 8)) & 0xFF);
				//}

				(([&buffer, &value]()
				{
					TargetType castValue = static_cast<TargetType>(value);
					for (size_t i = 0; i < sizeof(TargetType); i++)
					{
						buffer.push_back((castValue >> (i * 8)) & 0xFF);
					}
				}()), ...);
			}
		}

		template<std::integral TargetType>
		static inline TargetType GetRegisterID(const std::string& mnemonic, const TargetType& minID, const TargetType& maxID)
		{
			if (!std::regex_match(mnemonic, registerPattern))
				throw std::runtime_error("Inproperly formatted register mnemonic \"" + mnemonic + "\". Accepted values are R" + 
					std::to_string(minID) + " - R" + std::to_string(maxID));

			int id = std::stoi(mnemonic.substr(1));

			if (id < minID || id > maxID)
				throw std::runtime_error("Invalid register ID. System has no general purpose register with id \"" + std::to_string(id) + "\". " + mnemonic +
					" is not a valid register mnemonic. Accepted values are R" +
					std::to_string(minID) + " - R" + std::to_string(maxID));

			return static_cast<TargetType>(id);
		}

		template<std::integral TargetType>
		static inline TargetType GetImmediateValue(const std::string& immediate)
		{
			//Match base ten with # as delimiter
			if (std::regex_match(immediate, decimalPattern))
			{
				try
				{
					int64_t value = std::stoll(immediate.substr(1));
					if (value < std::numeric_limits<TargetType>::min() || value > std::numeric_limits<TargetType>::max())
						throw std::runtime_error("The immediate exceeds the limits of the target word type. Value should be in range of " + 
							std::to_string(std::numeric_limits<TargetType>::min()) + " - " +
							std::to_string(std::numeric_limits<TargetType>::max()) + " inclusive. Argument was \"" + immediate.substr(1) + "\"");

					return static_cast<TargetType>(value);
				}
				catch (const std::invalid_argument& argEx)
				{
					throw std::runtime_error("invlaid_argument thrown when trying to convert immediate to base ten int \"" + immediate +
						"\"\n>>>" + argEx.what());
				}
				catch (const std::out_of_range& rngEx)
				{
					throw std::runtime_error("out_of_range thrown when trying to convert immediate to base ten int \"" + immediate +
						"\". Your argument is way too big\n>>>" + rngEx.what());
				}
			}
			//Match Hex with 0x as delimiter
			else if (std::regex_match(immediate, hexPattern))
			{
				try
				{
					int64_t value = std::stoll(immediate.substr(2), nullptr, 16);
					if (value < std::numeric_limits<TargetType>::min() || value > std::numeric_limits<TargetType>::max())
						throw std::runtime_error("The immediate exceeds the limits of the target word type. Value should be in range of " +
						std::to_string(std::numeric_limits<TargetType>::min()) + " - " +
						std::to_string(std::numeric_limits<TargetType>::max()) + " inclusive. Argument was \"" + immediate + "\" (" + std::to_string(value) + ")");

					return static_cast<TargetType>(value);
				}
				catch (const std::invalid_argument& argEx)
				{
					throw std::runtime_error("invlaid_argument thrown when trying to convert immediate to base ten int \"" + immediate +
						"\"\n>>>" + argEx.what());
				}
				catch (const std::out_of_range& rngEx)
				{
					throw std::runtime_error("out_of_range thrown when trying to convert immediate to base ten int \"" + immediate +
						"\". Your argument is way too big\n>>>" + rngEx.what());
				}
			}
			//Match '*' with character enclosed in single quotes
			else if (std::regex_match(immediate, asciiPattern))
			{
				return static_cast<TargetType>(immediate[1]);
			}
			//Did not match any expected argument types
			else
			{
				throw std::runtime_error("Unrecognized format for immediate \"" + immediate + "\". Expected formats are #d+, 0xd+, or '.'");
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
#endif // !ASMINSTRUCTION_H
