.SILENT:

subfiles = lab4b.c Makefile README sanitycheck.sh

default:
	gcc -o lab4b -g lab4b.c -lmraa -lm
check:
	chmod a+x sanitycheck.sh
	./sanitycheck.sh 604-489-201
clean:
	rm -rf lab4b
dist:
	tar -zcvf lab4b-604-489-201.tar.gz $(subfiles)