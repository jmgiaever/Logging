CC = gcc
CFLAGS = -p
COPT = -O0
SRCS = main.c

all: main

main: $(SRCS) Makefile
	$(CC) $(CFLAGS) $(COPT) -o $@ $<  

clean: 
	rm -f *~ *.o *.exe *.s *.out main

compare:
	gnuplot ./Logging/logs/$(plot).plot
	ps2pdf ./Logging/logs/compare.ps ./Logging/logs/$(plot).pdf
	evince ./Logging/logs/$(plot).pdf
	rm ./Logging/logs/compare.ps

comparecln:
	rm -f ./Logging/logs/*.data
	rm -f ./Logging/logs/*.ps
	rm -f ./Logging/logs/*.pdf