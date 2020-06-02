#include "CppRSCServiceComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppRSCServiceLibrary.hpp"


namespace CppRSCService
{

CppRSCServiceComponent::CppRSCServiceComponent(IApplication& application, const String& name)
: ComponentBase(application, ::CppRSCService::CppRSCServiceLibrary::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::CppRSCService::CppRSCServiceLibrary::GetInstance().GetNamespace(), programProvider)
{
}

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

/// Thread Body

void CppRSCServiceComponent::workerThreadBody(void) {
		   endTime = Arp::DateTime::Now(); //The time window includes records between two worker thread cycles

			startTime = endTime;  		  	//The time window includes records between two worker thread cycles

//	IRscReadEnumerator<RscVariant<512>>& readEnumerator;
//	readEnumerator.BeginRead();
//	RscVariant<512> currentVarriant;
//
//
//	RscArrayReader arrayReader(currentVarriant);
//    size_t arraySize = arrayReader.GetSize();   //Get the size of Array
//    size_t r_offset = 0;                        //reinitialize the r_offset
//    RscVariant<512> valueTmp = {0};             //reinitialize the valueTmp

    	int port = 5000;
    	byte arrayReader[512];
    	std::size_t i;
		for (i = 0; i < sizeof(arrayReader); ++i) {
			arrayReader[i] =8;
		}
    	byte arrayWriter[512];
    	// Bind the port to any local address.

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
        IpAddress::IpV4Value test = 3232235881;
        //remotePort is 4000
        int remotePort = 4000;
        SocketError error;
        // Wait for the first client that requests a connection and accept it.

        Socket::Ptr newSocket;
        newSocket = listeningSocket -> Accept(test,remotePort , error);
        if (newSocket != nullptr)
        {
            byte buffer[512];
            // No receive any message and reply it directly to the sender.
            while (true)
            {
                //arrayReader is a byte array of 512 bytes.
                //memset(buffer, 0, sizeof(buffer));
                memcpy(buffer,arrayReader, sizeof(buffer));
                int bytesReceived = newSocket->Receive(buffer, sizeof(buffer), error);
                int sendResult = newSocket->Send(buffer, sizeof(buffer), error);
                //arrayWriter is a byte array of 512 bytes.
                memcpy(arrayWriter, buffer, sizeof(buffer));
            }
            (void) newSocket->Shutdown();
            (void) newSocket->Close();
        }


	}

} // end of namespace CppRSCService
