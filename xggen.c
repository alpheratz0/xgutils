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

	 _________________
	( I am inevitable )
	 -----------------
	  o
	   o

	      ■
	        ■
	    ■ ■ ■

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_COLUMNS                    (300)
#define DEFAULT_ROWS                       (300)
#define DEFAULT_ALIVE_PROB                 (0.3)

static inline float
frand(void)
{
	return ((float)(rand())) / RAND_MAX;
}

static void
usage(void)
{
	puts("usage: xggen [-hv] [-c columns] [-r rows] [-p alive_probability]");
	exit(0);
}

static void
version(void)
{
	puts("xggen version "VERSION);
	exit(0);
}

static const char *
enotnull(const char *str, const char *name)
{
	if (NULL == str) {
		fprintf(stderr, "xggen: %s cannot be null", name);
		exit(1);
	}

	return str;
}

int
main(int argc, char **argv)
{
	int x, y, r, c;
	float p;

	r = DEFAULT_ROWS;
	c = DEFAULT_COLUMNS;
	p = DEFAULT_ALIVE_PROB;

	while (++argv, --argc > 0) {
		if (!strcmp(*argv, "-h")) usage();
		else if (!strcmp(*argv, "-v")) version();
		else if (!strcmp(*argv, "-r")) --argc, r = atoi(enotnull(*++argv, "rows"));
		else if (!strcmp(*argv, "-c")) --argc, c = atoi(enotnull(*++argv, "columns"));
		else if (!strcmp(*argv, "-p")) --argc, p = atof(enotnull(*++argv, "alive probability"));
	}

	if (r <= 0 || c <= 0 || p < 0) {
		fprintf(
			stderr, "xggen: invalid %s supplied\n",
			r <= 0 ?
				"rows" :
				c <= 0 ?
					"columns" :
					"alive probability"
		);
		exit(1);
	}

	srand((unsigned)(getpid()));
	printf("%dx%d\n", c, r);

	if (p == 0) return 0;

	for (y = 0; y < r; ++y)
		for (x = 0; x < c; ++x)
			if (frand() < p)
				printf("%d,%d\n", x, y);

	return 0;
}
