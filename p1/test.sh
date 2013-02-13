#!/usr/bin/env sh
FINAL=10000
VALUE=1
CMD="./main IntegerArray.txt"
while [[ $VALUE -le $FINAL ]]
do
  VALUE=`expr 10 \\* $VALUE`
  echo "Timing input of $VALUE"
  time $CMD $VALUE
done
