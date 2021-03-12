# bfInterpreter  
An interpreter for the BrainFuck programming language  
Includes a few example programs written by me.
# Usage
    make  
    ./main file [-d] [-o output file] [-c config file]  
options are as follows:  
* -d = debug mode  
* -o = output file  
* -c = config file (for BF-like languages)  
# output files  
if you would like the interpreter to write to an output file as well as the command line, specify an output file with -o
# config files  
to use BF-like languages simply make a config file for the language and pass it to the program  
to create a config file simply copy blank.config and next to each symbol, after a single whitespace, type the alternate command