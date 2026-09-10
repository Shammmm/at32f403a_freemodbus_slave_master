cmake_minimum_required(VERSION 3.22)

#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set the project name
set(CMAKE_PROJECT_NAME at32f403a_freemodbus_slave_master)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add at32_workbench generated sources
add_subdirectory(cmake/at32_workbench)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_SOURCE_DIR}/modbus/mb_m.c
    ${CMAKE_SOURCE_DIR}/modbus/rtu/mbrtu_m.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfunccoils_m.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncdisc_m.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncholding_m.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncinput_m.c
    ${CMAKE_SOURCE_DIR}/modbus_port/portserial_m.c
    ${CMAKE_SOURCE_DIR}/modbus_port/porttimer_m.c
    ${CMAKE_SOURCE_DIR}/modbus_port/portevent_m.c
    ${CMAKE_SOURCE_DIR}/modbus_port/mt_port.c
    ${CMAKE_SOURCE_DIR}/modbus/mb.c
    ${CMAKE_SOURCE_DIR}/modbus/rtu/mbrtu.c
    ${CMAKE_SOURCE_DIR}/modbus/rtu/mbcrc.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfunccoils.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncdisc.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncholding.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncinput.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbfuncother.c
    ${CMAKE_SOURCE_DIR}/modbus/functions/mbutils.c
    ${CMAKE_SOURCE_DIR}/modbus_port/portserial.c
    ${CMAKE_SOURCE_DIR}/modbus_port/porttimer.c
    ${CMAKE_SOURCE_DIR}/modbus_port/portevent.c
    ${CMAKE_SOURCE_DIR}/project/src/mbtask.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_SOURCE_DIR}/modbus
    ${CMAKE_SOURCE_DIR}/modbus/include
    ${CMAKE_SOURCE_DIR}/modbus_port
    ${CMAKE_SOURCE_DIR}/modbus/ascii
    ${CMAKE_SOURCE_DIR}/modbus/functions
    ${CMAKE_SOURCE_DIR}/modbus/rtu
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    at32_workbench

    # Add user defined libraries
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
)