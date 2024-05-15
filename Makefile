# files to be used
SRC = ./src/*.c
INC = ./include/
OBJ = ./*.o

# variables
COMPFLAGS=-Wall -Wextra -pedantic
LINKFLAGS= 
TARGET=chexdumb

all:$(TARGET)

$(TARGET): obj
	cc -o $@ $(OBJ) $(LINKFLAGS)

obj:
	cc $(COMPFLAGS) -I $(INC) -c $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)
