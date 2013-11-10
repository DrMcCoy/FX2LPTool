include $(top_srcdir)/Makefile.common

# Pass the git version information to the compiler

VER_REVDESC = $(shell cat $(top_srcdir)/gitstamp/gitstamp)
VERSION_FLAGS = $(shell if test x$(VER_REVDESC) != "x"; then echo "-DFX2LPTOOL_REVDESC=\\\"$(VER_REVDESC)\\\""; fi)

VER_REV = $(shell cat $(top_srcdir)/gitstamp/gitstamp | cut -d '-' -f 2-)
VERSION_FLAGS += $(shell if test x$(VER_REV) != "x"; then echo "-DFX2LPTOOL_REV=\\\"$(VER_REV)\\\""; fi)

VER_DATE = $(shell date --utc '+%Y-%m-%dT%H:%M:%S')
VERSION_FLAGS += $(shell if test x$(VER_DATE) != "x"; then echo "-DFX2LPTOOL_BUILDDATE=\\\"$(VER_DATE)\\\""; fi)

AM_CXXFLAGS += $(VERSION_FLAGS)
AM_CFLAGS   += $(VERSION_FLAGS)

# Rebuild the version.lo when the git version changed
version.lo: $(top_srcdir)/gitstamp/gitstamp

bin_PROGRAMS = fx2lptool

noinst_HEADERS = \
                 types.hpp \
                 version.hpp \
                 util.hpp \
                 error.hpp \
                 fx2lp.hpp \
                 $(EMPTY)

fx2lptool_SOURCES = \
                  version.cpp \
                  util.cpp \
                  error.cpp \
                  fx2lp.cpp \
                  fx2lptool.cpp \
                  $(EMPTY)
