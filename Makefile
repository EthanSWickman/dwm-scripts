statusbar: status_bar.c battery_status.o time_status.o updates_status.o
	gcc -g -std=c99 -Wall -l X11 -o bar status_bar.c battery_status.o time_status.o updates_status.o
battery_status.o: battery_status.h battery_status.c
	gcc -c battery_status.c
time_status.o: time_status.h time_status.c
	gcc -c time_status.c
updates_status.o: updates_status.h updates_status.c
	gcc -c updates_status.c
clean: 
	rm bar *.o