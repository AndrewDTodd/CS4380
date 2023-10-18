#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include <string>
#include <stdexcept>

#include "Workpiece.h"

namespace ASMFramework
{
	struct Directive
	{
	protected:
		Directive(const std::string& mnemonic);

		class NotImplemented : public std::exception
		{
		public:
			const char* what() const noexcept override
			{
				return "Assembly Directive not yet implemented";
			}
		};

	public:
		const std::string _mnemonic;

		virtual void Implementation(const Workpiece* const& workpiece) const = 0;
	};
}
#endif // !DIRECTIVE_H
