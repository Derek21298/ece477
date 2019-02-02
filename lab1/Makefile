#
#	ECE 477 - Lab1 Makefile
#	Authors: Derek Haas, Dustin Knight, Alex Barnett


# Input files ============================================
TARGET = helloWorldLoop
SRC = hello_world_loop.c
OBJS = 
# ========================================================

ALLOBJS := $(SRC:.c=.o) $(OBJS)

all: $(ALLOBJS)
	gcc -o $(TARGET) $(ALLOBJS)

clean:
	rm -f $(SRC:.c=.o) $(TARGET)
