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
-i input
-v verbosity
*/

#include <stdio.h>
#include <stdlib.h> 

void printMem(char *mem, int memSize){
    int memEnd = 0;
    for(int i = memSize; i>=0; i--){
        if(mem[i] != 0){
            memEnd = i;
            break;
        }
    }
    for(int i = 0; i<=memEnd; i++){
        printf("|%i", mem[i]);
    }
    printf("|\n");
}

int getMemSize(char* buffer, int size){
    int memPos = 0;
    int maxMemPos = 0;

    for(int i = 0; i<size; i++){
        if(buffer[i] == '>'){
            memPos++;
        }else if(buffer[i] == '<'){
            memPos--;
        }

        if(memPos > maxMemPos){
            maxMemPos = memPos;
        }
    }

    return maxMemPos;
}

int main(int argc, char* argv[]){
    bool debug = false;
    bool output = false;
    bool input = false;
    char* args[3]; //0 - file to compile, 1 - output file, 2 - input file
    int verbosity = 1;
    if(argc < 2){
        printf("Not enough arguments! Usage: %s file [-d, -v [1, 2], -o output, -i input]", argv[0]);
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
            }else if(argv[i][1] == 'i'){
                input = true;
                i++;
                args[2] = argv[i];
            }else if(argv[i][1] == 'v'){
                i++;
                verbosity = atoi(argv[i]);
            }
        }else{
            //otherwise it must be the file
            args[0] = argv[i];
        }
    }

    if(debug) printf("program file: %s\n", args[0]);
    if(debug) if(output) printf("output file: %s\n", args[1]);
    if(debug) if(input) printf("input file: %s\n", args[2]);

    FILE *program;
    long programSize;
    char *buffer;
    size_t res;

    program = fopen(args[0], "r");
    if(program == NULL){
        printf("Error! unable to open file\n");
        return 0;
    }

    fseek(program, 0, SEEK_END);
    programSize = ftell(program);
    rewind(program);

    buffer = (char*)malloc(sizeof(char)*programSize);
    if(buffer == NULL){
        printf("Error! unable to allocate memory\n");
        return 0;
    }

    res = fread(buffer, 1, programSize, program);
    if(res != programSize){
        printf("Error! couldn't read file\n");
        return 0;
    }

    fclose(program);

    if(debug) printf("program: %s\n", buffer);

    FILE *outfile;
    if(output){
        outfile = fopen(args[1], "w");
        if(outfile == NULL){
            printf("Error! couldn't open output file\n");
            return 0;
        }
    }

    FILE *infile;
    long infileSize;
    char *inputBuffer;
    int inputBufferLoc = 0;
    if(input){
        infile = fopen(args[2], "r");
        if(infile == NULL){
            printf("Error! couldn't open input file\n");
            return 0;
        }
        fseek(infile, 0, SEEK_END);
        infileSize = ftell(infile);
        rewind(infile);

        inputBuffer = (char*)malloc(sizeof(char)*infileSize);
        if(inputBuffer == NULL){
            printf("Error! unable to allocate memory for input buffer\n");
            return 0;
        }

        res = fread(inputBuffer, 1, infileSize, infile);
        if(res != infileSize){
            printf("Error! couldn't read input file\n");
            return 0;
        }

        fclose(infile);
    }

    int memSize = getMemSize(buffer, programSize);
    char *mem = new char [memSize];
    char *curr = &mem[0];
    int loopLoc[16];
    char *loopVal[16];
    int loopPointer = -1;

    bool errorPrinted = false;

    for(int i = 0; i<programSize; i++){
        if(debug && verbosity == 2){
            printf("%c ", buffer[i]);
            printMem(mem, memSize);
        }
        switch(buffer[i]){
            case '>':
                if(curr != &mem[memSize-1]){
                    curr += 1;
                }else{
                    curr = &mem[0];
                }
                break;
            case '<':
                if(curr != &mem[0]){
                    curr -= 1;
                }else{
                    curr = &mem[memSize-1];
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
                if(input){
                    if(inputBufferLoc < infileSize){
                        (*curr) = inputBuffer[inputBufferLoc];
                        inputBufferLoc++;
                    }else{
                        if(!errorPrinted){
                            printf("\nran out of supplied input! continuing with manual input\n");
                            errorPrinted = true;
                        }
                        (*curr) = getchar();
                        getchar(); //for the enter
                    }
                }else{
                    (*curr) = getchar();
                    getchar(); //catches the enter
                }
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
        printf("\n");
        printMem(mem, memSize);
    }

    delete[] mem;

    if(output) fclose(outfile);
    if(input) free(inputBuffer);
    free(buffer);
    return 0;
}