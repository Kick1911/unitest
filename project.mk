APP_NAME = unitest
VERSION = 0.0.1
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

STATIC_DEP =
SHARED_DEP =

DEPENDENCIES =

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}