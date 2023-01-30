all: cf fb fr ipc md npc pw

clean:
	rm -f cf fb fr ipc md npc pw

install: all
	cp -f cf fb fr ipc md npc pw /usr/bin

uninstall:
	rm -f /usr/bin/cf /usr/bin/fb /usr/bin/fr /usr/bin/ipc /usr/bin/md \
	    /usr/bin/npc /usr/bin/pw

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
