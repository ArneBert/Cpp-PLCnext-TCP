#include "CppRSCServiceProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"

namespace CppRSCService
{
 
void CppRSCServiceProgram::Execute()
{
    //implement program 
 // Something has to follow here, but I'm not quiet sure what.
 	 uint32 dword;
	 RscString<512> dwordstr;
	 dwordstr = "Arp.Plc.Eclr/main1.DW_IN1";

	 ReadSingle(dwordstr);

}

} // end of namespace CppRSCService
