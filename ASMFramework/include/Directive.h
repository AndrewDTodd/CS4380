#ifndef DIRECTIVE_H
#define DIRECTIVE_H

#include <string>

#include "Workpiece.h"
#include "SingletonWrapper.h"

namespace ASMFramework
{
	struct Directive
	{
	protected:
		Directive(const std::string& mnemonic);

	public:
		const std::string _mnemonic;

		virtual void Implementation(Workpiece* workpiece) = 0;
	};
}
#endif // !DIRECTIVE_H
