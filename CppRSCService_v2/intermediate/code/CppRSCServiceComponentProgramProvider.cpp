#include "CppRSCServiceComponentProgramProvider.hpp"
#include "CppRSCServiceProgram.hpp"

namespace CppRSCService
{

IProgram::Ptr CppRSCServiceComponentProgramProvider::CreateProgramInternal(const String& programName, const String& programType)
{
    if (programType == "CppRSCServiceProgram")
    { 
        return std::make_shared<::CppRSCService::CppRSCServiceProgram>(this->cppRSCServiceComponent, programName);
    }

    // else unknown program
    return nullptr;
}

} // end of namespace CppRSCService
