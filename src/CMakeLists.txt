SET(CURLCPP_SOURCE
  CurlEasy.cpp
  CurlHeader.cpp
  CurlHttpPost.cpp
  CurlMulti.cpp
  CurlShare.cpp
  CurlVersion.cpp
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_LIBRARY(curlcpp STATIC ${CURLCPP_SOURCE})
TARGET_LINK_LIBRARIES(curlcpp curl)
