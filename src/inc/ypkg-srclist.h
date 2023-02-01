#include "src/ypkg-common.h"
#include "src/conf/ypkg-apt-config.h"

vector<string> ReadSourcesList(int* code);
struct SrcConfig SourceToConfig(char* conf);