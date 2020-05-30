#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
#include "CppRSCServiceProgram.hpp"
#include "CppRSCServiceLibrary.hpp"

namespace CppRSCService
{

using namespace Arp::Plc::Commons::Meta;

    void CppRSCServiceLibrary::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
                {   // ProgramDefinition: CppRSCService::CppRSCServiceProgram
                    DataType::Program, CTN<CppRSCService::CppRSCServiceProgram>(), sizeof(::CppRSCService::CppRSCServiceProgram), alignof(::CppRSCService::CppRSCServiceProgram), StandardAttribute::None,
                    {
                        // FieldDefinitions:
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace CppRSCService

