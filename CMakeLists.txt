cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BrickDuino")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Source code
file(GLOB CPP_FILES Sources/*.cpp)

#include directories
SET(INCLUDE_DIR "Headers/")
SET(INCLUDE_DIR_EXCEPTION "Headers/Exception/")

# Adicione a origem ao executável deste projeto.
add_executable (BrickDuino ${CPP_FILES}) 

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BrickDuino PROPERTY CXX_STANDARD 20)
endif()

#include directories
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_EXCEPTION})

# libraries
target_link_libraries(BrickDuino PRIVATE Qt6::Widgets)
target_link_libraries(BrickDuino PRIVATE Qt6::Core)
target_link_libraries(BrickDuino PRIVATE Qt6::Gui)