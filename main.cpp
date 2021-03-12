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
-h help
-v version
-d debug
-o output
-c config
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    bool printVersion;
    bool printHelp;
    bool debug;
    bool output;
    bool config;
    char* args[3]; //0 - file to compile, 1 - output file, 2 - config file
    if(argc < 2){
        printf("Not enough arguments! Usage: %s file [-h, -v, -d, -o output, -c config]", argv[0]);
        return 0;
    }

    for(int i = 1; i<argc; i++){
        
    }

    return 0;
}