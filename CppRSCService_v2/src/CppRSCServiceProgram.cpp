#include "CppRSCServiceProgram.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Core/ByteConverter.hpp"


namespace CppRSCService
{
 
void CppRSCServiceProgram::Execute()
{
    //implement program 
	memcpy(cppRSCServiceComponent.ports.InField, InBuffer, sizeof(InBuffer));
	memcpy(OutBuffer,cppRSCServiceComponent.ports.OutField, sizeof(OutBuffer));
	// = cppRSCServiceComponent.startTime
	OUTstart = cppRSCServiceComponent.ports.int64startTime2;
	OUTactive = cppRSCServiceComponent.ports.int64activeTime2;
	OUTend 		= cppRSCServiceComponent.ports.int64endTime2;
	//OutBuffer = cppRSCServiceComponent.arrayReader;

}

} // end of namespace CppRSCService
