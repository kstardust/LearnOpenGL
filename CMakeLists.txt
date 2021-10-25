project(learnopengl)

if (APPLE)
  list(APPEND CMAKE_MODULE_PATH "/Users/Kevin/Development/OpenGL/cmake")
  SET(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")
  set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)
  include_directories(/usr/local/include /Users/Kevin/Development/OpenGL/glad)
  set(GLAD_DIR /Users/Kevin/Development/OpenGL/glad/)
endif()

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
  ${GLFW3_INCLUDE_DIR}
  ${GLAD_DIR}/include
  )

SET(SOURCE_FILES
  src/main.cpp
  ${GLAD_DIR}/src/glad.c
  )

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${GLFW3_LIBRARY})

