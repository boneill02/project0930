C_SOURCES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))

OUT_DIR=bin
INC_DIR=include
OBJ_DIR=obj
SRC_DIR=src

CC=/usr/bin/gcc
CFLAGS=-g -w -I$(INC_DIR)
OUT_NAME=emu0930

out: objects
	$(CC) $(OBJ_DIR)/*.o -o $(OUT_DIR)/$(OUT_NAME) $(CFLAGS) -lSDL2 -lpthread

objects: $(C_SOURCES)
	$(CC) -c $< -o $@ $(CFLAGS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

run: out
	./$(OUT_DIR)/$(OUT_NAME)

clean:
	rm -rf $(OUT_DIR)/$(OUT_NAME) $(OBJ_DIR)/*.o
