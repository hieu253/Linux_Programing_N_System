.PHONY: all clean mk_shared mk_objs install

LIB_NAME := test

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs
LIB_DIR := $(CUR_DIR)/libs
LIB_STATIC := $(LIB_DIR)/static
LIB_SHARED := $(LIB_DIR)/shared

CC := gcc
INC_FLAGS := -I $(INC_DIR)

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(INC_FLAGS)

mk_shared:
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o -o $(LIB_SHARED)/lib$(LIB_NAME).so

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/math.o $(OBJ_DIR)/hello.o

install:
	cp -f $(LIB_SHARED)/lib$(LIB_NAME).so /usr/lib
	

all: mk_objs mk_shared  mk_static install
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library
	$(CC)  $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/lib$(LIB_NAME).so
	rm -rf $(LIB_STATIC)/lib$(LIB_NAME).a
	rm -rf $(BIN_DIR)/use-shared-library
	rm -rf $(BIN_DIR)/statically-linked

