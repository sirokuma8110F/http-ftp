#!/bin/bash
#---------------------------------------------------------------------------------
# Check Parameters
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# build and install ppc binutils
#---------------------------------------------------------------------------------

mkdir -p $target/binutils
cd $target/binutils

if [ ! -f configured-binutils ]
then
	../../binutils-$BINUTILS_VER/configure \
	--prefix=$prefix --target=$target --disable-nls --disable-shared --disable-debug \
	--disable-werror \
	--enable-poison-system-directories \
	--enable-plugins --enable-lto \
	--disable-werror $CROSS_PARAMS \
	|| { echo "Error configuing ppc binutils"; exit 1; }
	touch configured-binutils
fi

if [ ! -f built-binutils ]
then
	$MAKE || { echo "Error building ppc binutils"; exit 1; }
	touch built-binutils
fi

if [ ! -f installed-binutils ]
then
	$MAKE install || { echo "Error installing ppc binutils"; exit 1; }
	touch installed-binutils
fi
cd $BUILDDIR


#---------------------------------------------------------------------------------
# build and install mn10200 binutils
#---------------------------------------------------------------------------------

# Use modern config.sub for aarch64 host
cp binutils-$BINUTILS_VER/config.sub binutils-$MN_BINUTILS_VER/config.sub

mkdir -p mn10200/binutils
cd mn10200/binutils

if [ ! -f configured-binutils ]
then
	../../binutils-$MN_BINUTILS_VER/configure \
	--prefix=$prefix --target=mn10200 --disable-nls --disable-debug \
	--disable-multilib \
	--disable-werror $CROSS_PARAMS \
	|| { echo "Error configuing mn10200 binutils"; exit 1; }
	touch configured-binutils
fi

if [ ! -f built-binutils ]
then
	$MAKE || { echo "Error building mn10200 binutils"; exit 1; }
	touch built-binutils
fi

if [ ! -f installed-binutils ]
then
	$MAKE install || { echo "Error installing mn10200 binutils"; exit 1; }
	touch installed-binutils
fi

cd $BUILDDIR

#---------------------------------------------------------------------------------
# build and install just the c compiler
#---------------------------------------------------------------------------------
mkdir -p $target/gcc
cd $target/gcc

export gcc_cv_libc_provides_ssp=yes

if [ ! -f configured-gcc ]
then
	CFLAGS_FOR_TARGET="-O2 -ffunction-sections -fdata-sections" \
	CXXFLAGS_FOR_TARGET="-O2 -ffunction-sections -fdata-sections" \
	LDFLAGS_FOR_TARGET="" \
	../../gcc-$GCC_VER/configure \
	--enable-languages=c,c++,objc,lto \
	--enable-lto \
	--with-cpu=750 \
	--disable-nls --disable-shared --enable-threads=dkp --disable-multilib \
	--disable-win32-registry \
	--disable-libstdcxx-pch \
	--disable-libstdcxx-verbose \
	--enable-libstdcxx-time=yes \
	--enable-libstdcxx-filesystem-ts \
	--disable-tm-clone-registry \
	--disable-__cxa_atexit \
	--disable-libssp \
	--enable-cxx-flags='-ffunction-sections -fdata-sections' \
	--target=$target \
	--with-newlib \
	--with-headers=../../newlib-$NEWLIB_VER/newlib/libc/include \
	--prefix=$prefix \
	--with-bugurl="https://github.com/devkitpro/buildscripts/issues" --with-pkgversion="devkitPPC release 45.2" \
	$CROSS_PARAMS \
	$CROSS_GCC_PARAMS \
	$EXTRA_GCC_PARAMS \
        CFLAGS_FOR_TARGET="-O2 -ffunction-sections -fdata-sections" \
	|| { echo "Error configuring gcc stage 1"; exit 1; }
	touch configured-gcc
fi

if [ ! -f built-gcc-stage1 ]
then
	$MAKE all-gcc || { echo "Error building gcc stage1"; exit 1; }
	touch built-gcc-stage1
fi

if [ ! -f installed-gcc-stage1 ]
then
	$MAKE install-gcc || { echo "Error installing gcc stage1"; exit 1; }
	touch installed-gcc-stage1
fi

#---------------------------------------------------------------------------------
# build and install newlib
#---------------------------------------------------------------------------------
cd $BUILDDIR
mkdir -p $target/newlib
cd $target/newlib

unset CFLAGS
unset LDFLAGS

OLD_CC=$CC
OLD_CXX=$CXX
unset CC
unset CXX

if [ ! -f configured-newlib ]
then
	CFLAGS_FOR_TARGET="-O2 -ffunction-sections -fdata-sections -DCUSTOM_MALLOC_LOCK" \
	../../newlib-$NEWLIB_VER/configure \
	--target=$target \
	--prefix=$prefix \
	--enable-newlib-mb \
	--enable-newlib-register-fini \
	|| { echo "Error configuring newlib"; exit 1; }
	touch configured-newlib
fi

if [ ! -f built-newlib ]
then
	$MAKE || { echo "Error building newlib"; exit 1; }
	touch built-newlib
fi
if [ ! -f installed-newlib ]
then
	$MAKE install -j1 || { echo "Error installing newlib"; exit 1; }
	touch installed-newlib
fi

export CC=$OLD_CC
export CXX=$OLD_CXX

#---------------------------------------------------------------------------------
# build and install the final compiler
#---------------------------------------------------------------------------------

cd $BUILDDIR

cd $target/gcc

if [ ! -f built-stage2 ]
then
	$MAKE all || { echo "Error building gcc stage2"; exit 1; }
	touch built-stage2
fi

if [ ! -f installed-stage2 ]
then
	$MAKE install || { echo "Error installing gcc stage2"; exit 1; }
	touch installed-stage2
fi

rm -fr $prefix/$target/sys-include

#---------------------------------------------------------------------------------
# Install and build the gamecube crt and libogc
#---------------------------------------------------------------------------------

echo "installing linkscripts ..."
cp $BUILDSCRIPTDIR/dkppc/crtls/*.ld $prefix/$target/lib/

cd $BUILDDIR
