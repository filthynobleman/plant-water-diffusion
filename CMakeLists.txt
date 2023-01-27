cmake_minimum_required(VERSION 3.16.0)
project(PlantWaterDiffusion VERSION 0.1.0)

# Languages are C and C++
enable_language(C)
enable_language(CXX)


# Windows needs extra care for making shared libraries
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()


# Include eigen
include_directories("${CMAKE_SOURCE_DIR}/ext/eigen")


# Include project headers
include_directories("${CMAKE_SOURCE_DIR}/include")


# Library files
set(HPP_FILES   "${CMAKE_SOURCE_DIR}/include/pwd/common/includes.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/common/fwddecl.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/common/exceptions.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/common/checks.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/common/memory.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/common/common.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/utils/queue.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/utils/stack.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/pwd.hpp")
set(CPP_FILES   "${CMAKE_SOURCE_DIR}/src/common/baseexception.cpp"
                "${CMAKE_SOURCE_DIR}/src/common/nullexception.cpp"
                "${CMAKE_SOURCE_DIR}/src/common/assertexception.cpp")

# Create the library
add_library(pwd SHARED  ${CPP_FILES})
target_compile_features(pwd PRIVATE cxx_std_17)


# Build sample option
option(BUILD_SAMPLES "Build sample applications for testing." ON)

# Install
install(TARGETS pwd
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/pwd/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/pwd/lib"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/pwd/bin"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/pwd/include/pwd")


if (BUILD_SAMPLES)

    # Build, compile and link dependencies
    # GLAD
    set(GLAD_HOME "${CMAKE_SOURCE_DIR}/ext/glad" CACHE PATH "Home directory of GLAD.")
    include_directories("${GLAD_HOME}/include")
    add_library(GLAD STATIC "${GLAD_HOME}/src/glad.c")

    # GLFW
    set(GLFW_HOME "${CMAKE_SOURCE_DIR}/ext/glfw" CACHE PATH "Home directory of GLFW.")
    include_directories("${GLFW_HOME}/include")
    if (MSVC)
        set(glfw3 "${GLFW_HOME}/lib/glfw3.lib")
    else()
        set(glfw3 "${GLFW_HOME}/lib/glfw3.a")
    endif()
    find_package(OpenGL REQUIRED)

    # GLM
    set(GLM_HOME "${CMAKE_SOURCE_DIR}/ext/glm" CACHE PATH "Home directory of GLM.")
    include_directories("${GLM_HOME}/include")

    # Compile test applications
    add_executable(TestCommons "${CMAKE_SOURCE_DIR}/src/samples/test_commons.cpp")
    target_compile_features(TestCommons PRIVATE cxx_std_17)
    target_link_libraries(TestCommons pwd)
    
    add_executable(TestUtils "${CMAKE_SOURCE_DIR}/src/samples/test_utils.cpp")
    target_compile_features(TestUtils PRIVATE cxx_std_17)
    target_link_libraries(TestUtils pwd)
endif()










