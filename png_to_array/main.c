 

 

#include <math.h>
#include <string.h>
#define FILE_IMPLEMENTATION
#include "file/file.h"

 
#include "spng/spng.h"

#include <stdio.h>
#include <vcruntime.h>
size_t  file_size(FILE * f){

	fseek (f , 0 , SEEK_END);
	size_t 	size = ftell (f);
	rewind (f);

	return size;
}


int main(int argc, char * argv[]){

	if(argc != 3)
	{
		printf("Missing args!\n");
		printf("argv[1]: path/to/img.png\n");
		printf("argv[2]: path/to/output.txt\n");
		return -1;
	}
	if(strcmp(argv[1], argv[2]) ==0){

		printf("argv[1] and argv[2]: appears to be the same\n");
		return -1;
	}

 
	File_s fs = file_open(argv[1],"rb");
	
	fs.pfile_read(&fs);
	fs.pfile_close(&fs);
	/* Create a context */
	spng_ctx *ctx = spng_ctx_new(0);

	/* Set an input buffer */
	spng_set_png_buffer(ctx, fs.data, fs.data_size);
	size_t size;
	spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);
	if(size)
	{

		char *colors = malloc(size);
		spng_decode_image(ctx, colors,size, SPNG_FMT_RGBA8, 0);
		spng_ctx_free(ctx);
		fs.pfile_free(&fs);
		printf("size: %i \n",size);
		if(size > 4096)
		{
			printf("map too big , req 32x32 px \n");
			return 0;
		}
	 
		
		int map_size = size >> 2;
		int w = sqrt(map_size);
		int * ptr = colors;
		char * out_map = malloc(map_size);

		printf("map_size: %i, w:%i \n",map_size,w);
		char colr_freq[0xff] = {};
	 
		int cnt = 1;
		for(int i=0;i<w;i++)
		{
			for(int x=0;x<w;x++){
				int pos = i*w  +x;
				unsigned char *c = &ptr[pos];
				unsigned long long avg =  c[0] * c[1] *c[2] ;
				avg = pow(avg, 1/3.0);
				if(colr_freq[avg]  ==0)
				{
					colr_freq[avg] = cnt;
					cnt ++;
				}
				out_map[pos] = colr_freq[avg];
				printf("%02x ",out_map[pos]);
			}
			printf("\n");
		}
		File_s write = file_open(argv[2], "wb");
		write.data = out_map;
		write.data_size = map_size;
		write.pfile_write(&write);
		write.pfile_close(&write);
		free(out_map);
	}

 
	return 0;
}