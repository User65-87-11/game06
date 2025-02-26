cmake_minimum_required(VERSION 3.12)
project(Hello)

add_executable(tests)
 
target_sources(
    tests PRIVATE
    all.c
)

target_include_directories(
    tests PRIVATE 
    ../external/
    ../include/
	./
)

 
# target_link_libraries(
#     tests PRIVATE
#     C:/glfw-3.4.bin.WIN64/lib-vc2022/glfw3_mt.lib
#     glad
# 	#"../../libs/freetype/vs2015-2022/win64/freetype"
# )

 
 