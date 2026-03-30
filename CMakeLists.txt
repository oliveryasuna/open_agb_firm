cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(open_agb_firm LANGUAGES C CXX ASM)

set(TARGET "open_agb_firm")

option(NO_DEBUG "Disable debug features (enables NDEBUG, LTO)" OFF)
option(USE_FIRMTOOL "Use firmtool instead of firm_builder" OFF)

##==================================================
## Version from git tags
##==================================================

execute_process(
    COMMAND git describe --tags --match v[0-9]* --abbrev=8
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_DESCRIBE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

if(GIT_DESCRIBE)
    # Strip trailing -<count>-g prefix to get e.g. "v1.0-abcdef12"
    string(REGEX REPLACE "-[0-9]+-g" "-" VERS_STRING "${GIT_DESCRIBE}")
    string(REGEX MATCH "^v([0-9]+)" _match "${GIT_DESCRIBE}")
    set(VERS_MAJOR "${CMAKE_MATCH_1}")
    string(REGEX MATCH "\\.([0-9]+)" _match "${GIT_DESCRIBE}")
    set(VERS_MINOR "${CMAKE_MATCH_1}")
else()
    set(VERS_STRING "unknown")
    set(VERS_MAJOR 0)
    set(VERS_MINOR 0)
endif()

message(STATUS "Version: ${VERS_STRING} (${VERS_MAJOR}.${VERS_MINOR})")

add_subdirectory(arm9)
add_subdirectory(arm11)

##==================================================
## Firmware constants
##==================================================

set(ENTRY9       "0x08000040")
set(ENTRY11      "0x1FF89034")
set(SECTION0_ADR "0x08000040")
set(SECTION1_ADR "0x1FF89000")

##==================================================
## Firmware assembly
##==================================================

if(USE_FIRMTOOL)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/${TARGET}.firm
        COMMAND firmtool build ${CMAKE_BINARY_DIR}/${TARGET}.firm
            -n ${ENTRY9} -e ${ENTRY11}
            -A ${SECTION0_ADR} ${SECTION1_ADR}
            -D ${ARM9_BIN} ${ARM11_BIN}
            -C NDMA XDMA
        DEPENDS ${TARGET}9 ${TARGET}11
        COMMENT "Building ${TARGET}.firm (firmtool)"
    )
else()
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/${TARGET}.firm
        COMMAND firm_builder ${CMAKE_BINARY_DIR}/${TARGET}.firm
            ${ENTRY9} ${ENTRY11}
            ${SECTION0_ADR} 0 ${ARM9_BIN}
            ${SECTION1_ADR} 1 ${ARM11_BIN}
        DEPENDS ${TARGET}9 ${TARGET}11
        COMMENT "Building ${TARGET}.firm (firm_builder)"
    )
endif()

add_custom_target(firmware ALL
    DEPENDS ${CMAKE_BINARY_DIR}/${TARGET}.firm
)
