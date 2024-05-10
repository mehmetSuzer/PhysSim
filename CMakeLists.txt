
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(PhysSim VERSION 0.1.0)

find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)

set(LIB_DIR lib)
set(DATA_DIR data)

file(COPY ${CMAKE_SOURCE_DIR}/${DATA_DIR} DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(${LIB_DIR}/mathematics)
include_directories(${LIB_DIR}/mathematics)

add_subdirectory(${LIB_DIR}/verlet)
include_directories(${LIB_DIR}/verlet)

add_subdirectory(${LIB_DIR}/verlet_pool)
include_directories(${LIB_DIR}/verlet_pool)

add_subdirectory(${LIB_DIR}/observer)
include_directories(${LIB_DIR}/observer)

add_subdirectory(${LIB_DIR}/constraint)
include_directories(${LIB_DIR}/constraint)

add_subdirectory(${LIB_DIR}/circle_constraint)
include_directories(${LIB_DIR}/circle_constraint)

add_subdirectory(${LIB_DIR}/arc_constraint)
include_directories(${LIB_DIR}/arc_constraint)

add_subdirectory(${LIB_DIR}/rectangle_constraint)
include_directories(${LIB_DIR}/rectangle_constraint)

add_subdirectory(${LIB_DIR}/ellipse_constraint)
include_directories(${LIB_DIR}/ellipse_constraint)

add_subdirectory(${LIB_DIR}/solver)
include_directories(${LIB_DIR}/solver)

add_subdirectory(${LIB_DIR}/renderer)
include_directories(${LIB_DIR}/renderer)

add_subdirectory(${LIB_DIR}/command)
include_directories(${LIB_DIR}/command)

add_subdirectory(${LIB_DIR}/event_controller)
include_directories(${LIB_DIR}/event_controller)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    event_controller
    renderer
    solver
    ellipse_constraint
    rectangle_constraint
    arc_constraint
    circle_constraint
    observer
    verlet_pool
    verlet
    mathematics
    sfml-system 
    sfml-window 
    sfml-audio
    sfml-graphics
)
