#!/bin/bash


for xfont in $(cat figlet.list); do
   printf "\n\n"
   printf "$xfont\n"
   figlet -W -p -w 5000 -f $xfont "gentoo heatherly"
   figlet -W -p -w 5000 -f $xfont "abcdefghijklmnopqrstuvwxyz"
   figlet -W -p -w 5000 -f $xfont "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   figlet -W -p -w 5000 -f $xfont "0123456789"
   figlet -W -p -w 5000 -f $xfont "|{}[]#&_<>$ '%^~ ;/-:\()=+*"
done
