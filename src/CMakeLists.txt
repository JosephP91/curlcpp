set(CURLCPP_HEADER_LIST
  ../include/cookie.h
  ../include/cookie_date.h
  ../include/cookie_datetime.h
  ../include/cookie_time.h
  ../include/curl_config.h
  ../include/curl_cookie.h
  ../include/curl_easy.h
  ../include/curl_easy_info.h
  ../include/curl_exception.h
  ../include/curl_form.h
  ../include/curl_global.h
  ../include/curl_header.h
  ../include/curl_info.h
  ../include/curl_interface.h
  ../include/curl_ios.h
  ../include/curl_multi.h
  ../include/curl_option.h
  ../include/curl_pair.h
  ../include/curl_receiver.h
  ../include/curl_sender.h
  ../include/curl_share.h
  ../include/curl_utility.h
)

add_library(curlcpp
  curl_easy.cpp
  curl_header.cpp
  curl_global.cpp
  curl_form.cpp
  curl_multi.cpp
  curl_share.cpp
  curl_info.cpp
  curl_cookie.cpp
  curl_exception.cpp
  cookie.cpp
  cookie_date.cpp
  cookie_time.cpp
  cookie_datetime.cpp
  ${CURLCPP_HEADER_LIST}
)

add_library(curlcpp::curlcpp ALIAS curlcpp)

target_include_directories(curlcpp PUBLIC
"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>"
"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/>")

target_compile_features(curlcpp PUBLIC cxx_std_11)

target_compile_options(curlcpp PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4244 /wd4305 /wd4996 /wd4267 /wd4018>
)

if(CURLCPP_USE_PKGCONFIG)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(libcurl REQUIRED IMPORTED_TARGET libcurl>=${CURL_MIN_VERSION})
    target_link_libraries(curlcpp PUBLIC PkgConfig::libcurl)
else()
    # Add MacPorts
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_PREFIX_PATH /opt/local ${CMAKE_PREFIX_PATH})
    endif()

    find_package(CURL ${CURL_MIN_VERSION} REQUIRED)

    target_include_directories(curlcpp PUBLIC ${CURL_INCLUDE_DIRS})
    target_link_libraries(curlcpp PUBLIC ${CURL_LIBRARY})
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_options(curlcpp PUBLIC -stdlib=libc++)
endif()

if(IPO_SUPPORTED AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(curlcpp PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_target_properties (curlcpp PROPERTIES PUBLIC_HEADER "${CURLCPP_HEADER_LIST}")

include(GNUInstallDirs)
install(TARGETS curlcpp
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
