#include "src/ypkg-common.h"
#include "src/ypkg-parser.h"

int main(int argc,char** argv)
{  
	int ret=ParseCommand(argc,argv);
	return ret;
}