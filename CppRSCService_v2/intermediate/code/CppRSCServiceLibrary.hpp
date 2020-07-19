#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeDomain.hpp"

namespace CppRSCService
{

using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;
using namespace Arp::Plc::Commons::Meta::TypeSystem;

class CppRSCServiceLibrary : public MetaLibraryBase, public Singleton<CppRSCServiceLibrary>
{
public: // typedefs
    typedef Singleton<CppRSCServiceLibrary> SingletonBase;

public: // construction/destruction
    CppRSCServiceLibrary(AppDomain& appDomain);
    virtual ~CppRSCServiceLibrary() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // methods
    void InitializeTypeDomain();

private: // deleted methods
    CppRSCServiceLibrary(const CppRSCServiceLibrary& arg) = delete;
    CppRSCServiceLibrary& operator= (const CppRSCServiceLibrary& arg) = delete;

private:  // fields
    TypeDomain typeDomain;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppRSCServiceLibrary

} // end of namespace CppRSCService
