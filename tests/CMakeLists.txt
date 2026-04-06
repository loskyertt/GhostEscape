# for each "test/x.cpp", generate target "x"
message("CMakeLists.txt for test directory")

file(GLOB_RECURSE all_tests *.cpp)
foreach(v ${all_tests})
  message("Processing: ${v}")
  get_filename_component(target_name ${v} NAME_WE) # 生成目标名（去掉路径和扩展名）

  add_executable(${target_name} ${v})

  target_link_libraries(${target_name}
    PRIVATE
      ${SDL3_LIBRARIES}
      SDL3_image::SDL3_image
      SDL3_mixer::SDL3_mixer
      SDL3_ttf::SDL3_ttf
      glm::glm
  )

  # target_compile_options(${target_name} PRIVATE -Wall -Wextra -Werror)

  # MSVC UTF-8 支持
  if(MSVC)
    target_compile_options(${target_name} PRIVATE /utf-8)
  endif()
endforeach()

message(STATUS "--------------------------------------------\n")
