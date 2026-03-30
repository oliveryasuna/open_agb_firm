# ARM11 target (ARMv6K+VFPv2 / MPCore)

set_property(SOURCE
    ${CMAKE_SOURCE_DIR}/source/arm11/fast_frame_convert.s
    ${CMAKE_SOURCE_DIR}/source/arm11/fast_rom_padding.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/memory.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/cache.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/exception.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/lgy_link.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/start.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/contextswitch.s
    APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp"
)

set(ARM11_ARCH_FLAGS
    -march=armv6k+vfpv2
    -mtune=mpcore
    -mfloat-abi=hard
    -mtp=soft
    -marm
    -mthumb-interwork
    -masm-syntax-unified
)

##==================================================
## Sources
##==================================================

set(ARM11_PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/source/oaf_error_codes.c
    ${CMAKE_SOURCE_DIR}/source/arm11/main.c
    ${CMAKE_SOURCE_DIR}/source/arm11/cheats.c
    ${CMAKE_SOURCE_DIR}/source/arm11/config.c
    ${CMAKE_SOURCE_DIR}/source/arm11/filebrowser.c
    ${CMAKE_SOURCE_DIR}/source/arm11/gpu_cmd_lists.c
    ${CMAKE_SOURCE_DIR}/source/arm11/oaf_osd.c
    ${CMAKE_SOURCE_DIR}/source/arm11/oaf_video.c
    ${CMAKE_SOURCE_DIR}/source/arm11/open_agb_firm.c
    ${CMAKE_SOURCE_DIR}/source/arm11/patch.c
    ${CMAKE_SOURCE_DIR}/source/arm11/save_type.c
    ${CMAKE_SOURCE_DIR}/source/arm11/fast_frame_convert.s
    ${CMAKE_SOURCE_DIR}/source/arm11/fast_rom_padding.s
)

set(ARM11_LIBN3DS_SHARED_SOURCES
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

set(ARM11_LIBN3DS_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/console.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/debug.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/cache.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/codec.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/csnd.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/exception.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/gfx.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/gpio.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/hid.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/hw_cal.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/i2c.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/interrupt.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/lcd.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/lgy11.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/lgy_link.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/lgycap.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/mcu.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/mmu.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/pdn.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/prng.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/spi.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/spiflash.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/drivers/timer.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/fmt.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/fs.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/ipc_handler.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/power.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/start.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/system.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_clear.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_empty.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_find.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_init.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_insert.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_iterator.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_minmax.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_remove.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_rotate.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/util/rbtree/rbtree_size.c
)

set(ARM11_LIBN3DS_ALLOCATOR_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/allocator/fcram.cpp
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/allocator/mem_pool.cpp
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm11/allocator/vram.cpp
)

set(ARM11_KERNEL_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/contextswitch.s
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/kernel.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/kevent.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/kmutex.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/ksemaphore.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/ktimer.c
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/source/slabheap.c
)

set(ARM11_INIH_SOURCES
    ${CMAKE_SOURCE_DIR}/libraries/inih/ini.c
)

##==================================================
## Target
##==================================================

add_executable(${TARGET}11
    ${ARM11_PROJECT_SOURCES}
    ${ARM11_LIBN3DS_SHARED_SOURCES}
    ${ARM11_LIBN3DS_SOURCES}
    ${ARM11_LIBN3DS_ALLOCATOR_SOURCES}
    ${ARM11_KERNEL_SOURCES}
    ${ARM11_INIH_SOURCES}
)

target_include_directories(${TARGET}11 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/include
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/kernel/include
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/libraries
    ${CMAKE_SOURCE_DIR}/libraries/libn3ds/source/arm9/fatfs
    ${CMAKE_SOURCE_DIR}/libraries
)

target_compile_definitions(${TARGET}11 PRIVATE
    __ARM11__
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

set(ARM11_COMMON_C_FLAGS
    ${ARM11_ARCH_FLAGS}
    -O2
    -gdwarf-4
    -mword-relocations
    -ffunction-sections
    -fno-math-errno
    -Wall
    -Wextra
)

if(NO_DEBUG)
    set(ARM11_C_FLAGS ${ARM11_COMMON_C_FLAGS} -flto)
    set(ARM11_ASM_FLAGS ${ARM11_ARCH_FLAGS} -gdwarf-4 -flto)
else()
    set(ARM11_C_FLAGS ${ARM11_COMMON_C_FLAGS} -fstack-protector-strong -fno-inline)
    set(ARM11_ASM_FLAGS ${ARM11_ARCH_FLAGS} -gdwarf-4)
endif()

target_compile_options(${TARGET}11 PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=c23>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++23 -fno-rtti -fno-exceptions>
    $<$<COMPILE_LANGUAGE:ASM>:${ARM11_ASM_FLAGS}>
    $<$<COMPILE_LANGUAGE:C,CXX>:${ARM11_C_FLAGS}>
)

##==================================================
## Link flags
##==================================================

set(ARM11_COMMON_LINK_FLAGS
    ${ARM11_ARCH_FLAGS}
    -gdwarf-4
    -nostartfiles
    -T ${CMAKE_CURRENT_SOURCE_DIR}/arm11.ld
    -Wl,--use-blx,--gc-sections
    -Wl,-Map,${CMAKE_CURRENT_BINARY_DIR}/${TARGET}11.map
)

if(NO_DEBUG)
    set(ARM11_LINK_FLAGS ${ARM11_COMMON_LINK_FLAGS} -flto)
else()
    set(ARM11_LINK_FLAGS
        ${ARM11_COMMON_LINK_FLAGS}
        -fstack-protector-strong
        -fno-inline
        -Wl,-wrap=malloc,-wrap=calloc,-wrap=free
    )
endif()

target_link_options(${TARGET}11 PRIVATE ${ARM11_LINK_FLAGS})

target_link_libraries(${TARGET}11 PRIVATE m)

##==================================================
## Post-build: ELF to BIN
##==================================================

add_custom_command(TARGET ${TARGET}11 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary
        $<TARGET_FILE:${TARGET}11>
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}11.bin
    COMMENT "Converting ${TARGET}11.elf -> ${TARGET}11.bin"
)

set(ARM11_BIN ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}11.bin PARENT_SCOPE)
