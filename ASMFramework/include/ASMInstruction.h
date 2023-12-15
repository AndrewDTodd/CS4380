#ifndef ASM_INSTRUCTION_H
#define ASM_INSTRUCTION_H

#include <string>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <concepts>
#include <regex>

#include "Workpiece.h"
#include "LanguageDefinition.h"

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
		static const std::regex asciiEscape;

		/// <summary>
		/// Gets the offset of the provided label name
		/// </summary>
		/// <param name="labelName">The name of the label to get the offset of</param>
		/// <param name="workpiece">The Workpiece instance being worked upon. Containes the relevent symbol table with the lebel in it</param>
		/// <returns>The offset for the label as contained in the symbol table. Will be 0 for a label whos offset has not yet been determined</returns>
		static inline size_t& GetLabelOffset(const std::string& labelName, Workpiece* const& workpiece)
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

		/// <summary>
		/// Add an unresolved label to the workpieces set of deferred labels
		/// </summary>
		/// <typeparam name="TargetType">The type of the last item serialized to the buffer. Used to get propper offset. The offset is the types size in bytes subtracted from the buffer size</typeparam>
		/// <param name="labelName">The name of the label that is being deferred</param>
		/// <param name="buffer">The buffer that was just serialized too, where the deferred label was just written</param>
		/// <param name="workpiece">The Workpiece instance being worked upon. Contains the relevant deferred label collection</param>
		template<std::integral TargetType>
		static inline void AddUnresolvedLabel(const std::string& labelName, std::vector<uint8_t>& buffer, Workpiece* const& workpiece)
		{
			size_t buffOffset = buffer.size() - sizeof(TargetType);

			workpiece->_unresolvedLabels[labelName].push_back({ &buffer, buffOffset });
			//workpiece->_unresolvedLabels[labelName].push_back(reinterpret_cast<void*>(buffer.data() + buffOffset));
		}

		/// <summary>
		/// Serializes the list of parameters to the provided buffer
		/// </summary>
		/// <typeparam name="TargetType">The type that the parameters should be represented/converted too then put in the buffer</typeparam>
		/// <typeparam name="...InputType">The types of the parameters that are going to be serialized to the buffer</typeparam>
		/// <param name="buffer">The byte buffer to serialize into</param>
		/// <param name="...value">Parameter pack of all the items to serialize</param>
		template<std::integral TargetType, std::integral... InputType>
		static inline void SerializeToBuffer(std::vector<uint8_t>& buffer, const InputType&... value)
		{
			if constexpr (is_little_endian)
			{
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

		/*template<std::integral TargetType>
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
		}*/

		/// <summary>
		/// Gets the numeric value represented by the supported formated string
		/// </summary>
		/// <typeparam name="TargetType">The numeric type that the value is to be represented as when returned</typeparam>
		/// <param name="immediate">The formated strign representing a numeric value</param>
		/// <returns>The value represented in the type defined by the TargetType template parameter</returns>
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
					if (immediate[0] == '-')
					{
						long long value = std::stoll(immediate, nullptr, 16);

						if (value < std::numeric_limits<TargetType>::min() || value > std::numeric_limits<TargetType>::max())
							throw std::runtime_error("The immediate exceeds the limits of the target word type. Value should be in range of " +
								std::to_string(std::numeric_limits<TargetType>::min()) + " - " +
								std::to_string(std::numeric_limits<TargetType>::max()) + " inclusive. Argument was \"" + immediate + "\" (" + std::to_string(value) + ")");

						return static_cast<TargetType>(value);
					}
					else
					{
						using UnsignedTargetType = typename std::make_unsigned<TargetType>::type;
						unsigned long long unsignedValue = std::stoull(immediate, nullptr, 16);

						if (unsignedValue > std::numeric_limits<UnsignedTargetType>::max())
							throw std::out_of_range("");

						return static_cast<TargetType>(unsignedValue);
					}
				}
				catch (const std::out_of_range& rngEx)
				{
					throw std::runtime_error("out_of_range thrown when trying to convert immediate to base ten int \"" + immediate +
						"\"\n>>>" + rngEx.what());
				}
			}
			//Match '*' with character enclosed in single quotes
			else if (std::regex_match(immediate, asciiPattern))
			{
				return static_cast<TargetType>(immediate[1]);
			}
			else if (std::regex_match(immediate, asciiEscape))
			{
				if (immediate[2] == 'n')
				{
					return static_cast<TargetType>('\n');
				}
				else if (immediate[2] == 't')
				{
					return static_cast<TargetType>('\t');
				}
				else
					throw std::runtime_error("Unsupported escape sequence \"" + immediate + "\". Supported sequences are \\n and \\t");

				return sizeof(uint8_t);
			}
			//Did not match any expected argument types
			else
			{
				throw std::runtime_error("Unrecognized format for immediate \"" + immediate + "\". Expected formats are #d+, 0xd+,'.', or '\\.'");
			}
		}

		/// <summary>
		/// Used internally by the CheckRegisterIDWarning method to make a string with the register ids that will trigger a warning
		/// </summary>
		/// <typeparam name="...WarnRegisterIDs">A collection of the register IDs that are to trigger a warning in the calling context</typeparam>
		/// <returns>A string with the registers that trigger a warning</returns>
		template<uint8_t... WarnRegisterIDs>
		inline std::string Warning_MakeStringFlagedRegisters() const
		{
			std::ostringstream oss;
			((oss << ", R" << WarnRegisterIDs), ...);
			return oss.str();
		}

		/// <summary>
		/// Used internally by the CheckRegisterIDInvalid method to make a string with the invalid register ids
		/// </summary>
		/// <typeparam name="...InvalidRegisterIDs">A collection of the register IDs that are invalid in the calling context</typeparam>
		/// <returns>A string with the registers that are invalid</returns>
		template<uint8_t... InvalidRegisterIDs>
		inline std::string Exeption_MakeStringInvalidRegisters() const
		{
			std::ostringstream oss;
			((oss << ", R" << InvalidRegisterIDs), ...);
			return oss.str();
		}

		/// <summary>
		/// Called by an Assember INS to verify the provided register id and throw an exeption if it is invalid in the calling context
		/// </summary>
		/// <typeparam name="RegisterType">The type used for the register id to be validated</typeparam>
		/// <typeparam name="...InvalidRegisterIDs">A collection of the register IDs that are to be considered invalid in the calling context</typeparam>
		/// <param name="id">The register id to verify</param>
		template<std::integral RegisterType, uint8_t... InvalidRegisterIDs>
		inline void CheckRegisterIDInvalid(const RegisterType& id) const
		{
			((id == InvalidRegisterIDs ? throw std::runtime_error("You may not set the value of special registers this way." + Exeption_MakeStringInvalidRegisters<InvalidRegisterIDs>()) : void()), ...);
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

		class Warning : public std::exception
		{
		private:
			const std::string message;
		public:
			size_t returnVal;

			Warning(std::string&& msg, size_t&& rtrnVal): message(msg), returnVal(rtrnVal)
			{}

			const char* what() const noexcept override
			{
				return message.c_str();
			}
		};

		const std::string _mnemonic;

		/// <summary>
		/// Called by passes to preform the instructions work on the workpiece
		/// </summary>
		/// <param name="buffer">The byte buffer presently being written too</param>
		/// <param name="workpiece">The Workpiece instance to be worked upon</param>
		/// <param name="langDef">Pointer to the LanguageDefinition for the assembler</param>
		/// <param name="args">Collection of possible arguments that were tokenized for the instruction</param>
		/// <returns>The number of bytes written to the buffer</returns>
		/// <exception cref="std::runtime_error Thrown by the instruction if the operation cannot be completed properly"/>
		/// <exception cref="ASMInstruction::NotImplemented Thrown by the instruction to signify that its tooling is not implemented, and therefore the instruction is unsupported at this time"/>
		/// <exception cref="ASMInstruction::Warning Thrown by the instruciton if a condition is met that warrants a warning to the user, but not a failure of the assembly process. Will return the number of bytes written to the buffer allong with the warning message"/>
		virtual size_t Implementation(std::vector<uint8_t>& buffer, Workpiece* const& workpiece, const LanguageDefinition* const& langDef, const std::vector<std::string>& args) const = 0;

		/// <summary>
		/// Called by an Assember INS to check the provided register id against those that should trigger a warning in the calling context
		/// </summary>
		/// <typeparam name="RegisterType">The type used for the register id to be validated</typeparam>
		/// <typeparam name="...WarnRegisterIDs">A collection of the register IDs that should trigger a warning in the calling context</typeparam>
		/// <param name="id">The register id to check</param>
		template<std::integral RegisterType, uint8_t... WarnRegisterIDs>
		inline void CheckRegisterIDWarning(const RegisterType& id, size_t&& bytesWritten) const
		{
			((id == WarnRegisterIDs ? throw Warning("R" + std::to_string(id) + "is considered dangerouse to use in this context. The following registers will cause this warning in this context" + Warning_MakeStringFlagedRegisters<WarnRegisterIDs>(), bytesWritten) : void()), ...);
		}
	};
}
#endif // !ASMINSTRUCTION_H
