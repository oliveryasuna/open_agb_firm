# CMake toolchain file for devkitARM (arm-none-eabi-gcc)

if(NOT DEFINED ENV{DEVKITARM})
    message(FATAL_ERROR "DEVKITARM is not set")
endif()

set(DEVKITARM $ENV{DEVKITARM})

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_OBJCOPY      "${DEVKITARM}/bin/arm-none-eabi-objcopy" CACHE FILEPATH "objcopy tool")
set(CMAKE_OBJDUMP      "${DEVKITARM}/bin/arm-none-eabi-objdump" CACHE FILEPATH "objdump tool")
set(CMAKE_SIZE         "${DEVKITARM}/bin/arm-none-eabi-size"    CACHE FILEPATH "size tool")
set(CMAKE_NM           "${DEVKITARM}/bin/arm-none-eabi-nm"      CACHE FILEPATH "nm tool")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH "${DEVKITARM}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
