cmake_minimum_required(VERSION 3.11...3.15)

#if using an older VERSION of curl ocsp stapling can be disabled
set(CURL_MIN_VERSION "7.28.0")

# Setting up project
project(curlcpp LANGUAGES CXX)

set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
			STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
			"Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT ERROR)

if(IPO_SUPPORTED)
	message(STATUS "IPO / LTO supported, will enable for targets in release build type")
else()
	message(STATUS "IPO / LTO not supported: <${ERROR}>, will not enable")
endif()

option(CURLCPP_USE_PKGCONFIG
	"Use pkg-config to find libcurl. When off, find_package() will be used" OFF)

# Set up source directories
add_subdirectory(src)

# Set up test directory.
add_subdirectory(test)

# Set library location
set(CURLCPP_LIB_LOCATION "$<TARGET_FILE:${curlcpp}>")

configure_file(CMake/curlcppConfig.cmake.in
  ${CMAKE_INSTALL_PREFIX}/lib/curlcpp/curlcppConfig.cmake @ONLY)
