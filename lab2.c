#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

   pid_t pid; 
   int status;
   const int numberOfChildren = 11;

   char *commands[][3]={
    //This will show a list that is (-l) detailed of your file directory.
    {"ls", "-l", NULL},
    //This is a simple command to print my name in the terminal
    {"echo", "Kyle Dennewith", NULL},
    //This will give you info on what the echo command does
    {"man", "echo", NULL},
    //This will give execution privleges to the randomShellFile Shell Script.
    {"chmod +x", "randomShellFile.sh", NULL},
    //This will display the routing to a certain address, IP's to get to destination, max 5 lines.
    {"ping", "my.cwu.edu", NULL},
    //Prints the amount of time your system has been on.
    {"uptime", NULL},
    //This will display your current username for the system you're on.
    {"whoami", NULL},
    //Will show the history of commands that wen't through.
    {"bash -c history", NULL},
    //Making a directory folder called RandomFolder_DELETE.
    {"mkdir", "RandomFolder_DELETE", NULL},
    //Removing a file named RandomFolder_DELETE made from mkdir above.
    {"rm -r", "RandomFolder_DELETE", NULL},
    //This will show the disk usage of your system in a human formatted text (-h)
    {"df", "-h", NULL},
   };

    //Print statement just to show the parent proceess ID like in the example in class.
    printf("Parent process PID: %d\n", getpid());

    for(int i = 0; i < numberOfChildren; i++){
        pid = fork();

        if(pid < 0){
          perror("Fork Failed, please try again.");// Will send if pid does not exist since it is not a positive integer.
            exit(EXIT_FAILURE);  
        } else if (pid == 0){
            //The Child process PID's
            printf("Child processes PID: %d - Executing commands: %s\n", getpid(), commands[i][0]);
            execvp(commands[i][0], commands[i]);
            //This will execute if the execvp catches an error.
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    }

    //This is the wait loop, the parent process will wait for each child process to end
    // because of the wait(&status) which returns the exit status of the program. Once
    // it's true that means the process id has been passed into pid. Also added exit status.
    while((pid = wait(&status)) > 0){
        printf("Child procces with PID %d finished: Exit Code %d\n", pid, WTERMSIG(status));
    }

    return 0;
}