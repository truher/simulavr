#
#  $Id$
#

EXTRA_DIST = spmtest.cfg spmtest.template run_test.sh testutil.h \
    testutil.c erasefunc.c erasepage.c writefunc.c writepage.c mk_pattern.py

export PYTHONPATH=$(srcdir)/../modules

check-local: spmtest

clean-local:
	rm -f spmtest.makefile page_pattern.h
	rm -f $(srcdir)/*.elf $(srcdir)/*.report $(srcdir)/*.output

spmtest: page_pattern.h
if PYTHON_USE
if USE_AVR_CROSS
	@PYTHON@ -m create_makefile -o $(srcdir)/spmtest.makefile \
	                            -c $(srcdir)/spmtest.cfg \
	                            -t $(srcdir)/spmtest.template
	$(MAKE) -f spmtest.makefile test
else
	@echo "  Configure could not find AVR cross compiling environment so spmtest"
	@echo "  can not be run."
endif
else
	@echo "  Configure could not find python on your system so spmtest"
	@echo "  can not be run."
endif

page_pattern.h: mk_pattern.py
if PYTHON_USE
	@PYTHON@ mk_pattern.py > page_pattern.h
else
	@echo "  Configure could not find python on your system so spmtest"
	@echo "  can not be run. (creating page_pattern.h)"
endif

.PHONY: spmtest

