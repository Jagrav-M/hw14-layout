CFLAGS = -std=c11 -g -Wall --pedantic -Wshadow -Wvla -Wextra -Wunreachable-code
OBJS = main.o hw14.o util.o
HEADERS = hw14.h
APP = layout

$(APP): $(OBJS)
	$(CC) $(CFLAGS) *.o -o $(APP)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf $(APP)
