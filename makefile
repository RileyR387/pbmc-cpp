# Author: Riley Raschke
# © 2020 rrappsdev.com

.DEFAULT_GOAL := build

TARGET = pbmc
CC = g++
CFLAGS = -std=c++0x #-ggdb -Wall
SRC_INCLUDE = src
INC =include
DEST=bin
OBJ_DIR=obj
mkd=@mkdir
UNAME_S := $(shell uname -s)
IS_ALPINE := $(shell test -f /etc/alpine-release && echo yes)

#$(info $$IS_ALPINE is [${IS_ALPINE}])

THREAD_LIB :=
ifeq ($(UNAME_S),Darwin)
	THREAD_LIB = boost_thread-mt
else ifeq ($(IS_ALPINE),yes)
	THREAD_LIB = boost_thread-mt
else
	THREAD_LIB = boost_thread
endif

build: clean-all BigInt.o PBnumbers.o PBgenerator.o exec

exec:
	$(mkd) -p $(DEST)
	$(CC) $(CFLAGS) -I $(SRC_INCLUDE) \
		-o $(DEST)/$(TARGET) $(SRC_INCLUDE)/main.cpp \
		$(OBJ_DIR)/PBnumbers.o $(OBJ_DIR)/PBgenerator.o $(OBJ_DIR)/BigInt.o \
		-l boost_program_options -l pthread -l boost_system -l $(THREAD_LIB) -l boost_timer

PBnumbers.o:
	$(CC) $(CFLAGS) -I $(SRC_INCLUDE) -o $(OBJ_DIR)/PBnumbers.o \
		-c $(SRC_INCLUDE)/PBnumbers.cpp

PBgenerator.o:
	$(CC) $(CFLAGS) -I $(SRC_INCLUDE) -o $(OBJ_DIR)/PBgenerator.o \
		-c $(SRC_INCLUDE)/PBgenerator.cpp \
		-l boost_thread -l boost_system

BigInt.o:
	$(mkd) -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(SRC_INCLUDE) -o $(OBJ_DIR)/BigInt.o -c $(SRC_INCLUDE)/BigInt.cpp

clean-all: clean
	$(RM) $(DEST)/$(TARGET)

clean:
	ulimit -c unlimited ;
	$(RM) core $(OBJ_DIR)/*.o

