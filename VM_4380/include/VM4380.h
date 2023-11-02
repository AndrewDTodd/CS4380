#ifndef VM4380_H
#define VM4380_H

#include "../../VMFramework/include/Machine.h"

#include <cstdint>

#include <gtest/gtest_prod.h>

#include "ISA_4380.h"
#include "Process_4380.h"

class VM4380 : public VMFramework::Machine<VM4380, int32_t, Process_4380, ISA_4380>
{
private:
	/// <summary>
	/// Create a new process to execute starting at the specified program location
	/// </summary>
	/// <param name="startInstruction">Pointer to the location in the program where this process should begin execution</param>
	void SpawnProcess(const int32_t& initialPC) override;

	/// <summary>
	/// Defines the logic for determining the entry point of a program in the ISA4380 architecture
	/// </summary>
	/// <returns>Pointer to the byte in the program segment to start executing at</returns>
	int32_t CalculatePrimaryThreadInitPC() override;

	FRIEND_TEST(VM4380Testing, Validate_StartUp);
	FRIEND_TEST(VM4380Testing, Validate_ShutDown);
	FRIEND_TEST(VM4380Testing, Validate_LoadProgram);
	FRIEND_TEST(VM4380Testing, Validate_SpawnProcess);
};
#endif //!VM4380_H
