#include "src/ypkg-common.h"
#include "src/conf/ypkg-apt-config.h"

vector<char*> ReadSourcesList(int* code);
struct SrcConfig SourceToConfig(char* conf);