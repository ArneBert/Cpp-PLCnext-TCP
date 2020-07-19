#include "CppRSCServiceLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "CppRSCServiceComponent.hpp"

namespace CppRSCService
{

CppRSCServiceLibrary::CppRSCServiceLibrary(AppDomain& appDomain)
    : MetaLibraryBase(appDomain, ARP_VERSION_CURRENT, typeDomain)
    , typeDomain(CommonTypeName<CppRSCServiceLibrary>().GetNamespace())
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::CppRSCService::CppRSCServiceComponent>(), &::CppRSCService::CppRSCServiceComponent::Create);
    this->InitializeTypeDomain();
}

void CppRSCServiceLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    CppRSCServiceLibrary::Main(appDomain);
    return  CppRSCServiceLibrary::GetInstance();
}

} // end of namespace CppRSCService
