CC      = cc
CFLAGS  = -std=c99 -pedantic -Wall -Wextra -Os
PREFIX  = /usr/local

all: xggen

.c.o:
	${CC} -c ${CFLAGS} $<

xggen: xggen.o
	${CC} -o $@ $<

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f xggen ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/xggen
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f xggen.1 ${DESTDIR}${MANPREFIX}/man1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/xggen.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/xggen
	rm -f ${DESTDIR}${MANPREFIX}/man1/xggen.1

clean:
	rm -f xggen xggen.o

.PHONY: all clean install uninstall
