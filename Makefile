
all:
	gcc -o chat_room chat_room.c

clean:
	find . -type f ! -name 'chat_room.c' -delete
