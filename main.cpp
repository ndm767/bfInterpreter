/*
TODO
Load files
Interpret BrainFuck
Allow config files for bf-like languages
Allow cell visualization
*/


/*
Brainfuck instructions taken from https://en.wikipedia.org/wiki/Brainfuck
> 	increment the data pointer (to point to the next cell to the right).
< 	decrement the data pointer (to point to the next cell to the left).
+ 	increment (increase by one) the byte at the data pointer.
- 	decrement (decrease by one) the byte at the data pointer. (if less than 0, wrap around to 256)
. 	output the byte at the data pointer.
, 	accept one byte of input, storing its value in the byte at the data pointer.
[ 	if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
] 	if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
*/

/*
options:
-d debug
-o output
-c config
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    bool debug;
    bool output;
    bool config;
    char* args[3]; //0 - file to compile, 1 - output file, 2 - config file
    if(argc < 2){
        printf("Not enough arguments! Usage: %s file [-d, -o output, -c config]", argv[0]);
        return 0;
    }

    for(int i = 1; i<argc; i++){
        //check if argument is a command
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'd'){
                printf("debug\n");
                debug = true;
            }else if(argv[i][1] == 'o'){
                printf("output\n");
                output = true;
                i++;
                args[1] = argv[i];
            }else if(argv[i][1] == 'c'){
                printf("config\n");
                config = true;
                i++;
                args[2] = argv[i];
            }
        }else{
            //otherwise it must be the file
            args[0] = argv[i];
        }
    }
    printf("file: %s\n", args[0]);
    if(output) printf("output file: %s\n", args[1]);
    if(config) printf("config file: %s\n", args[2]);

    return 0;
}