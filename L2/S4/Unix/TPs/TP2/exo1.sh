#!/bin/bash

if [ $# -ne 1 ]
then
  echo "Un argument : extension"
  exit 1
fi

echo `ls *.$1 | wc -l`