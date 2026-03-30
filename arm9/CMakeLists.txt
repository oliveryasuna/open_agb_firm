# ARM9 target (ARMv5TE / ARM946E-S)

set_property(SOURCE
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/memory.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/cache.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/exception.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/lgy7_code.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/start.s
    APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp"
)

set(ARM9_ARCH_FLAGS
    -march=armv5te
    -mtune=arm946e-s
    -mfloat-abi=soft
    -mtp=soft
    -marm
    -mthumb-interwork
    -masm-syntax-unified
)

##==================================================
## Sources
##==================================================

set(ARM9_PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/source/arm9/main.c
)

set(ARM9_LIBN3DS_SHARED_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/drivers/corelink_dma-330.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/drivers/mmc/sdmmc.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/drivers/pxi.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/drivers/sha.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/drivers/tmio.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/error_codes.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/fsutil.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/memory.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/util.c
)

set(ARM9_LIBN3DS_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/debug.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/cache.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/exception.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/hid.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/interrupt.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/lgy9.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/ndma.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/prng.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/spicard.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/drivers/timer.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/fatfs/diskio.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/fatfs/ffsystem.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/fs.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/ipc_handler.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/lgy7_code.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/start.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/system.c
)

set(ARM9_FATFS_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/libraries/fatfs/source/ff.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/libraries/fatfs/source/ffunicode.c
)

##==================================================
## Target
##==================================================

add_executable(${TARGET}9
    ${ARM9_PROJECT_SOURCES}
    ${ARM9_LIBN3DS_SHARED_SOURCES}
    ${ARM9_LIBN3DS_SOURCES}
    ${ARM9_FATFS_SOURCES}
)

target_include_directories(${TARGET}9 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/include
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/libraries
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/fatfs
)

target_compile_definitions(${TARGET}9 PRIVATE
    __ARM9__
    __3DS__
    LIBN3DS_LEGACY=1
    VERS_STRING="${VERS_STRING}"
    VERS_MAJOR=${VERS_MAJOR}
    VERS_MINOR=${VERS_MINOR}
    $<$<BOOL:${NO_DEBUG}>:NDEBUG>
)

##==================================================
## Compile flags
##==================================================

set(ARM9_COMMON_C_FLAGS
    ${ARM9_ARCH_FLAGS}
    -O2
    -gdwarf-4
    -mword-relocations
    -ffunction-sections
    -Wall
    -Wextra
)

if(NO_DEBUG)
    set(ARM9_C_FLAGS ${ARM9_COMMON_C_FLAGS} -flto)
    set(ARM9_ASM_FLAGS ${ARM9_ARCH_FLAGS} -gdwarf-4 -flto)
else()
    set(ARM9_C_FLAGS ${ARM9_COMMON_C_FLAGS} -fstack-protector-strong -fno-inline)
    set(ARM9_ASM_FLAGS ${ARM9_ARCH_FLAGS} -gdwarf-4)
endif()

target_compile_options(${TARGET}9 PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=c23>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++23 -fno-rtti -fno-exceptions>
    $<$<COMPILE_LANGUAGE:ASM>:${ARM9_ASM_FLAGS}>
    $<$<COMPILE_LANGUAGE:C,CXX>:${ARM9_C_FLAGS}>
)

##==================================================
## Link flags
##==================================================

set(ARM9_COMMON_LINK_FLAGS
    ${ARM9_ARCH_FLAGS}
    -gdwarf-4
    -nostartfiles
    -T ${CMAKE_CURRENT_SOURCE_DIR}/arm9.ld
    -Wl,--use-blx,--gc-sections
    -Wl,-Map,${CMAKE_CURRENT_BINARY_DIR}/${TARGET}9.map
)

if(NO_DEBUG)
    set(ARM9_LINK_FLAGS ${ARM9_COMMON_LINK_FLAGS} -flto)
else()
    set(ARM9_LINK_FLAGS
        ${ARM9_COMMON_LINK_FLAGS}
        -fstack-protector-strong
        -fno-inline
        -Wl,-wrap=malloc,-wrap=calloc,-wrap=free
    )
endif()

target_link_options(${TARGET}9 PRIVATE ${ARM9_LINK_FLAGS})

##==================================================
## Post-build: ELF to BIN
##==================================================

add_custom_command(TARGET ${TARGET}9 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
        $<TARGET_FILE:${TARGET}9>
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}9.bin
    COMMENT "Converting ${TARGET}9.elf -> ${TARGET}9.bin"
)

set(ARM9_BIN ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}9.bin PARENT_SCOPE)
