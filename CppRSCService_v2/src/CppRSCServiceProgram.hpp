#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramBase.hpp"
#include "Arp/System/Commons/Logging.h"
#include "CppRSCServiceComponent.hpp"

namespace CppRSCService
{

using namespace Arp;
using namespace Arp::System::Commons::Diagnostics::Logging;
using namespace Arp::Plc::Commons::Esm;

//#program
//#component(CppRSCService::CppRSCServiceComponent)
class CppRSCServiceProgram : public ProgramBase, private Loggable<CppRSCServiceProgram>
{
public: // typedefs
	byte arrayWriter2[512];
	byte arrayReader2[512];

public: // construction/destruction
    CppRSCServiceProgram(CppRSCService::CppRSCServiceComponent& cppRSCServiceComponentArg, const String& name);
    CppRSCServiceProgram(const CppRSCServiceProgram& arg) = delete;
    virtual ~CppRSCServiceProgram() = default;

public: // operators
    CppRSCServiceProgram&  operator=(const CppRSCServiceProgram& arg) = delete;

public: // properties

public: // operations
    void    Execute() override;

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           boolean portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field.
        */

	//#port
	//#attributes(Input|Retain)
	//#name(OutBuffer)
	uint8 OutBuffer [512] = {0}; //The Port-Variable for the connection in PLCnext Engineer

	//#port
	//#attributes(Output|Retain)
	//#name(OUTDword)
	uint32 OUTDword = 0; //The Port-Variable for the connection in PLCnext Engineer

	//#port
	//#attributes(Input|Retain)
	//#name(InBuffer)
	uint8 InBuffer [512] = {0}; //The Port-Variable for the connection in PLCnext Engineer

	//#port
	//#attributes(Output|Retain)
	//#name(OUTstart)
	int32 OUTstart = 0; //The Port-Variable for the connection in PLCnext Engineer

	//#port
	//#attributes(Output|Retain)
	//#name(OUTstart)
	int32 OUTactive = 0; //The Port-Variable for the connection in PLCnext Engineer

	//#port
	//#attributes(Output|Retain)
	//#name(OUTstart)
	int32 OUTend = 0; //The Port-Variable for the connection in PLCnext Engineer

private: // fields
    CppRSCService::CppRSCServiceComponent& cppRSCServiceComponent;

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class ProgramBase
inline CppRSCServiceProgram::CppRSCServiceProgram(CppRSCService::CppRSCServiceComponent& cppRSCServiceComponentArg, const String& name)
: ProgramBase(name)
, cppRSCServiceComponent(cppRSCServiceComponentArg)
{
}

} // end of namespace CppRSCService
