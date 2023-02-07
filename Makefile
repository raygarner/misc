.POSIX:

DEST = /usr/bin
EXES = afn cf fb fr ipc md npc pw

all: $(EXES)

options:
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "CC      = $(CC)"

clean:
	rm -f $(EXES)

install: all
	cp -f $(EXES) $(DEST)

uninstall:
	@$(foreach EXE,$(EXES), rm -f $(DEST)/$(EXE))

afn:
	$(CC) $(CFLAGS) $@.c -o $@
	
cf:
	$(CC) $(CFLAGS) $@.c -o $@

fb:
	$(CC) $(CFLAGS) $@.c -o $@

fr:
	$(CC) $(CFLAGS) $@.c -o $@

ipc:
	$(CC) $(CFLAGS) $@.c -o $@

md:
	$(CC) $(CFLAGS) $@.c -o $@

npc:
	$(CC) $(CFLAGS) $@.c -o $@

pw:
	$(CC) $(CFLAGS) $@.c -o $@

.PHONY: all options clean install uninstall
