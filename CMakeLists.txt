cmake_minimum_required(VERSION 3.10)

project(bible_cli VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(requiredlibs)
# FIND_PACKAGE(CURL)
# IF(CURL_FOUND)
#   INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
#   set(requiredlibs ${requiredlibs} ${CURL_LIBRARIES})
# ELSE(CURL_FOUND)
#   MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
# ENDIF(CURL_FOUND)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(bible_cli src/main.cc)
include_directories(${CURL_INCLUDE_DIR})
include_directories(./include)

target_link_libraries(bible_cli ${CURL_LIBRARIES})

target_include_directories(bible_cli PUBLIC
  "${PROJECT_BINARY_DIR}/src"
  )


