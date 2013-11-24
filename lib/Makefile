SOURCES:= libmcp3008.c
HEADERS:= libmcp3008.h
OBJECTS = libmcp3008.o
LIB_VERSION:= 1
LIB_NAME:= libmcp3008.so
LIB_DIR:= /usr/lib
INCLUDES:= -I.
CC:= gcc
CC_OPTS:= -fPIC -c -Wall
LD:= ld
LD_OPTS:= -shared -lc

default: all

all:
	@echo "  CC $(shell pwd)/$(SOURCES)"
	@$(CC) $(INCLUDES) $(CC_OPTS) $(SOURCES)
	@echo "  LD $(shell pwd)/$(LIB_NAME)"
	@$(LD) $(LD_OPTS) -soname=$(LIB_NAME).$(LIB_VERSION) $(OBJECTS) -o $(LIB_NAME).$(LIB_VERSION).0
	@ln -fs $(LIB_NAME).$(LIB_VERSION).0 $(LIB_NAME)
	@ln -fs $(LIB_NAME).$(LIB_VERSION).0 $(LIB_NAME).$(LIB_VERSION)

install:
	@cp -fv $(LIB_NAME).$(LIB_VERSION).0 $(LIB_DIR)/
	@ln -fvs $(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION).0 $(LIB_DIR)/$(LIB_NAME)
	@ln -fvs $(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION).0 $(LIB_DIR)/$(LIB_NAME).$(LIB_VERSION)
	@cp -fv $(HEADERS) /usr/include/

uninstall:
	@rm -fv $(LIB_DIR)/$(LIB_NAME)*
	@rm -rv /usr/include/$(HEADERS)

clean:
	@rm -fv $(LIB_NAME).$(LIB_VERSION).0 $(LIB_NAME) $(LIB_NAME).$(LIB_VERSION) $(OBJECTS)
