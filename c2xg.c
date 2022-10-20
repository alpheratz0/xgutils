/*
	Copyright (C) 2022 <alpheratz99@protonmail.com>

	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License version 2 as published by the
	Free Software Foundation.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place, Suite 330, Boston, MA 02111-1307 USA

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/file.h>

#define DEFAULT_COLUMNS                    (300)
#define DEFAULT_ROWS                       (300)

static void
die(const char *fmt, ...)
{
	va_list args;

	fputs("c2xg: ", stderr);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

static void
usage(void)
{
	puts("usage: c2xg [-hv] [-c columns] [-r rows] [cells_file]");
	exit(0);
}

static void
version(void)
{
	puts("c2xg version "VERSION);
	exit(0);
}

static const char *
enotnull(const char *str, const char *name)
{
	if (NULL == str)
		die("%s cannot be null", name);
	return str;
}

int
main(int argc, char **argv)
{
	const char *cpath;
	FILE *fp;
	int x, y, r, c, ch;

	r = DEFAULT_ROWS;
	c = DEFAULT_COLUMNS;
	cpath = NULL;
	x = y = 0;

	while (++argv, --argc > 0) {
		if ((*argv)[0] == '-' && (*argv)[1] != '\0' && (*argv)[2] == '\0') {
			switch ((*argv)[1]) {
				case 'h': usage(); break;
				case 'v': version(); break;
				case 'r': --argc; r = atoi(enotnull(*++argv, "rows")); break;
				case 'c': --argc; c = atoi(enotnull(*++argv, "columns")); break;
				default: die("invalid option %s", *argv); break;
			}
		} else {
			if (cpath != NULL)
				die("unexpected argument: %s", *argv);
			cpath = *argv;
		}
	}

	if (r <= 0)
		die("invalid number of rows");

	if (c <= 0)
		die("invalid number of columns");

	if (NULL == cpath)
		die("you must specify a path");

	if (NULL == (fp = fopen(cpath, "r")))
		die("can't open file: %s", cpath);

	printf("%dx%d\n", c, r);

	while ((ch = getc(fp)) != EOF) {
		switch (ch) {
			case '!':
				/* this is a comment, skip forward */
				while ((ch = getc(fp)) != '\n')
					if (ch == EOF)
						goto end;
				break;
			case '\n':
				++y, x = 0;
				break;
			case 'O':
				printf("%d,%d\n", ++x, y);
				break;
			default:
				++x;
				break;
		}
	}

end:
	fclose(fp);

	return 0;
}
