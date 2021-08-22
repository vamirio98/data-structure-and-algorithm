.PHONY: compile build debug file rw dfile drw clean

TARGET = test

CC = g++

build:
	$(CC) -Wall -O2 $(SRC) -o $(TARGET)

debug:
	$(CC) -Wall -g $(SRC) -o $(TARGET)

file: SRC = test_File.cpp File.cpp
file: $(SRC:cpp=o) build

rw: SRC = test_RW.cpp File.cpp File_reader.cpp File_writer.cpp
rw: build

dfile: SRC = test_File.cpp File.cpp
dfile: $(SRC:cpp=o) debug

drw: SRC = test_RW.cpp File.cpp File_reader.cpp File_writer.cpp
drw: $(SRC:cpp=o) debug

clean:
	rm $(TARGET)
