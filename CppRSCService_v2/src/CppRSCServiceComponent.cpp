#include "CppRSCServiceComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppRSCServiceLibrary.hpp"


namespace CppRSCService
{

//CppRSCServiceComponent::CppRSCServiceComponent(IApplication& application, const String& name)
//: ComponentBase(application, ::CppRSCService::CppRSCServiceLibrary::GetInstance(), name, ComponentCategory::Custom)
//, programProvider(*this)
//, ProgramComponentBase(::CppRSCService::CppRSCServiceLibrary::GetInstance().GetNamespace(), programProvider)
//{
//}

void CppRSCServiceComponent::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void CppRSCServiceComponent::LoadConfig()
{
    // load project config here
}

void CppRSCServiceComponent::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
    listeningSocket = std::make_shared<Socket>(SocketType::Tcp, SocketDomain::Ipv4, SocketBlockingMode::Blocking);

}

void CppRSCServiceComponent::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void CppRSCServiceComponent::Start()
{
	xStopThread = false;
		Log::Info("-------------------------------workerThreadInstance start");
		workerThreadInstance.Start();
		Log::Info("-------------------------------workerThreadInstance started");
}

void CppRSCServiceComponent::Stop()
{
	// if you want to stop some loops of your thread during execution
	// add something like "stoptheThread" before executing workerThreadStop.
	xStopThread = true;
	Log::Info("-------------------------------workerThreadInstance stop");
	workerThreadInstance.Stop();
	Log::Info("-------------------------------workerThreadInstance stopped");
}

/// Thread Body

void CppRSCServiceComponent::workerThreadBody(void) {
	ports.startTime = Arp::DateTime::Now(); //The time window includes records between two worker thread cycles

		   int port = 5000;
	    	//byte arrayReader[512];
	    	//byte arrayWriter[512];
	    	std::size_t i;



			for (i = 0; i < sizeof(ports.InField); ++i) {
				ports.OutField[i] =8;
				ports.InField[i] =8;
			}


		   if(ports.xtest)
		   	{
			   if (listeningSocket -> Bind(0,port) != SocketError::None)
			           {
			               return;
			           }
			           // Make socket a passive listener that processes incoming connection requests.
			           if (listeningSocket -> Listen(10) != SocketError::None)
			           {
			               return;
			           }

			           //Other PLC IP-adress is 192.168.1.105
			           //uint32 remoteIp = 3232235881;
			           IpAddress test = 3232235881;
			           //remotePort is 4000
			           int remotePort = 4000;
			           SocketError error;
			           // Wait for the first client that requests a connection and accept it.

			           Socket::Ptr newSocket;
			           newSocket = listeningSocket -> Accept(test,remotePort , error);
			           if (newSocket != nullptr)
			           {
			        	   ports.activeTime = Arp::DateTime::Now();
			               byte buffer[512];
			               // No receive any message and reply it directly to the sender.
			               while (true)
			               {
			                   //arrayReader is a byte array of 512 bytes.

			                   int bytesReceived = newSocket->Receive(buffer, sizeof(buffer), error);
			                   memcpy(buffer,ports.OutField, sizeof(buffer));
			                   memcpy(ports.InField, buffer, sizeof(buffer));

			                   int sendResult = newSocket->Send(buffer, sizeof(buffer), error);
			                   //arrayWriter is a byte array of 512 bytes.

			               }
			               (void) newSocket->Shutdown();
			               (void) newSocket->Close();
			               ports.endTime = Arp::DateTime::Now();
			           }

			           ports.int64startTime2 = ports.startTime.GetTicks();
				   ports.int64activeTime2 = ports.activeTime.GetTicks();
			           ports.int64endTime2 = ports.endTime.GetTicks();

			           Thread::Sleep(1000);

					  //uint32 elapsed_time = endTime - startTime;
		   	}
		   	else
		   	{
		   		(void) newSocket->Close();
		   	}

	}

} // end of namespace CppRSCService
