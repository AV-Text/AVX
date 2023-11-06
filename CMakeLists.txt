cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AVXSearch CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)
include_directories("C:/src/AVX/AVXSearch")
include_directories("C:/src/AVX/AVXText")
include_directories("C:/src/AVX/AVXText/foundations")
include_directories("C:/src/AVX/AVXText/xvmem")
include_directories("C:/src/blueprint-blue/Blueprint-Blue-Lib")
include_directories("C:/tool/flatbuffers/include")

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################


set(PROJECT_NAME AVXSearch)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "AVXSearch/AVXBlueprint.h"
    "AVXSearch/AVXComparator.h"
    "AVXSearch/AVXDeltaComparator.h"
    "AVXSearch/AVXFind.h"
    "AVXSearch/AVXFound.h"
    "AVXSearch/AVXFragment.h"
    "AVXSearch/AVXLemmaComparator.h"
    "AVXSearch/AVXMatch.h"
    "AVXSearch/AVXPOS16Comparator.h"
    "AVXSearch/AVXPOS32Comparator.h"
    "AVXSearch/AVXPuncComparator.h"
    "AVXSearch/AVXResult.h"
    "AVXSearch/AVXSearch.h"
    "AVXSearch/AVXSegment.h"
    "AVXSearch/AVXStatement.h"
    "AVXSearch/AVXStrongsComparator.h"
    "AVXSearch/AVXTransitionComparator.h"
    "AVXSearch/AVXWordComparator.h"

    "AVXText/directory.h"
    "AVXText/Feature.h"
    "AVXText/FeatureSpec.h"
    "AVXText/fivebitencoding.h"
    "AVXText/md5.h"
    "AVXText/SearchClause.h"
    "AVXText/SearchControls.h"
    "AVXText/SearchFragment.h"
    "AVXText/SearchRequest.h"
    "AVXText/slicable.h"
    "AVXText/XBitArray.h"

    "AVXText/DigitalAV.h"

    "AVXText/foundations/avxgen.h"
    "AVXText/foundations/book.h"
    "AVXText/foundations/chapter.h"
    "AVXText/foundations/framework.h"
    "AVXText/foundations/lemmata.h"
    "AVXText/foundations/lexicon.h"
    "AVXText/foundations/names.h"
    "AVXText/foundations/oov_lemmata.h"
    "AVXText/foundations/written.h"

    "AVXText/xvmem/XVMem.h"
    "AVXText/xvmem/XVMem_platform.h"
    "AVXText/xvmem/XVMem_windows.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "AVXSearch/AVXBlueprint.cpp"
    "AVXSearch/AVXDeltaComparator.cpp"
    "AVXSearch/AVXFind.cpp"
    "AVXSearch/AVXFound.cpp"
    "AVXSearch/AVXFragment.cpp"
    "AVXSearch/AVXLemmaComparator.cpp"
    "AVXSearch/AVXMatch.cpp"
    "AVXSearch/AVXPOS16Comparator.cpp"
    "AVXSearch/AVXPOS32Comparator.cpp"
    "AVXSearch/AVXPuncComparator.cpp"
    "AVXSearch/AVXResult.cpp"
    "AVXSearch/AVXSearch.cpp"
    "AVXSearch/AVXSegment.cpp"
    "AVXSearch/AVXStatement.cpp"
    "AVXSearch/AVXStrongsComparator.cpp"
    "AVXSearch/AVXTransitionComparator.cpp"
    "AVXSearch/AVXWordComparator.cpp"

    "AVXText/directory.cpp"
    "AVXText/fivebitencoding.cpp"
    "AVXText/md5.cpp"
    "AVXText/search.cpp"
    "AVXText/slicable.cpp"
    "AVXText/XBitArray.cpp"

    "AVXText/DigitalAV.cpp"

    "AVXText/foundations/book.cpp"
    "AVXText/foundations/lemmata.cpp"
    "AVXText/foundations/lexicon.cpp"
    "AVXText/foundations/names.cpp"
    "AVXText/foundations/oov_lemmata.cpp"

    "AVXText/xvmem/XVMem_windows.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE AVXSearch)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "AVXSEARCH_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "AVXSEARCH_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()