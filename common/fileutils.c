#include "fileinfo.h"

void setup_files(void) {
    loaded_files = newDynamicBuf(LoadedFile);
    initDynamicBuf(LoadedFile, loaded_files);
}