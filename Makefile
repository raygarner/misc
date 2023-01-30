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
	$(CC) -Wall cf.c -o cf

fb:
	$(CC) -Wall fb.c -o fb

fr:
	$(CC) -Wall fr.c -o fr

ipc:
	$(CC) -Wall ipc.c -o ipc

md:
	$(CC) -Wall md.c -o md

npc:
	$(CC) -Wall npc.c -o npc

pw:
	$(CC) -Wall pw.c -o pw
