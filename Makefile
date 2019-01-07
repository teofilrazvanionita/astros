# Makefile to build all programs in all subdirectories
#
# DIRS is a list of all subdirectories containing makefiles
#

#

DIRS = 	source

# Dummy targets for building and clobbering everything in all subdirectories

all:
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done

clean:
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
