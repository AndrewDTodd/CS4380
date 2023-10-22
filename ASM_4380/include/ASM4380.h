#ifndef ASM_4380_H
#define ASM_4380_H

//#include "../../ASMFramework/include/Assembler.h"
//#include "../../ASMFramework/include/SingletonWrapper.h"
#include <Assembler.h>
#include <SingletonWrapper.h>
#include <Workpiece.h>

#include <gtest/gtest_prod.h>

#include "PassOne_Tokenization.h"
#include "PassTwo.h"
#include "PassThree.h"

#include "LanguageDefinition_4380.h"

class ASM4380 : public ASMFramework::Assembler, public ASMFramework::SingletonWrapper<ASM4380>
{
	friend class ASMFramework::SingletonWrapper<ASM4380>;

private:
	//Passes instantiation ****************************************************************
	PassOne_Tokenization _passOne;
	PassTwo _passTwo;
	PassThree _passThree;
	//*************************************************************************************

	//Workpiece instantiation *************************************************************
	ASMFramework::Workpiece _workpiece;
	//*************************************************************************************

	//LanguageDefinition instantiation ****************************************************
	LanguageDefinition_4380 _languageDef;
	//*************************************************************************************

protected:
	/// <summary>
	/// Constructor to make ASM4380 instance. Used by GetInstance inherited from SingletonWrapper. Not externally accessable
	/// </summary>
	ASM4380();

	/// <summary>
	/// Destructor for ASM4380, called by ShutDown
	/// </summary>
	~ASM4380();

public:
	void ShutDown() override;
};
#endif // !ASM_4380_H
