# Made with C Project Manager
# Author: Caswall Engelsman (mail@cengelsman.com)

include config.mk
include project.mk

ARCHIVE_FILES := ${APP_NAME:%=lib%.a}
LIBRARY_FILES := ${APP_NAME:%=lib%.so}

all: set_debug_vars dep ${APP_NAME}

set_debug_vars:
	${eval DEBUG = -g3}

${APP_NAME}: %: ${SRC_PATH}/%.o ${COMP_O} ${UTILS_O}
	${call print,${GREEN}BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	${call print,${CYAN}CC $@}
	${Q}${CC} -c $< -o $@ ${CFLAGS}

static_library: dep ${ARCHIVE_FILES}

${ARCHIVE_FILES}: ${COMP_O} ${UTILS_O}
	${call print,${BROWN}AR $@}
	${Q}cd ${LIB_PATH}; ar -x *.a || true
	${Q}ar -cq $@ $^ ${shell find ${LIB_PATH} -name '*.o'}

set_pic:
	${eval CFLAGS += -fPIC}

shared_library: set_pic dep ${LIBRARY_FILES}

${LIBRARY_FILES}: ${COMP_O} ${UTILS_O}
	${call print,${BRIGHT_MAGENTA}LIB $@.${VERSION}}
	${Q}${CC} -shared -Wl,-soname,$@ -o $@.${VERSION} $^ ${LDFLAGS}
	${call print,${BRIGHT_CYAN}SYMLINK $@}
	${Q}ln -sf $@.${VERSION} $@

dep: ${DEPENDENCIES:%=${LIB_PATH}/%}

test:
	${MAKE} test -C tests

${LIB_PATH}/%:
	${eval WORD_LIST = ${subst /, ,$@}}
	${eval ORG = ${word 2, ${WORD_LIST}}}
	${eval PROJECT = ${word 3, ${WORD_LIST}}}
	${eval VERSION = ${word 4, ${WORD_LIST}}}
	${eval LIB_NAME = ${word 5, ${WORD_LIST}}}
	${eval NAME = ${word 1, ${subst ., ,${LIB_NAME:lib%=%}}}}

	${Q}mkdir -p ${dir $@}
	${call get_archive,${ORG}/${PROJECT},${VERSION},${LIB_NAME},$@}
	${Q}mkdir -p ${INCLUDE_PATH}
	${call get_header,${ORG}/${PROJECT},${VERSION},${NAME},${INCLUDE_PATH}}
	${Q}ln -sf ${shell pwd}/$@ ${shell pwd}/${LIB_PATH}/${LIB_NAME}

set_prod_vars:
	${eval DEBUG = -O3}

prod: set_prod_vars dep ${APP_NAME}

install: ${INSTALL_STEPS}

install_binary: ${INSTALL_PATH}/bin/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin/

install_static: ${ARCHIVE_FILES} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${ARCHIVE_FILES} ${INSTALL_PATH}/lib/

install_shared: ${APP_NAME:%=lib%.so.${VERSION}} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${APP_NAME:%=lib%.so.${VERSION}} ${INSTALL_PATH}/lib/

install_share_folder: ${APP_NAME:%=${INSTALL_PATH}/share/%}
	${call print,${GREEN}INSTALL $<}
	${Q}cp -R ${SHARE_PATH}/* ${APP_NAME:%=${INSTALL_PATH}/share/%}

${INSTALL_PATH}/%:
	${call print,${GREEN}MKDIR $@}
	${Q}mkdir -p $@

clean:
	${call print,${BRIGHT_CYAN}CLEAN ${APP_NAME}}
	${Q}${MAKE} -C tests clean
	${Q}${RM} ${APP_NAME} ${APP_NAME:%=${SRC_PATH}/%.o} ${APP_NAME:%=lib%.*} ${COMP_O} ${UTILS_O}

.PHONY: clean set_prod_vars set_debug_vars prod all set_pic install install_share_folder install_shared install_binary install_static dep
