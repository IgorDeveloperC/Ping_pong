cmake_minimum_required(VERSION 3.10)

project(PingPongGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_EXE src/main.cpp src/ConfigManager.cpp src/Player.cpp src/config.json
		include/Player.h include/ConfigManager.h include/json.hpp )


include_directories("${PROJECT_SOURCE_DIR}/include")

#set(SOURCE_LIB library/json.hpp)

#add_library(nlohmann PUBLIC ${SOURCE_LIB})


add_executable(PingPongGame ${SOURCE_EXE})

#add_subdirectory(library)

#target_link_libraries(PingPongGame nlohmann)

