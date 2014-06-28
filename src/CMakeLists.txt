SET(CURLCPP_SOURCE
  curl_easy.cpp
  curl_header.cpp
  curl_form.cpp
  curl_multi.cpp
  curl_share.cpp
  curl_info.cpp
  curl_error.cpp	
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_LIBRARY(curlcpp STATIC ${CURLCPP_SOURCE})
TARGET_LINK_LIBRARIES(curlcpp ${CURL_LIBRARY})
