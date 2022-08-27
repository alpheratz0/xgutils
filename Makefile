.POSIX:
.PHONY: all clean install uninstall dist

include config.mk

all: xggen

xggen: xggen.o
	$(CC) $(LDFLAGS) -o xggen xggen.o $(LDLIBS)

clean:
	rm -f xggen xggen.o xggen-$(VERSION).tar.gz

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f xggen $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/xggen
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f xggen.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/xggen.1

dist: clean
	mkdir -p xggen-$(VERSION)
	cp -R COPYING config.mk Makefile README xggen.1 xggen.c xggen-$(VERSION)
	tar -cf xggen-$(VERSION).tar xggen-$(VERSION)
	gzip xggen-$(VERSION).tar
	rm -rf xggen-$(VERSION)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xggen
	rm -f $(DESTDIR)$(MANPREFIX)/man1/xggen.1
