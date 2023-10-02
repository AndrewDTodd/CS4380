#ifndef ISA_4380_H
#define ISA_4380_H

#include "ISA.h"

#include <cstdint>

#include "Process_4380.h"

using namespace VMFramework;

class ISA_4380 : public ISA<int32_t, int32_t, Process_4380>
{
public:
	ISA_4380();
};
#endif //!ISA_4380_H
