SRCDIR=src

default: all

all:
	@cd $(SRCDIR) && make

clean:
	@cd $(SRCDIR) && make clean
	@rm -rf *~ core

distclean: clean
	@cd $(SRCDIR) && make distclean

.PHONY: all clean distclean
