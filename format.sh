#!/bin/bash
#
# An example hook script to verify what is about to be committed.
# Called by "git commit" with no arguments.  The hook should
# exit with non-zero status after issuing an appropriate message if
# it wants to stop the commit.
#
# Usage:
# Remove the .sh file extension when you put the script in your hooks folder!
#
# Purposes: 
# Add an empty line at the end of the file.
# Remove trailing spaces at the end of a line.
# 
# Source: http://eng.wealthfront.com/2011/03/corrective-action-with-gits-pre-commit.html
# Version: 2011-03-08
# Related: http://stackoverflow.com/questions/13223868/how-to-stage-line-by-line-in-git-gui-although-no-newline-at-end-of-file-warnin


# Files (not deleted) in the index
find . -type f -iregex ".*\.\(cpp\|json\|log\|txt\|h\)" -print0 | while IFS= read -r -d $'\0' f; do

    echo $f 
    # Only examine known text files
    if [[ "$f" =~ [.](cpp|h)$ ]]
    then
        clang-format-3.6 -i $f
    fi

    # Add a linebreak to the file if it doesn't have one
    if [ "$(tail -c1 $f)" != '\n' ]
    then
        echo >> $f
    fi

    # Remove trailing whitespace if it exists
    if grep -q "[[:blank:]]$" $f
    then
        sed -i "" -e $'s/[ \t]*$//g' $f
    fi


done
