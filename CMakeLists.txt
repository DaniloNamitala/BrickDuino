cmake_minimum_required (VERSION 3.0)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("BrickDuino")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Source code
file(GLOB MAIN_CPP_FILES Sources/*.cpp)
file(GLOB BRICK_T_CPP_FILES Sources/Brick/Toolbox/*.cpp)
file(GLOB BRICK_W_CPP_FILES Sources/Brick/Workspace/*.cpp)
file(GLOB BRICK_CPP_FILES Sources/Brick/*.cpp)
file(GLOB PAINTER_CPP_FILES Sources/Painter/*.cpp)
file(GLOB TOOLBOX_CPP_FILES Sources/Toolbox/*.cpp)
file(GLOB SCREENS_CPP_FILES Sources/Screens/*.cpp)

#include directories
SET(INCLUDE_DIR "Headers/")
SET(INCLUDE_DIR_EXCEPTION "Headers/Exception/")
SET(INCLUDE_DIR_BRICK_R "Headers/Brick/")
SET(INCLUDE_DIR_BRICK_T "Headers/Brick/Toolbox")
SET(INCLUDE_DIR_BRICK_W "Headers/Brick/Workspace")
SET(INCLUDE_DIR_PAINTER "Headers/Painter/")
SET(INCLUDE_DIR_TOOLBOX "Headers/Toolbox/")
SET(INCLUDE_DIR_SCREENS "Headers/Screens/")

# Adicione a origem ao executável deste projeto.
add_executable (BrickDuino 
  ${MAIN_CPP_FILES} 
  ${TOOLBOX_CPP_FILES} 
  ${PAINTER_CPP_FILES} 
  ${SCREENS_CPP_FILES} 
  ${BRICK_CPP_FILES} 
  ${BRICK_T_CPP_FILES} 
  ${BRICK_W_CPP_FILES}
)  

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BrickDuino PROPERTY CXX_STANDARD 20)
endif()

#include directories
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_EXCEPTION})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_BRICK_T})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_BRICK_W})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_BRICK_R})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_PAINTER})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_TOOLBOX})
target_include_directories(BrickDuino PUBLIC ${INCLUDE_DIR_SCREENS})

# libraries
target_link_libraries(BrickDuino PRIVATE Qt6::Widgets)
target_link_libraries(BrickDuino PRIVATE Qt6::Core)
target_link_libraries(BrickDuino PRIVATE Qt6::Gui)