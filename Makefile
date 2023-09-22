.POSIX:
.PHONY: all clean install uninstall dist

include config.mk

all: xggen c2xg

xggen: src/xggen.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o xggen src/xggen.c

c2xg: src/c2xg.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o c2xg src/c2xg.c

clean:
	rm -f xggen c2xg xgutils-$(VERSION).tar.gz

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f xggen $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/xggen
	cp -f man/xggen.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/xggen.1
	cp -f c2xg $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/c2xg
	cp -f man/c2xg.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/c2xg.1

dist: clean
	mkdir -p xgutils-$(VERSION)
	cp -R COPYING config.mk Makefile README man src \
		xgutils-$(VERSION)
	tar -cf xgutils-$(VERSION).tar xgutils-$(VERSION)
	gzip xgutils-$(VERSION).tar
	rm -rf xgutils-$(VERSION)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xggen
	rm -f $(DESTDIR)$(MANPREFIX)/man1/xggen.1
	rm -f $(DESTDIR)$(PREFIX)/bin/c2xg
	rm -f $(DESTDIR)$(MANPREFIX)/man1/c2xg.1
