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

# Add your executable
add_executable(GhostStreaming main.cpp
        MetadataDB.cpp
        MetadataDB.h)

# Link your executable with the FFmpeg libraries
target_link_libraries(GhostStreaming ${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${AVUTIL_LIBRARIES})

# Additionally, link your executable with the Boost libraries
target_link_libraries(GhostStreaming ${Boost_LIBRARIES})

# Link against the SQLite3 library
target_link_libraries(GhostStreaming ${SQLite3_LIBRARIES})

