CC=gcc
OBJS=tool/AsciiArtTool.o RLEList.o tool/main.o
EXEC=AsciiArtTool
DEBUG=#assign -g for debug
CFLAGS=-std=c99 -Wall -Werror -pedantic-errors -I/home/mtm/public/2122b/ex1 -Itool -DNDEBUG $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o:tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
RLEList.o:RLEList.c RLEList.h
main.o:tool/main.c tool/AsciiArtTool.h RLEList.h

clean:
	rm -f $(OBJS) $(EXEC)