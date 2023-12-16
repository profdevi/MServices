#v1.0 copyright Comine.com 20230616F1713
#
#
#   

cmake_minimum_required(VERSION 3.14)

########################################################
project(MServices)

###################################
# C++ Version
###################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

###################################
# Build Src Files
###################################
file(GLOB MSource "src/*.h" "src/*.cpp" "src/*.c" )
add_executable(${PROJECT_NAME} ${MSource} )

###################################
install(TARGETS ${PROJECT_NAME} DESTINATION bin)


