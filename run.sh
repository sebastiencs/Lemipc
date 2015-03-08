#!/bin/sh
## run.sh for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Mar  8 21:53:41 2015 chapui_s
## Last update Sun Mar  8 21:57:26 2015 chapui_s
##

i=0
team=$1

if [ -f $team ] ;
then
    echo "./run.sh team_nb"
else
    while (($i < 10));
    do
	./lemipc `pwd` $team &
	i=$(expr $i + 1)
	usleep 500000
    done
fi
