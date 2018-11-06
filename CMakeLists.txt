cmake_minimum_required(VERSION 2.6)
project(population_genetics)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)

add_executable(popSimulation src/main.cpp src/simulation.cpp src/graphics.cpp src/random.cpp)
if (test)
  enable_testing()
  find_package(GTest)
  if (NOT GTEST_FOUND)
    link_directories(${CMAKE_SOURCE_DIR}/lib)
    SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
    SET(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
  endif(NOT GTEST_FOUND)
  add_executable (test_popSim src/test_main.cpp src/simulation.cpp src/graphics.cpp src/random.cpp)
  target_link_libraries(test_popSim ${GTEST_BOTH_LIBRARIES} pthread)
  add_test(population_genetics test_popSim)
endif(test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)



