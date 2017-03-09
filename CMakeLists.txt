#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description: Arduino CMake example                                          #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(TrigGPS C CXX)

print_board_list()
print_programmer_list()

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# This configuration file outlines some of the ways Arduino CMake
# can be used. For a detailed explenation of all the options please
# reade README.rst.

set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0) # Default Port, when not specified

#====================================================================#
# Bundled blink sketch example
#====================================================================#
generate_arduino_firmware(TrigGPS
#${CMAKE_PROJECT_NAME}
#)
	SKETCH src/TrigGPS
	SRCS src/TrigGPS/pmrrc.cpp src/TrigGPS/kdtree.cpp ${MY_LIB_SRCS}
	#SRCS ${CMAKE_SOURCE_DIR}/src/TrigGPS/kdtree.cpp ${CMAKE_SOURCE_DIR}/src/TrigGPS/pmrcc.cpp)
)

#generate_arduino_firmware(Blink2
#    SKETCH ${CMAKE_SOURCE_DIR}/test/Blink2
#    BOARD mega
#    PORT /dev/ttyUSB0)
	
# Alternative: by variables
#set(blink_bundled_SKETCH Blink)
#set(blink_bundled_PROGRAMMER usbtinyisp)
#set(blink_bundled_NO_AUTOLIBS true)
#
#generate_arduino_firmware(triggps)
