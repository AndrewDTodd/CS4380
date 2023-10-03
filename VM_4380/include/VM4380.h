#ifndef VM4380_H
#define VM4380_H

#include "../../VMFramework/include/Machine.h"

#include <cstdint>

#include "ISA_4380.h"
#include "Process_4380.h"

using namespace VMFramework;

class VM4380 : public Machine<VM4380, int32_t, int32_t, Process_4380, ISA_4380>
{
private:
	/// <summary>
	/// Create a new process to execute starting at the specified program location
	/// </summary>
	/// <param name="startInstruction">Pointer to the location in the program where this process should begin execution</param>
	void SpawnProcess(void* initialPC) override;
};
#endif //!VM4380_H
