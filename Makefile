.SILENT:

subfiles = lab4b.c Makefile README sanitycheck

default:
	gcc -o lab4b -g lab4b.c -lmraa -lm
check:
	./sanitycheck
clean:
	rm -rf lab4b
dist:
	tar -zcvf lab4b-604489201.tar.gz $(subfiles)