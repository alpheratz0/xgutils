# Copyright (C) 2022 <alpheratz99@protonmail.com>
# This program is free software.

VERSION=0.1.0
CC=cc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -Os -DVERSION=\"$(VERSION)\"
PREFIX=/usr/local
LDFLAGS=-s
MANPREFIX=$(PREFIX)/share/man
