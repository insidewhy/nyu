.PHONY: test accept

nyu    = ../.obj/nyu

test: fail.out nyu.out

nyu.out: meta.nyah nyah.nyah nyu.nyah ${nyu}
fail.out: fail.nyah ${nyu}

%.out:
	@rm -rf .$@
	@mkdir -p .$@
	@${nyu} -I. -p -o .$@ $< > .$@/$@
	@for f in .$@/*.out ; do diff `basename $$f` $$f || exit 1 ; done
	@touch $@
	@rm .$@/*.out
	@echo $< succeeded

accept:
	mv .*.out/* .
