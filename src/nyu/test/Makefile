.PHONY: test accept

nyu    = ../.obj/nyu

test: self/stdout parse_fail/stdout bad_include/stdout class/stdout \
	  order/stdout missing_rule/stdout

self/stdout: self.nyah $(wildcard ../grammar/*.nyah) ${nyu}
parse_fail/stdout: parse_fail.nyah ${nyu}
class/stdout: class.nyah ${nyu}
bad_include/stdout: bad_include.nyah ${nyu}
order/stdout: order.nyah ${nyu}
missing_rule/stdout: missing_rule.nyah ${nyu}

%/stdout:
	@dir=`dirname $@`; \
	rm -rf .$$dir; \
	mkdir -p .$$dir; \
	${nyu}  2>.$$dir/stderr >.$@ -I. -I../grammar -p -o .$$dir $<; \
	diff -r $$dir .$$dir && rm -rf .$$dir
	@touch $@
	@echo $< succeeded

accept:
	@for f in $(wildcard .*/stdout) ; do \
		dir=`dirname $$f | sed 's/.//'`; \
		rm -rf $$dir; mv .$$dir $$dir; \
	done
