#!/bin/bash

source ../../config.sh


ROOT="../../../../"

MAKEFILE="makefile.mk"
RULE="all"
APP="${ROOT}build/linux/test/random_strings/app.out"


$MAKE $RULE -f $MAKEFILE


if [ $? -eq 0 ]; then

    $APP


    if [ $? -eq 0 ]; then

        echo $EXECUTION_SUCCESS

    else

        echo $EXECUTION_FAILED $?
    
    fi

else 

    echo $COMPILATION_FAILED $?

fi