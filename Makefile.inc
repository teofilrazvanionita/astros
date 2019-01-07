# Makefile.inc - common definitions used by all makefiles

CC = gcc
ASTROS_DIR = ../
ASTROS_INCL_DIR = ${ASTROS_DIR}include

CFLAGS = -g \
	   -Wall \
	   -Wno-sign-compare \
	   -Wno-unused-parameter \
	   -Wextra \
    

LDLIBS = -lpthread

RM = rm -f
