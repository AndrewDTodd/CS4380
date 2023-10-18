#ifndef ASM_4380_H
#define ASM_4380_H

//#include "../../ASMFramework/include/Assembler.h"
//#include "../../ASMFramework/include/SingletonWrapper.h"
#include <Assembler.h>
#include <SingletonWrapper.h>

#include <gtest/gtest_prod.h>

using namespace ASMFramework;

class ASM4380 : public Assembler, public SingletonWrapper<ASM4380>
{
protected:
	/// <summary>
	/// Constructor to make ASM4380 instance. Used by GetInstance inherited from SingletonWrapper. Not externally accessable
	/// </summary>
	ASM4380();

public:
	/// <summary>
	/// Destructor for ASM4380
	/// </summary>
	~ASM4380();
};
#endif // !ASM_4380_H
