cmake_minimum_required(VERSION 2.8)

project( METASM )

option(BUILD_SHARED "ON to build Metasm as SHARED, OFF to build Metasm AS STATIC" OFF)
option(BUILD_EXAMPLES "ON to build examples" ON)
option(DEBUG "Enable debugging symbols" OFF)

include_directories( "include" )


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    
    # using GCC

    add_compile_options(
                    -std=c++14
                    -Wall
                    -Wextra
                    -pedantic
                    )
    if(DEBUG)
        #Debug Mode
        add_compile_options(
                    -g
                    )
    else()
        #Release Mode
        add_compile_options(
                    -O3
                    )
    endif()
endif()


set(SOURCES
    "include/Metasm.hpp"
    "src/Metasm.cpp"
    )

if(BUILD_SHARED)
    add_library(METASM SHARED ${SOURCES})
else()
    add_library(METASM STATIC ${SOURCES})
endif()

target_link_libraries( METASM "libgccjit.so" )

if(BUILD_EXAMPLES)

    set(LINK_LIBS ${LINK_LIBS} METASM)

    set(SOURCE
        "examples/basics.cpp"
        )

    add_executable(basics ${SOURCE})
    target_link_libraries(basics ${LINK_LIBS})

    set(SOURCE
        "examples/labels.cpp"
        )

    add_executable(labels ${SOURCE})
    target_link_libraries(labels ${LINK_LIBS})

    set(SOURCE
        "examples/square_root.cpp"
        )

    add_executable(square_root ${SOURCE})
    target_link_libraries(square_root ${LINK_LIBS})
endif() 