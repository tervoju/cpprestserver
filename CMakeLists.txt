cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(testserver VERSION 0.0.1)

#from https://raw.githubusercontent.com/matt-42/lithium/master/cmake_project_template/CMakeLists.txt

find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED context)
pkg_search_module(JSONCPP jsoncpp)

include_directories(${CURL_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

set(LI_PREFIX_PATH "./lithium/bin/")
# the symbol generation target
add_custom_target(
    symbols_generation
    COMMAND ${LI_PREFIX_PATH}li_symbol_generator ${CMAKE_CURRENT_SOURCE_DIR})

set(LITHIUM_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lithium/include)

include_directories(${LITHIUM_HEADER_DIR})

set(LIBS ${CURL_LIBRARIES} 
         ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
         ${OPENSSL_LIBRARIES} 
         ${JSONCPP_LIBRARIES})

add_executable(testserver testserver.cpp)
# Link the symbol generation to your cmake target:
add_dependencies(testserver symbols_generation)
target_link_libraries(testserver ${LIBS})