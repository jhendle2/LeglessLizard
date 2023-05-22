CC:=gcc
CFLAGS:=-g -Wall -std=gnu17

SRC:=./src
OBJ:=./obj

SRCS:=$(wildcard $(SRC)/*.c)
HDRS:=$(wildcard $(SRC)/*.h)
OBJS:=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

$(OBJ)/%.o: $(SRC)/%.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

APP:=lglz
.PHONY: $(APP)

$(APP): $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

FILE:=./examples/hello.llz
test: $(APP)
	./$(APP) $(FILE)

clean:
	rm -r $(APP) $(OBJS)

valgrind: $(APP)
	valgrind -s --track-origins=yes --leak-check=full ./$(APP) $(FILE)