#ifndef ASM_4380_H
#define ASM_4380_H

#include <cstdint>

#include <Assembler.h>
#include <SingletonWrapper.h>
#include <Workpiece.h>

#include <gtest/gtest_prod.h>

#include "PassOne_Tokenization.h"
#include "PassTwo_Assemble.h"
#include "PassThree_Serialize.h"

#include "LanguageDefinition_4380.h"

class ASM4380 : public ASMFramework::Assembler, public ASMFramework::SingletonWrapper<ASM4380>
{
	friend class ASMFramework::SingletonWrapper<ASM4380>;

private:
	//Passes instantiation ****************************************************************
	PassOne_Tokenization _passOne;
	PassTwo_Assemble _passTwo;
	PassThree_Serialize _passThree;
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

	void ProcessASM(const char* assemblyPath) override;
};
#endif // !ASM_4380_H
