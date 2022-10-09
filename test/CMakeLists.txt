cmake_minimum_required(VERSION 3.10...3.15)

project(test)

set(CMAKE_CXX_STANDARD 11)

include_directories("/usr/local/include")


add_executable(cookie_example_exec cookie.cpp)
add_executable(custom_request_example_exec custom_request.cpp)
add_executable(easy_example_exec easy.cpp)
add_executable(easy_info_example_exec easy_info.cpp)
add_executable(header_example_exec header.cpp)
add_executable(recv_header_example_exec recv_header.cpp)
add_executable(multi_example_exec multi.cpp)

target_link_libraries(cookie_example_exec curlcpp)
target_link_libraries(custom_request_example_exec curlcpp)
target_link_libraries(easy_example_exec curlcpp)
target_link_libraries(easy_info_example_exec curlcpp)
target_link_libraries(header_example_exec curlcpp)
target_link_libraries(recv_header_example_exec curlcpp)
target_link_libraries(multi_example_exec curlcpp)
