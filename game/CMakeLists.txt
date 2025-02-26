cmake_minimum_required(VERSION 3.12)
project(Hello)


 
add_executable(main)
 
 
target_sources(
    main PRIVATE
    main.c
)

 

target_include_directories(
    main PRIVATE 
    C:/glfw-3.4.bin.WIN64/include
    C:/glad/include
     ../external/
    ../include/
	../models/
	# ./
)

 
target_link_libraries(
    main PRIVATE
    C:/glfw-3.4.bin.WIN64/lib-vc2022/glfw3_mt.lib
    glad
	#"../../libs/freetype/vs2015-2022/win64/freetype"
)

 
 