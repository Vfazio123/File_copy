/*
// Name: Vincent Fazio
// Class: CSC 4210
// Date: 2/16/21
// About: Forking the parent process, the child process is used to read a file, copy its contents to another file thats being written.

// Compile Instructions: gcc fazio_filecopy.c
//                  Run: ./a.out <input file> <output file>
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc == 3) {
        //Forking parent process
        pid_t cpid = fork();

        //Checking for pipe failure
        if(cpid < 0){
            perror("Error: Pipe Failed");
            exit(0);
        }

        //Declaring varibles for files and buffer file
        FILE *INPUT, *OUTPUT;
        char mystring[10000];
        INPUT = fopen(argv[1], "r");
        OUTPUT = fopen(argv[2], "w+");
        //If parent_id > 0 wait
        if(cpid > 0){
            //Reading from stdin and putting it into buffer (mystring)
            while(fgets(mystring, 10000, INPUT)) {
                //prints to command line
                puts(mystring);
            }
            wait(0);
           
        //else, let child process copy the file
        } else {
            //open both files
            //if input file has nothing (exit)
            if (INPUT == NULL) { 
                perror ("Error opening file");
                exit(0);
            }

            // fgets/fputs - Reading characters from stream and stores them as a C string. Using this string as a buffer to hold infomation that is put into the output file
            while(fgets(mystring, 10000, INPUT)){
                fputs(mystring, OUTPUT);
            }
        }       
    }
    //error handling
    else if(argc > 3) {
        perror("Too many arguments supplied.\n");
        exit(0);
    } 
    else if(argc < 3) {
        perror("Too few arguments supplied.\n");
        exit(0);
    }
    return 0;
}
