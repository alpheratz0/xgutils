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
#include <sys/file.h>

int
main(int argc, char **argv)
{
	const char *cpath;
	FILE *fp;
	char c;
	int x, y;

	if (argc < 2) return 1;

	cpath = *++argv;
	fp = fopen(cpath, "r");
	x = y = 0;

	printf("1000x1000\n");

	while ((c = getc(fp)) != EOF) {
		if (c == '!')  {
			while (1) {
				c = getc(fp);
				if (c == EOF)
					return 0;

				if (c == '\n') {
					break;
				}
			}
			continue;
		}

		if (c == '\n') {
			x = 0;
			++y;
			continue;
		}

		if (c == 'O') {
			printf("%d,%d\n", x, y);
		}

		++x;
	}

	return 0;
}
