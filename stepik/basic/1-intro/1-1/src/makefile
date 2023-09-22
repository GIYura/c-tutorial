CC = gcc
RM = rm -rf
STANDARD = -std=c99
OPTIMIZATION = -O0
CFLAGS = $(STANDARD) -c -g $(OPTIMIZATION) -MD -Wall -pedantic
LDFLAGS = 
SRC = $(wildcard *.c)
OBJ = $(addsuffix .o, $(basename $(SRC)))
TARGET = hello

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo 'Done!'

%.o: %.c 
	@$(CC) $(CFLAGS) $< -o $@

include $(wildcard *.d)

clean:
	@$(RM) *.o *.d *.out *.i *.s
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'

