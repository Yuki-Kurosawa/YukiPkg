#! /bin/bash
export YPKG_VER=0.0.1

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

# Build Package
dh_make -p yukipkg_${YPKG_VER} --createorig 
dpkg-buildpackage -sa #> /dev/null

dpkg -I ../yukipkg_${YPKG_VER}*.deb 

sudo dpkg -i ../yukipkg_${YPKG_VER}*.deb > /dev/null
ypkg version
sudo apt purge yukipkg -y > /dev/null

rm -rvf ../yukipkg_${YPKG_VER}*.deb > /dev/null
rm -rvf ../yukipkg-dbgsym_${YPKG_VER}*.ddeb > /dev/null

# Remove Last Build
dh clean
find . -name "*.o"  | xargs rm -f
rm -rf config.* configure.* autom4te.cache Makefile.am *.log aclocal.* install-sh missing depcomp stamp-h1 configure configure~ compile \
src/.deps src/.dirstamp .deps src/cmd/.deps src/inc/.deps src/cmd/.dirstamp src/inc/.dirstamp Makefile.in Makefile
rm -rf ./etc ./var