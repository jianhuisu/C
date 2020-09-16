#!/bin/bash

if [ -z $TERMINAL_EMULATOR ]
then
# ghome terminal

export PS1="\[\e[36;40m\][\u@\[\e[32;40m\]\h \W]$>\[\e[0m\]"

else

# jetbrains idea terminal
# echo "welcome to jetbrains terminal"
export PS1="\[\e[36;1m\]\u@\[\e[32;1m\]\h \W]> \[\e[0m\]"
fi
