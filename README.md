# bfInterpreter  
An interpreter for the brainf\*ck programming language.  
Includes a few example programs written by me.  
If you would like to learn more about brainf\*ck you can find the Wikipedia article [here](https://en.wikipedia.org/wiki/Brainfuck).  
# Usage  
(MacOS and Linux, if you are on Windows: sorry)  
  
    make  
    ./main file [-d] [-o output file] [-i input file]  
Options are as follows:  
* -d = debug mode  
* -o = output file  
* -i = input file
# Output Files  
If you would like the interpreter to write to an output file as well as the command line, specify an output file with -o.  
# Input Files  
If you would like the interpreter to take input from a file rather than the user, specify an output file with -i.  
Note: any whitespace or EOL character in the input file will be treated as input. Input in bf can only be a single character.  
# Debug Mode
If you would like to see the final cell values and some other misc info, then turn on debug mode
