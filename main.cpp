/*
TODO
Allow cell visualization
*/


/*
Brainfuck instructions taken from https://en.wikipedia.org/wiki/Brainfuck
> 	increment the data pointer (to point to the next cell to the right).
< 	decrement the data pointer (to point to the next cell to the left).
+ 	increment (increase by one) the byte at the data pointer.
- 	decrement (decrease by one) the byte at the data pointer.
. 	output the byte at the data pointer.
, 	accept one byte of input, storing its value in the byte at the data pointer.
[ 	if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
] 	if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
*/

/*
options:
-d debug
-o output
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    bool debug = false;
    bool output = false;
    bool config = false;
    char* args[2]; //0 - file to compile, 1 - output file
    if(argc < 2){
        printf("Not enough arguments! Usage: %s file [-d, -o output]", argv[0]);
        return 0;
    }

    for(int i = 1; i<argc; i++){
        //check if argument is a command
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'd'){
                debug = true;
            }else if(argv[i][1] == 'o'){
                output = true;
                i++;
                args[1] = argv[i];
            }
        }else{
            //otherwise it must be the file
            args[0] = argv[i];
        }
    }

    if(debug) printf("program file: %s\n", args[0]);
    if(debug) if(output) printf("output file: %s\n", args[1]);

    FILE *infile;
    long infileSize;
    char *buffer;
    size_t res;

    infile = fopen(args[0], "r");
    if(infile == NULL){
        printf("Error! unable to open file\n");
        return 0;
    }

    fseek(infile, 0, SEEK_END);
    infileSize = ftell(infile);
    rewind(infile);

    buffer = (char*)malloc(sizeof(char)*infileSize);
    if(buffer == NULL){
        printf("Error! unable to allocate memory\n");
        return 0;
    }

    res = fread(buffer, 1, infileSize, infile);
    if(res != infileSize){
        printf("Error! couldn't read file\n");
        return 0;
    }

    fclose(infile);

    if(debug) printf("program: %s\n", buffer);

    FILE *outfile;
    if(output){
        outfile = fopen(args[1], "w");
        if(outfile == NULL){
            printf("Error! couldn't open output file\n");
            return 0;
        }
    }

    char mem[3000] = {0};
    char *curr = &mem[0];
    int loopLoc[16];
    char *loopVal[16];
    int loopPointer = -1;

    for(int i = 0; i<infileSize; i++){
        switch(buffer[i]){
            case '>':
                if(curr != &mem[2999]){
                    curr += 1;
                }else{
                    curr = &mem[0];
                }
                break;
            case '<':
                if(curr != &mem[0]){
                    curr -= 1;
                }else{
                    curr = &mem[2999];
                }
                break;
            case '+':
                (*curr)++;
                break;
            case '-':
                (*curr)--;
                break;
            case '.':
                putchar((*curr));
                if(output){
                    fputc((*curr), outfile);
                }
                break;
            case ',':
                (*curr) = getchar();
                break;
            case '[':
                loopPointer++;
                loopLoc[loopPointer] = i;
                loopVal[loopPointer] = curr;
                break;
            case ']':
                if((*loopVal[loopPointer]) > 0){
                    i = loopLoc[loopPointer];
                }else{
                    loopPointer--;
                }
                break;
            default:
                break;
        }
    }

    if(debug){
        int memEnd = 0;
        for(int i = 2999; i>=0; i--){
            if(mem[i] != 0){
                memEnd = i;
                break;
            }
        }
        printf("\n");
        for(int i = 0; i<=memEnd; i++){
            printf("|%i", mem[i]);
        }
        printf("|\n");
    }

    if(output) fclose(outfile);
    free(buffer);
    return 0;
}