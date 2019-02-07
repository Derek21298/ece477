#
#	ECE 477 - Lab1 Makefile
#	Authors: Derek Haas, Dustin Knight, Alex Barnett


# Input files ============================================
TARGET1 = helloWorldLoop
TARGET2 = somethingCool
SRC1 = hello_world_loop
SRC2 = something_cool
OBJS = 
# ========================================================

all: $(SRC1).o $(SRC2).o
	gcc -o $(TARGET1) $(SRC1).o
	gcc -o $(TARGET2) $(SRC2).o

clean:
	rm -f $(SRC1).o $(TARGET1)
	rm -f $(SRC2).o $(TARGET2)
