.POSIX:
.PHONY: all clean install uninstall dist

include config.mk

all: xggen c2xg

xggen: xggen.o
	$(CC) $(LDFLAGS) -o xggen xggen.o $(LDLIBS)

c2xg: c2xg.o
	$(CC) $(LDFLAGS) -o c2xg c2xg.o $(LDLIBS)

clean:
	rm -f xggen c2xg xggen.o c2xg.o xgutils-$(VERSION).tar.gz

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f xggen $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/xggen
	cp -f c2xg $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/c2xg
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f xggen.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/xggen.1
	cp -f c2xg.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/c2xg.1

dist: clean
	mkdir -p xgutils-$(VERSION)
	cp -R COPYING config.mk Makefile README xggen.1 \
		xggen.c c2xg.1 c2xg.c xgutils-$(VERSION)
	tar -cf xgutils-$(VERSION).tar xgutils-$(VERSION)
	gzip xgutils-$(VERSION).tar
	rm -rf xgutils-$(VERSION)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xggen
	rm -f $(DESTDIR)$(PREFIX)/bin/c2xg
	rm -f $(DESTDIR)$(MANPREFIX)/man1/xggen.1
	rm -f $(DESTDIR)$(MANPREFIX)/man1/c2xg.1
