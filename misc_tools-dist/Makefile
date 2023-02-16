.POSIX:

DEST = /usr/bin
SRC = afn.c fr.c ipc.c pw.c np.c
EXES = $(SRC:.c=)

all: $(EXES)

options:
	@echo "DEST    = $(DEST)"
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "CC      = $(CC)"
	@echo "SRC     = $(SRC)"
	@echo "EXES    = $(EXES)"

clean:
	rm -f $(EXES)

install: all
	cp -f $(EXES) $(DEST)

uninstall:
	@$(foreach EXE,$(EXES), rm -f $(DEST)/$(EXE))

dist: clean
	mkdir -p misc_tools-dist
	cp -R README TODO Makefile common.h $(SRC) misc_tools-dist
	tar -cf - misc_tools-dist | gzip > misc_tools.tar.gz
	rm -rf misc_tools-dist

afn:
	$(CC) $(CFLAGS) $@.c -o $@
	
fr:
	$(CC) $(CFLAGS) $@.c -o $@

ipc:
	$(CC) $(CFLAGS) $@.c -o $@

pw:
	$(CC) $(CFLAGS) $@.c -o $@

np:
	$(CC) $(CFLAGS) $@.c -o $@

.PHONY: all options clean install uninstall dist
