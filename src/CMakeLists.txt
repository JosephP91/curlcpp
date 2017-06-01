set(CURLCPP_SOURCE
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
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_library(curlcpp ${CURLCPP_SOURCE})
target_link_libraries(curlcpp ${CURL_LIBRARY})
install (TARGETS curlcpp LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
