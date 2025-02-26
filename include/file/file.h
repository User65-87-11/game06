#pragma once


#ifdef FILE_IMPLEMENTATION
#include <stdlib.h>
#endif
#include <stdio.h>
#include <vcruntime.h>
 

typedef struct File_s File_s;
struct  File_s {
	bool is_valid;
	char * err;
	FILE * pfile;
	char * mode;
	char * path;
	char * data;
	size_t data_size;
	size_t read_size;

	//
	void (*pfile_read)(File_s *);
	void (*pfile_close)(File_s *);
	void (*pfile_free)(File_s *);
	void (*pfile_write)(File_s *);

};

void file_read(File_s [static 1] );
void  file_close(File_s [static 1]);
void  file_free(File_s [static 1]);
void file_write(File_s [static 1]);
File_s file_open(const char  name [static 1],const char mode [static 1]);


#ifdef FILE_IMPLEMENTATION
void  file_close(File_s file[static 1]){
	if(file->pfile !=nullptr)
		fclose(file->pfile);
}
void file_write(File_s file[static 1] ){
	if(file->is_valid ==false) return;

	int err = fwrite(file->data, sizeof(char), file->data_size, file->pfile);
	if(err)
	{
		file->err="fwrite";
		file->is_valid = false;
		return ;
	}
 
 
}
void  file_free(File_s ptr[static 1]){
	if(ptr->data!=nullptr)
	{
		free(ptr->data);

	}
	FILE *f = ptr->pfile;
	*ptr = (File_s){.pfile = f};

}
File_s file_open(const char  name [static 1],const char mode [static 1]){
	File_s ret ={.err="no-err",.is_valid=true,.mode = mode};
	ret.pfile_read = file_read;
	ret.pfile_write = file_write;
	ret.pfile_free = file_free;
	ret.pfile_close = file_close;

	int err = fopen_s(&ret.pfile, name,mode);
	if(err){
		ret.err="fopen";
		ret.is_valid = false;
	}
	return ret;
}

void  file_read(File_s  ptr [static 1]){
	if(ptr->is_valid == false) return;
	
 
	fseek (ptr->pfile , 0 , SEEK_END);
	ptr->read_size = ftell (ptr->pfile);
	rewind (ptr->pfile);

	if(ptr->read_size == 0){
		ptr->err="ftell";
		ptr->is_valid = false;
		return;
	}

	ptr->data = malloc(ptr->read_size);
	if(ptr->data == nullptr)
	{
		ptr->err="malloc";
		ptr->is_valid = false;
		return;
	}
	ptr->data_size = ptr->read_size;
	//fread_s(void *Buffer, size_t BufferSize, size_t ElementSize, size_t ElementCount, FILE *Stream)
	ptr->data_size = fread_s(ptr->data,  ptr->read_size, sizeof(char),  ptr->read_size, ptr->pfile);
	if(ptr->data_size == 0)
	{
		ptr->err="fread_s";
		ptr->is_valid = false;
		return;
	}
 
}
#endif