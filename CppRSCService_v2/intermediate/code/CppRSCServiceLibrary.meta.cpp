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
                        { "OutBuffer", offsetof(::CppRSCService::CppRSCServiceProgram, OutBuffer), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 512 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "OUTDword", offsetof(::CppRSCService::CppRSCServiceProgram, OUTDword), DataType::UInt32, "", sizeof(uint32), alignof(uint32), {  }, StandardAttribute::Output | StandardAttribute::Retain },
                        { "InBuffer", offsetof(::CppRSCService::CppRSCServiceProgram, InBuffer), DataType::UInt8 | DataType::Array, "", sizeof(uint8), alignof(uint8), { 512 }, StandardAttribute::Input | StandardAttribute::Retain },
                        { "OUTstart", offsetof(::CppRSCService::CppRSCServiceProgram, OUTstart), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Output | StandardAttribute::Retain },
                        { "OUTstart", offsetof(::CppRSCService::CppRSCServiceProgram, OUTactive), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Output | StandardAttribute::Retain },
                        { "OUTstart", offsetof(::CppRSCService::CppRSCServiceProgram, OUTend), DataType::Int32, "", sizeof(int32), alignof(int32), {  }, StandardAttribute::Output | StandardAttribute::Retain },
                    }
                },
            }
            // End TypeDefinitions
        );
    }

} // end of namespace CppRSCService

