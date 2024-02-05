#include<stdio.h>
int main(int argc, char *argv[]) {
	int itr = atoi(argv[1]);
	for (int i = 1; i<= itr; i++) {
		printf("User PID:%d PPID: %d Iterations:%d before sleeping\n", getpid(), getpid(), i);
		sleep(1);
		printf("User PID: %d PPID: %d Iterations:%d after sleeping\n", getpid(), getpid(), getpid(), i);
	}
return 0;
}
