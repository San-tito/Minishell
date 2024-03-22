#! /bin/bash

# Variables
makefile="Makefile"
lexer_tester="lexer_tester"
parser_tester="parser_tester"
executor_tester="executor_tester"
expansor_tester="expansor_tester"

# First make the makefile
if [ -f ${makefile} ]
then
    make
else
    echo "ERROR: Makefile not found!"
    exit 1
fi

# ...Here in theory we should have all the executables
# Execute the lexer tests
# ./${lexer_tester} "test1" "outfile"
