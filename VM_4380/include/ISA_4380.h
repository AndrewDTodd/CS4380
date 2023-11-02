#ifndef ISA_4380_H
#define ISA_4380_H

#include "ISA.h"

#include <cstdint>

class Process_4380;

class ISA_4380 : public VMFramework::ISA<int32_t, Process_4380>
{
public:
	ISA_4380();
};
#endif //!ISA_4380_H
