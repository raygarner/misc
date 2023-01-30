DEST = /usr/bin
CFLAGS = -Wall
EXES = cf fb fr ipc md npc pw

all: $(EXES)

clean:
	rm -f $(EXES)

install: all
	cp -f $(EXES) $(DEST)

uninstall:
	rm -f $(DEST)/cf $(DEST)/fb $(DEST)/fr $(DEST)/ipc $(DEST)/md \
	    $(DEST)/npc $(DEST)/pw

cf:
	$(CC) $(CFLAGS) cf.c -o cf

fb:
	$(CC) $(CFLAGS) fb.c -o fb

fr:
	$(CC) $(CFLAGS) fr.c -o fr

ipc:
	$(CC) $(CFLAGS) ipc.c -o ipc

md:
	$(CC) $(CFLAGS) md.c -o md

npc:
	$(CC) $(CFLAGS) npc.c -o npc

pw:
	$(CC) $(CFLAGS) pw.c -o pw
