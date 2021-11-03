cmake_minimum_required(VERSION 3.18)
project(learnopengl)

if (APPLE)
  list(APPEND CMAKE_MODULE_PATH "/Users/Kevin/Development/OpenGL/cmake")
  SET(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")
  set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
  set(GLAD_DIR /Users/Kevin/Development/OpenGL/glad/)
  find_package(glfw3 REQUIRED)  
elseif (WIN32)
  set(GLAD_DIR "C:/Users/liqilong/Desktop/OpenGL/glad/")
  set(GLM_LIBRARY "C:/Users/liqilong/Desktop/OpenGL/lib/glm.lib")
  set(GLFW3_LIBRARY "C:/Users/liqilong/Desktop/OpenGL/lib/glfw3.lib")
  set(GLFW3_INCLUDE_DIR "C:/Users/liqilong/Desktop/OpenGL/include")
endif()

find_package(OpenGL REQUIRED)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "src/*.h")

include_directories(
  ${GLFW3_INCLUDE_DIR}
  ${GLAD_DIR}/include
  )

list(APPEND SOURCE_FILES
  ${GLAD_DIR}/src/glad.c
  )

add_executable(main ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(main ${GLFW3_LIBRARY} ${GLM_LIBRARY})

