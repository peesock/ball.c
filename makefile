CC=gcc
BIN=ballc

all: build

build:
	$(CC) main.c -lm -o $(BIN)

clean:
	rm -f $(BIN)

# install: build
# ifneq ($(shell id -u), 0)
# 	@echo "You must be root"
# else
# 	cp $(BIN) /usr/local/bin/$(BIN)
# 	chmod +x /usr/local/bin/$(BIN)
# endif
#
# uninstall: clean
# ifneq ($(shell id -u), 0)
# 	@echo "You must be root"
# else
# 	rm -f /usr/local/bin/$(BIN)
# endif

