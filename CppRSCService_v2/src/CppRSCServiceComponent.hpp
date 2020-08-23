#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppRSCServiceComponentProgramProvider.hpp"
#include "CppRSCServiceLibrary.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

#include "Arp/System/Acf/IControllerComponent.hpp"
#include "Arp/System/Commons/Threading/WorkerThread.hpp"
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Commons/Threading/ThreadSettings.hpp"

#include "Arp/System/Rsc/ServiceManager.hpp"
#include "Arp/Services/DataLogger/Services/IDataLoggerService.hpp"
#include "Arp/System/Rsc/Services/RscVariant.hxx"
#include "Arp/System/Rsc/Services/RscType.hpp"
#include "Arp/System/Rsc/Services/RscArrayReader.hpp"
#include "Arp/Services/DataLogger/Services/ErrorCode.hpp"
#include "Arp/Plc/Gds/Services/VariableInfo.hpp"

#include "Arp/Plc/Gds/Services/IDataAccessService.hpp"
#include "Arp/System/Commons/Net/Socket.hpp"

#include <mutex>
namespace CppRSCService
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

using namespace Arp::System::Rsc;
using namespace Arp::System::Rsc::Services;
using namespace Arp::Plc::Gds::Services;

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

using namespace Arp::System::Commons::Net;

//#component
class CppRSCServiceComponent
		: public ComponentBase
		, public ProgramComponentBase
		, private Loggable<CppRSCServiceComponent>
		, public IControllerComponent
{
public: // typedefs

public: // construction/destruction
    CppRSCServiceComponent(IApplication& application, const String& name);
    virtual ~CppRSCServiceComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // IControllerComponent operations
    void Start(void);
    void Stop(void);

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    CppRSCServiceComponent(const CppRSCServiceComponent& arg) = delete;
    CppRSCServiceComponent& operator= (const CppRSCServiceComponent& arg) = delete;

    void workerThreadBody(void);

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    CppRSCServiceComponentProgramProvider programProvider;

    //Worker Thread
           WorkerThread workerThreadInstance;

    //Start and End time as time window parameter

           /*
           Arp::DateTime startTime;
           Arp::DateTime endTime;
           Arp::DateTime activeTime;

           byte arrayReader[512];
           byte arrayWriter[512];

		   int64 int64startTime2;
		   int64 int64endTime2;
		   int64 int64activeTime2;

		   */


           bool xStopThread = false;

           std::shared_ptr<Socket> listeningSocket;
           std::shared_ptr<Socket> newSocket;


public: /* Ports
           =====
           Component ports are defined in the following way:

           //#attributes(Hidden)
           struct Ports 
           {
               //#name(NameOfPort)
               //#attributes(Input|Retain|Opc)
               Arp::boolean portField = false;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
           };
           
           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, there must be no other Component variables declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */

           	   //#attributes(Hidden)
               struct Ports
               {
					// Some Input Variables like TargetIP, Target Port, Start Connection, ect ect...

					//#name(In)
					//#attributes(Input)
					Arp::byte InField[512];
					//#name(ReadNext)
					//#attributes(Output)
					Arp::boolean CanReadNext = false; // Some other component will recieve this and send Values when true to InField.

					//#name(Start network)
					//#attributes(Input)
					Arp::boolean xtest = false;

					//#name(Out)
					//#attributes(Output)
					Arp::byte OutField[512];

					//#name(WriteNext)
					//#attributes(Input)
					Arp::boolean CanWriteNext = false; // Some other component will set this and recieve Values from true to OutField.

					//#name(starttime)
					//#attributes(Output)
					Arp::DateTime startTime;

					//#name(ActiveTime)
					//#attributes(Output)
					Arp::DateTime activeTime;

					//#name(Endtime)
					//#attributes(Output)
					Arp::DateTime endTime;

					//#name(Starttimeticks)
					//#attributes(Output)
					int64 int64startTime2;

					//#name(Activetimeticks)
					//#attributes(Output)
					int64 int64activeTime2;

					//#name(EndTimeticks)
					//#attributes(Output)
					int64 int64endTime2;

               };

               Ports ports;
};

inline IComponent::Ptr CppRSCServiceComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new CppRSCServiceComponent(application, name));
}

///////////////////////////////////////////////////////////////////////////////
inline CppRSCServiceComponent::CppRSCServiceComponent(IApplication& application, const String& name)
: ComponentBase(application, ::CppRSCService::CppRSCServiceLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::CppRSCService::CppRSCServiceLibrary::GetInstance().GetNamespace(), programProvider)


// ADDED: Worker Thread
, workerThreadInstance(make_delegate(this, &CppRSCServiceComponent::workerThreadBody), 100 , "WorkerThreadName")
 {
}
} // end of namespace CppRSCService
