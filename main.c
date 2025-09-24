#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define MAXMSGLENGTH 500

/*

CIS 452 01
Kenan Velagic
Joshua Johnson
Project One - One Bad Apple

*/

int main() {
    char input[500];
    pid_t pid;
    int numProcesses;

    /*
    .
    .
    .
      Prompt user to enter the number of nodes for the
      circular ring. Store the value in var 'k', which will
      later be used to create that many processes and pipes.
    .
    .
    .
    */

    printf("Enter the number of nodes: ");
    scanf("%d", &numProcesses);
    getchar();  // Clear buffer

    /*
    .
    .
    .
      After getting the number of nodes k, we create k pipes.
      Each pipe will connect one node to the next.
       - pipes[i][0] is the read end of pipe i
       - pipes[i][1] is the write end of pipe i
      These pipes allow each child process (node) to receive a message
      from the previous, and send it to the next node in the ring.
    .
    .
    .
    */

    puts("Enter message you would like to send");
    fgets(input, sizeof(input), stdin);

    int pipes[numProcesses][2];

    for (int i = 0; i < numProcesses; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("Failed pipe creation.");
            exit(1);
        }
    }

    int nodeId = 0;

    for (int i = 1; i < numProcesses; i++) {
        pid = fork();
        if (pid < 0) {
            perror("Unsuccessful fork system call.");
            exit(1);
        }
        if (pid == 0) {
            nodeID = i;
            break;
        }
    }
    int next = (nodeID + 1) % numProcesses
    int readFd = pipes[nodeID][READ_END];  // read from predecessor
    int writeFd = pipes[next][WRITE_END];    // write to next

    // close all other pipes
    for (int j = 0; j < numProcesses; ++j) {
        if (j != nodeID) close(pipes[j][0]);
        if (j != (nodeID + 1) % numProcesses) close(pipes[j][1]);
    }
    

    // ring loop
    while (1) {
    }
    return 0;
}
