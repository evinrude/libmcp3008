.PHONY: lib test

default: all

all: lib test

lib:
	@make -C ./lib/ all

test:
	@make -C ./test/ all

clean:
	@make -C ./lib/ clean
	@make -C ./test/ clean

install:
	@make -C ./lib/ install

uninstall:
	@make -C ./lib/ uninstall
