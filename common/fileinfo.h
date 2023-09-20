#ifndef FILE_INFO_H
#define FILE_INFO_H

#include "../dynabuf/dynabuf.h"

typedef struct {

} LoadedFile;

DynamicBuffer(LoadedFile) *loaded_files;

void setup_files(void);

#endif