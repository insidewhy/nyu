.PHONY: test accept

outdir = .new.output
nyu    = ../.obj/nyu

test: nyah.out

nyah.out: nyah.nyah grammar.nyah ${nyu}

%.out:
	@rm -rf ${outdir}
	@mkdir -p ${outdir}
	@${nyu} -I. -p -o ${outdir} $< > ${outdir}/$@
	@for f in ${outdir}/*.out ; do diff `basename $$f` $$f || exit 1 ; done
	@touch $@
	@rm ${outdir}/*.out
	@echo $< succeeded

accept:
	mv ${outdir}/* .
