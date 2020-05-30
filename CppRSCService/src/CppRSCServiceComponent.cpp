#include "CppRSCServiceComponent.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "CppRSCServiceLibrary.hpp"
#include "Arp/System/Commons/Net/Socket.hpp"
#include "Arp/System/Commons/Net/IpAddress.hpp"

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

	IRscReadEnumerator<RscVariant<512>>& readEnumerator;
	readEnumerator.BeginRead();
	RscVariant<512> currentVarriant;


	RscArrayReader arrayReader(currentVarriant);
    size_t arraySize = arrayReader.GetSize();   //Get the size of Array
    size_t r_offset = 0;                        //reinitialize the r_offset
    RscVariant<512> valueTmp = {0};             //reinitialize the valueTmp
	
	

	}
	
class TcpEchoServer
{
public:
    TcpEchoServer(void);
    void Process();
private:
    Socket listeningSocket;
};
inline TcpEchoServer::TcpEchoServer(void) : listeningSocket(SocketType::Tcp, SocketDomain::Ipv4, SocketBlockingMode::Blocking)
{}
void TcpEchoServer::Process()
{
    int port = 5000;
    // Bind the port to any local address.
    if (listeningSocket.Bind(0, port) != SocketError::None)
    {
        return;
    }
    // Make socket a passive listener that processes incoming connection requests.
    if (listeningSocket.Listen(10) != SocketError::None)
    {
        return;
    }

    //Other PLC adress is 192.168.1.105 
    uint32 remoteIp;
    //remotePort is 4000
    int remotePort;
    SocketError error;
    // Wait for the first client that requests a connection and accept it.
    Socket::Ptr newSocket = listeningSocket.Accept(remoteIp, remotePort, error);
    if (newSocket != nullptr)
    {
        byte buffer[512];
        // No receive any message and reply it directly to the sender.
        while (true)
        {
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = newSocket->Receive(buffer, sizeof(buffer), error);
            int sendResult = newSocket->Send(buffer, bytesReceived, error);
        }
        (void) newSocket->Shutdown();
        (void) newSocket->Close();
    }
}

} // end of namespace CppRSCService
