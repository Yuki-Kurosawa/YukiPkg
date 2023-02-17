#!/bin/bash

# Remove Last Build
rm -rf config.* configure.* autom4te.cache Makefile.am *.log aclocal.* install-sh missing depcomp stamp-h1 configure configure~ compile \
src/.deps src/.dirstamp .deps src/cmd/.deps src/inc/.deps src/cmd/.dirstamp src/inc/.dirstamp Makefile.in Makefile
# Configure makefile
autoscan
cp configure.scan configure.ac
cp configure.scan autoconf.tmp
if [ -f autoconf.ac ];then
  cp autoconf.ac configure.ac
else
  cp configure.ac autoconf.ac
fi
cp autoconf.ac configure.ac
aclocal
autoheader
autoconf
cp makefile.prog.am Makefile.am
automake --add-missing 1>/dev/null 2>&1

# Install via "./configure;make"
./configure 1>/dev/null 2>&1
make 1>/dev/null 2>&1

# Initialize config
mkdir -p ./etc/ypkg
mkdir -p ./var/lib/ypkg/{,lists,tmp,pkgs}
cp sources.list ./etc/ypkg/sources.list

# Do some unit tests
echo "-------------------- BEGIN UNIT TESTS --------------------"
#./ypkg
#./ypkg version
#./ypkg cf
./ypkg up
cp -R ./var/lib/ypkg/ ./testvar
echo "-------------------- END UNIT TESTS --------------------"

# Remove Last Build
make clean
rm -rf config.* configure.* autom4te.cache Makefile.am *.log aclocal.* install-sh missing depcomp stamp-h1 configure configure~ compile \
src/.deps src/.dirstamp .deps src/cmd/.deps src/inc/.deps src/cmd/.dirstamp src/inc/.dirstamp Makefile.in Makefile
rm -rf ./etc ./var
