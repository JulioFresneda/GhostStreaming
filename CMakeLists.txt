cmake_minimum_required(VERSION 3.27)
project(GhostStreaming)

set(CMAKE_CXX_STANDARD 17)

# Find the required FFmpeg libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)

# Include the FFmpeg header files
include_directories(${AVFORMAT_INCLUDE_DIRS} ${AVCODEC_INCLUDE_DIRS} ${AVUTIL_INCLUDE_DIRS})

# Find Boost with the required components
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

# Find SQLite3 package
find_package(SQLite3 REQUIRED)

# Include SQLite3 headers
include_directories(${SQLite3_INCLUDE_DIRS})


find_package(Crow REQUIRED)
include_directories(${Crow_INCLUDE_DIRS})



# Add executable for the server application
add_executable(GhostStreamingServer
        streaming_server/main.cpp
        streaming_server/MetadataDB.cpp
        streaming_server/api_endpoint.cpp
        streaming_server/api_endpoint.h
        # Add any other source files for the server app here
)

# Add executable for the add-media application
add_executable(GhostStreamingAddMedia
        add_media_app/main.cpp
        add_media_app/MetadataDatabase.cpp
        streaming_server/MetadataDB.h
        # Add any other source files for the add-media app here
)

add_executable(GhostStreamingClient streaming_client/StreamingClient.cpp streaming_client/StreamingClient.h
        streaming_client/main.cpp)

# Link GhostStreamingServer executable with the FFmpeg, Boost, and SQLite3 libraries
target_link_libraries(GhostStreamingServer
        ${AVFORMAT_LIBRARIES}
        ${AVCODEC_LIBRARIES}
        ${AVUTIL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${SQLite3_LIBRARIES}
        ${Crow_INCLUDE_DIRS})



# Link GhostStreamingAddMedia executable with the FFmpeg, Boost, and SQLite3 libraries
target_link_libraries(GhostStreamingAddMedia
        ${AVFORMAT_LIBRARIES}
        ${AVCODEC_LIBRARIES}
        ${AVUTIL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${SQLite3_LIBRARIES})

target_link_libraries(GhostStreamingClient
        ${AVFORMAT_LIBRARIES}
        ${AVCODEC_LIBRARIES}
        ${AVUTIL_LIBRARIES}
        ${Boost_LIBRARIES}
        ${SQLite3_LIBRARIES})