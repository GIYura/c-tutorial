ASM = as
ASM_FLAGS = -g
LINKER = ld
TARGET = hello
RM = rm -rf

all: $(TARGET)

$(TARGET): hello.o
	@$(LINKER) $^ -o $@
	@echo 'Done!'

%.o: %.S
	@$(ASM) $(ASM_FLAGS) $^ -o $@

clean:
	@$(RM) *.o
	@$(RM) $(TARGET)
	@echo 'Cleaning ... Done!'
