CC = gcc
CFLAGS = -Wall -Wextra 

all: user oss

user: user.c
	$(CC) $(CFLAGS) -o user user.c

oss: oss.c
	$(CC) $(CFLAGS) -o oss oss.c

clean: 
	rm -f user oss
