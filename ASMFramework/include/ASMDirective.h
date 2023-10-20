#ifndef ASM_DIRECTIVE_H
#define ASM_DIRECTIVE_H

#include <string>
#include <stdexcept>

#include "Workpiece.h"

namespace ASMFramework
{
	struct ASMDirective
	{
	protected:
		ASMDirective(const std::string& mnemonic);

		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembly ASMDirective not yet implemented";
			}
		};

	public:
		const std::string _mnemonic;

		virtual void Implementation(const Workpiece* const& workpiece) const = 0;
	};
}
#endif // !ASM_DIRECTIVE_H
