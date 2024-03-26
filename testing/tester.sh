#! /bin/bash

# Variables
makefile="Makefile"
lexer_tester="lexer_tester"
parser_tester="parser_tester"
executor_tester="executor_tester"
expansor_tester="expansor_tester"
outfile="tester_results"
correct_outfile="results"

# First make the makefile
if [ -f ${makefile} ]
then
    make  &> /dev/null
else
    echo "ERROR: Makefile not found!"
    exit 1
fi

# ...Here in theory we should have all the executables
# Execute the lexer tests
if [ -f ${outfile} ]
then
    rm ${outfile}
fi
touch ${outfile}
./${lexer_tester} ${outfile}

diff ${correct_outfile} ${outfile} &> /dev/null
if [ ! $? -eq 0 ]
then
    echo "Failed lexer tests."
    exit 1
else
    echo "Passed lexer tests."
fi

rm ${outfile}
