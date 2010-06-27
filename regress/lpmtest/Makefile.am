#
#  $Id$
#

EXTRA_DIST = lpmtest.cfg lpmtest.template run_test.sh testutil.h \
    testutil.c simple.c

export PYTHONPATH=$(srcdir)/../modules

check-local: lpmtest

clean-local:
	rm -f lpmtest.makefile
	rm -f $(srcdir)/*.elf $(srcdir)/*.report $(srcdir)/*.output

lpmtest:
if PYTHON_USE
if USE_AVR_CROSS
	@PYTHON@ -m create_makefile -o $(srcdir)/lpmtest.makefile \
	                            -c $(srcdir)/lpmtest.cfg \
	                            -t $(srcdir)/lpmtest.template
	$(MAKE) -f lpmtest.makefile test
else
	@echo "  Configure could not find AVR cross compiling environment so lpmtest"
	@echo "  can not be run."
endif
else
	@echo "  Configure could not find python on your system so lpmtest"
	@echo "  can not be run."
endif

.PHONY: lpmtest


