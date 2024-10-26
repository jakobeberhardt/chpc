CC = gcc
CFLAGS = -O2
LDFLAGS =
TARGET = array_processing

SRC = main.c
ASM_SRC = predicated_function.S speculative_function.S
OBJ = $(SRC:.c=.o) $(ASM_SRC:.S=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
