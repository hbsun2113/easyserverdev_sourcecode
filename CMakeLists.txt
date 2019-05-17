cmake_minimum_required(VERSION 3.5.1)
project(easyserverdev_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(main.cpp server3.cpp client3_2.cpp select_server4_1.cpp select_client4_1.cpp select_client4_2.cpp select_client4_3.cpp blocking_server6.cpp blocking_client6.cpp nonblocking_client6.cpp nonblocking_connect8.cpp linux_nonblocking_connect8.cpp)