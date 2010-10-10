.PHONY: test accept

outdir = .new.output
nyu    = ../.obj/nyu

test: nyu.out fail.out

nyu.out: meta.nyah nyah.nyah nyu.nyah ${nyu}
fail.out: fail.nyah ${nyu}

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
