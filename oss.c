#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int totalProcesses = 1;
    int simultaneousProcesses = 1;
    int iterations = 1;

    int opt;
    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch (opt) {
            case 'n':
                totalProcesses = atoi(optarg);
                break;
            case 's':
                simultaneousProcesses = atoi(optarg);
                break;
            case 't':
                iterations = atoi(optarg);
                break;
            case 'h':
                printf("Usage: %s [-h] [-n proc] [-s simul] [-t iter]\n", argv[0]);
                printf("Options:\n");
                printf("  -h             : Show this help message\n");
                printf("  -n <proc>      : Number of total children to launch (default: 1)\n");
                printf("  -s <simul>     : Number of children to allow to run simultaneously (default: 1)\n");
                printf("  -t <iter>      : Number of iterations for user processes (default: 1)\n");
                return 0;
            default:
                fprintf(stderr, "Unknown option: %c\n", optopt);
                return 1;
        }
    }

    // Ensure positive values for parameters
    totalProcesses = (totalProcesses > 0) ? totalProcesses : 1;
    simultaneousProcesses = (simultaneousProcesses > 0) ? simultaneousProcesses : 1;
    iterations = (iterations > 0) ? iterations : 1;

    // Launch user processes
    while (totalProcesses > 0) {
        pid_t c = fork();
        if (c == 0) {
            // Child process
            char iterationsStr[10];
            snprintf(iterationsStr, sizeof(iterationsStr), "%d", iterations);
            execl("./user", "./user", iterationsStr, NULL);
            perror("execl");
            exit(1);
        } else if (c < 0) {
            // Fork failed
            perror("fork");
            return 1;
        } else {
            // Parent process
            totalProcesses--;
            if (totalProcesses % simultaneousProcesses == 0) {
                int status;
                wait(&status);
            }
        }
    }

    // Wait for all child processes to finish
    int status;
    while (wait(&status) > 0);

    return 0;
}

