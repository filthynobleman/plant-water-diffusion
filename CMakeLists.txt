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
                "${CMAKE_SOURCE_DIR}/include/pwd/graph/node.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/graph/graph.hpp"
                "${CMAKE_SOURCE_DIR}/include/pwd/pwd.hpp")
set(CPP_FILES   "${CMAKE_SOURCE_DIR}/src/common/baseexception.cpp"
                "${CMAKE_SOURCE_DIR}/src/common/nullexception.cpp"
                "${CMAKE_SOURCE_DIR}/src/common/assertexception.cpp"
                "${CMAKE_SOURCE_DIR}/src/graph/node.cpp"
                "${CMAKE_SOURCE_DIR}/src/graph/graph.cpp")

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

    # STB
    set(STB_HOME "${CMAKE_SOURCE_DIR}/ext/stb")
    include_directories("${STB_HOME}/include")
    add_library(STB "${CMAKE_SOURCE_DIR}/src/stb/stb_implementation.cpp")
    
    # ImGui
    set(IMGUI_HOME "${CMAKE_SOURCE_DIR}/ext/imgui")
    include_directories("${IMGUI_HOME}")
    include_directories("${IMGUI_HOME}/backends")
    add_library(IMGUI STATIC    "${IMGUI_HOME}/imgui.cpp"
                                "${IMGUI_HOME}/imgui_widgets.cpp"
                                "${IMGUI_HOME}/imgui_tables.cpp"
                                "${IMGUI_HOME}/imgui_draw.cpp"
                                "${IMGUI_HOME}/imgui_demo.cpp"
                                "${IMGUI_HOME}/backends/imgui_impl_glfw.cpp"
                                "${IMGUI_HOME}/backends/imgui_impl_opengl3.cpp")
    target_link_libraries(IMGUI ${glfw3} OpenGL::GL)


    # I/O library
    add_library(MeshIO STATIC   "${CMAKE_SOURCE_DIR}/src/io/obj.cpp"
                                "${CMAKE_SOURCE_DIR}/src/io/mesh.cpp")

    # Rendering library
    add_library(Rendering STATIC    "${CMAKE_SOURCE_DIR}/src/rendering/camera.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/model.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/shader.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/texture.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/transform.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/vertex.cpp"
                                    "${CMAKE_SOURCE_DIR}/src/rendering/window.cpp")
    
    # User interface library
    add_library(UI STATIC   "${CMAKE_SOURCE_DIR}/src/ui/uimanager.cpp"
                            "${CMAKE_SOURCE_DIR}/src/ui/uicomponent.cpp"
                            "${CMAKE_SOURCE_DIR}/src/ui/modprop.cpp"
                            "${CMAKE_SOURCE_DIR}/src/ui/lightprop.cpp"
                            "${CMAKE_SOURCE_DIR}/src/ui/simopts.cpp"
                            "${CMAKE_SOURCE_DIR}/src/ui/camprop.cpp")

    # Compile test applications
    add_executable(TestCommons "${CMAKE_SOURCE_DIR}/src/samples/test_commons.cpp")
    target_compile_features(TestCommons PRIVATE cxx_std_17)
    target_link_libraries(TestCommons pwd)
    
    add_executable(TestUtils "${CMAKE_SOURCE_DIR}/src/samples/test_utils.cpp")
    target_compile_features(TestUtils PRIVATE cxx_std_17)
    target_link_libraries(TestUtils pwd)
    
    add_executable(TestGraph "${CMAKE_SOURCE_DIR}/src/samples/test_graph.cpp")
    target_compile_features(TestGraph PRIVATE cxx_std_17)
    target_link_libraries(TestGraph pwd GLAD STB ${glfw3} IMGUI OpenGL::GL UI Rendering MeshIO)
endif()










