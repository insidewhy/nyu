.PHONY: test accept

nyu    = ../.obj/nyu

test: self/stdout fail/stdout

self/stdout: self.nyah $(wildcard ../grammar/*.nyah) ${nyu}
fail/stdout: fail.nyah ${nyu}

%/stdout:
	@dir=`dirname $@`; \
	rm -rf .$$dir; \
	mkdir -p .$$dir; \
	${nyu} -I. -I../grammar -p -o .$$dir $< > .$@; \
	diff -r .$$dir $$dir
	@touch $@
	@echo $< succeeded

accept:
	@for f in $(wildcard .*/stdout) ; do \
		dir=`dirname $$f | sed 's/.//'`; \
		rm -rf $$dir; mv .$$dir $$dir; \
	done
