CC = gcc
RM = rm -rf
STANDARD = -std=c99
OPTIMIZATION = -O0
#LIB = -lpthread
LIB += -lrt
#-save-temps - to save all compiler files
#-Werror - treat all warning as error
CFLAGS = $(STANDARD) -c -g $(OPTIMIZATION) -MD -Wall -pedantic
LDFLAGS = 
SRC = $(wildcard *.c)
OBJ = $(addsuffix .o, $(basename $(SRC)))
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(LDFLAGS) $^ -o $@ $(LIB)
	@echo 'Done!'

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@

include $(wildcard *.d)

clean:
	@$(RM) *.o *.d *.out *.s *.i
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'
