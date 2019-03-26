# KallistiOS 1.2.0
#
# dccommon/Makefile
# 2003-2005 Viktor Gars
#

all: common

include $(KOS_BASE)/Makefile.rules

OBJS =	src/id3.o src/linkedlist.o src/cdda.o src/dccontrol.o src/gldraw.o src/dreamcast.o \
				src/menu.o src/plprint.o src/vmu.o src/timer.o src/rect.o src/point.o

KOS_LOCAL_CFLAGS = -I./include

clean:
	-rm -f $(OBJS)

common:	$(OBJS)
