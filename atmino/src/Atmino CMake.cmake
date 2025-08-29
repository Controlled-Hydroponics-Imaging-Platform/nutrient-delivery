cmake_minimum_required(VERSION 3.13)

# Pull in Pico SDK (expects PICO_SDK_PATH env var or pico_sdk_import.cmake)
include(pico_sdk_import.cmake)

project(LuxSensorProject C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add your executable (all source files go here)
add_executable(LuxSensorProject
    main.cpp
    Sensor.cpp
    LuxSensor.cpp
)

# Link with Pico libraries
target_link_libraries(LuxSensorProject
    pico_stdlib    # basic stdlib
    hardware_i2c   # I2C driver
)

# Enable USB or UART stdio (you can change this depending on how you debug)
pico_enable_stdio_usb(LuxSensorProject 1) # 1 : enabled
pico_enable_stdio_uart(LuxSensorProject 0) # 0 : disabled

# Create .uf2 file for flashing
pico_add_extra_outputs(LuxSensorProject)

# end of Cmake file