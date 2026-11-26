cmake_minimum_required(VERSION 3.16)
project(homework_3)

find_package(OpenCV REQUIRED)

add_executable(
    homework_3
    src/Detector.cpp
    src/main.cpp 
    src/pnp_solver.cpp 
)   

target_include_directories(homework_3 PRIVATE include ${OpenCV_INCLUDE_DIRS})
target_compile_features(homework_3 PRIVATE cxx_std_17)
target_link_libraries(homework_3 PRIVATE ${OpenCV_LIBS})