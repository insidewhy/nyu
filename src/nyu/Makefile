.PHONY: build install clean test

default: build

-include Makefile.local

build:
	${MAKE} -C .obj

install:
	${MAKE} -C .obj install

reconfigure:
	rm -rf .obj.old
	mv .obj .obj.old
	./.obj.old/reconfigure
	rm -rf .obj.old

clean:
	rm -rf .obj Makefile

ifeq ($(wildcard test/Makefile),)
test: build
	${MAKE} -C .obj test
else
test: build
	${MAKE} -C test test
endif

uninstall:
	${MAKE} -C .obj uninstall
