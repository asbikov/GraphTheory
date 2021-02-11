#!/bin/sh

prefix="$1"
f="$2"

echoeval "cp ${prefix} ${prefix}_0"

i=0
while true
	do
	j=$(expr $i + 1)
	echoeval "cat ${prefix}_${i} | ${f} > ${prefix}_${j}"
	if [ $(stat -c %s ${prefix}_${j}) -eq 0 ]; then break; fi
	i=$j
done
