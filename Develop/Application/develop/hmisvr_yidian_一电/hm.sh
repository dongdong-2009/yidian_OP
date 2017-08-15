#!  /bin/sh
make distclean
/usr/local/Trolltech/Qte-4.8.4-arm/bin/qmake
#/usr/local/Trolltech/QtEmbedded-4.8.4-arm/bin/qmake
make -j8
cp hmisvr $UBUNTU_YD_OP_AC_APP_RUNTIME_DIR

