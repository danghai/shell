#!/bin/sh
for i in 1 5 3 2
do
  echo "Looping ... number $i"
done

max=10
for i in `seq 2 $max`
do
  echo "$i"
done

INPUT_STRING=hello
while [ "$INPUT_STRING" != "bye" ]
do
  echo "Please type something in (bye to quit)"
  read INPUT_STRING
  echo "You typed: $INPUT_STRING"
done
