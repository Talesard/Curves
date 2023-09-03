CC=clang++
CFLAGS=-o3 -fopenmp # -o3
SOURCE_DIR=src
BIN_DIR=bin
SOURCES=*.cpp
EXECUTABLE=app.exe

build:
	$(CC) $(CFLAGS) $(SOURCE_DIR)\\$(SOURCES) -o $(BIN_DIR)\$(EXECUTABLE)
run:
	$(BIN_DIR)\$(EXECUTABLE)
clean:
	rmdir /q /s $(BIN_DIR)
init:
	mkdir $(BIN_DIR)
help:
	@echo off && echo Available args: init, build, run, clean