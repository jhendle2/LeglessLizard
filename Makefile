CC:=gcc
CFLAGS:=-g -Wall -std=gnu17

SRC:=./src
OBJ:=./obj

SRCS:=$(wildcard $(SRC)/*.c)
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

APP:=lglz
.PHONY: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

FILE:=./examples/hello.llz
test: $(APP)
	./$(APP) $(FILE)

clean:
	rm -r $(APP) $(OBJS)