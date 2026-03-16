# for all "src/x.cpp", generate target "x"
message("CMakeLists.txt for src directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

add_executable(${TARGET}
  main.cpp
)

target_link_libraries(${TARGET}
  PRIVATE
    gamedll
)

if(MSVC)
  target_compile_options(${TARGET} PRIVATE /utf-8)  # UTF-8 支持
endif()

message(STATUS "--------------------------------------------\n")
