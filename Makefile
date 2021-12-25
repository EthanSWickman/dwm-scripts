jifbar: status_bar.c battery_status.o time_status.o updates_status.o
	gcc -g -std=c99 -Wall -l X11 -o jifbar status_bar.c battery_status.o time_status.o updates_status.o
battery_status.o: battery_status.h battery_status.c
	gcc -c battery_status.c
time_status.o: time_status.h time_status.c
	gcc -c time_status.c
updates_status.o: updates_status.h updates_status.c
	gcc -c updates_status.c
clean: 
	rm jifbar *.o
install: jifbar
	mkdir -p /usr/local/bin
	cp -f ./jifbar /usr/local/bin/jifbar
	chmod 755 /usr/local/bin/jifbar
uninstall: 	
	rm -f /usr/local/bin/jifbar

