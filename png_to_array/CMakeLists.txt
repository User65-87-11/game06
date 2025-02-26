cmake_minimum_required(VERSION 3.12)
project(Hello2)

add_executable(png)
 
target_sources(
    png PRIVATE
    main.c
	../external/spng/spng.c
)
add_library(zlib STATIC
    ../external/zlib-1.3.1/adler32.c
	../external/zlib-1.3.1/compress.c
    ../external/zlib-1.3.1/crc32.c
    ../external/zlib-1.3.1/deflate.c
    ../external/zlib-1.3.1/gzclose.c
    ../external/zlib-1.3.1/gzlib.c
    ../external/zlib-1.3.1/gzread.c
    ../external/zlib-1.3.1/gzwrite.c
    ../external/zlib-1.3.1/infback.c
    ../external/zlib-1.3.1/inffast.c
    ../external/zlib-1.3.1/inflate.c
    ../external/zlib-1.3.1/inftrees.c
    ../external/zlib-1.3.1/trees.c
    ../external/zlib-1.3.1/uncompr.c
    ../external/zlib-1.3.1/zutil.c
)
target_include_directories(
    png PRIVATE 
    ../external/
    ../include/
	./
	../external/zlib-1.3.1/
)


target_link_libraries(png PRIVATE zlib)

 

 
# target_link_libraries(
#     tests PRIVATE
#     C:/glfw-3.4.bin.WIN64/lib-vc2022/glfw3_mt.lib
#     glad
# 	#"../../libs/freetype/vs2015-2022/win64/freetype"
# )

 
 