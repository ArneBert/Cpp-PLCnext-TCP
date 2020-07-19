#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

namespace CppRSCService
{

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class CppRSCServiceComponent;

class CppRSCServiceComponentProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    CppRSCServiceComponentProgramProvider(CppRSCServiceComponent& cppRSCServiceComponentArg);
    virtual ~CppRSCServiceComponentProgramProvider() = default;

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

private:   // deleted methods
    CppRSCServiceComponentProgramProvider(const CppRSCServiceComponentProgramProvider& arg) = delete;
    CppRSCServiceComponentProgramProvider& operator=(const CppRSCServiceComponentProgramProvider& arg) = delete;

private: // fields
    CppRSCServiceComponent& cppRSCServiceComponent;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class CppRSCServiceComponentProgramProvider

inline CppRSCServiceComponentProgramProvider::CppRSCServiceComponentProgramProvider(CppRSCServiceComponent& cppRSCServiceComponentArg)
    : cppRSCServiceComponent(cppRSCServiceComponentArg)
{
}

} // end of namespace CppRSCService
