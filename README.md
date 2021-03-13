# bfInterpreter  
An interpreter for the brainf\*ck programming language.  
Includes a few example programs written by me.  
If you would like to learn more about brainf\*ck you can find the Wikipedia article [here](https://en.wikipedia.org/wiki/Brainfuck).  
# Usage  
(MacOS and Linux, if you are on Windows: sorry)  
  
    make  
    ./main file [-d] [-v [1, 2]] [-o output file] [-i input file]  
Options are as follows:  
* -d = debug mode
* -v = verbosity level (1 by default)  
* -o = output file  
* -i = input file
# Output Files  
If you would like the interpreter to write to an output file as well as the command line, specify an output file with -o.  
# Input Files  
If you would like the interpreter to take input from a file rather than the user, specify an input file with -i.  
Note: any whitespace or EOL character in the input file will be treated as input.  
Input in bf can only be a single character.  
# Debug Mode
If you would like to see the final cell values and some other misc info, turn on debug mode.  
If you would like to see the memory values of each command as it executes, set the verbosity to 2.  
Verbosity is set to 1 by default.
