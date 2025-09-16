  #include <stdio.h>
  #include <unistd.h>
  #include <sys/wait.h>
  #include <string.h>
  #include <stdlib.h>

  /*

  CIS 452 01
  Kenan Velagic
  Joshua Johnson
  Project One - One Bad Apple

  */

  int main() {
      char input[500];
      pid_t pid;
      int k;

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
      scanf("%d", &k);
      getchar(); // Clear buffer

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

      int pipes[k][2];

      for (int i = 0; i < k; i++) {
        if (pipe(pipes[i]) < 0) {
          perror("Failed pipe creation.");
          exit(1);
        }
      }

      for (int i = 0; i < k; i++) {
        pid = fork();

        if (pid < 0) {
          perror("Unsuccessful fork system call.");
          exit(1);
        }

        if (pid == 0) {
          // Child Process

        } else {
          // Parent Process
          wait(NULL);
        }
      }
      
      return 0;
  }
