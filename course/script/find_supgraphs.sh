prefix="$1"
f="$2"

if [ $(stat -c %s "${prefix}") -eq 0 ]
then
echoeval "touch subgraphs_${prefix}"
exit
fi

echoeval "cat ${prefix} | divide_by -prefix \"supgraphs_${prefix}_value\" -E > supgraphs_${prefix}_values.txt"
min_value=$(cat supgraphs_${prefix}_values.txt | head -n1 | awk '{print $1}')
max_value=$(cat supgraphs_${prefix}_values.txt | tail -n1 | awk '{print $1}')
echoeval "rm supgraphs_${prefix}_values.txt"

index=$min_value
echoeval "cp supgraphs_${prefix}_value_${index} supgraphs_${prefix}_${index}"

while true
do
    supgraphs="supgraphs_${prefix}_${index}"

    if [ $(stat -c %s "${supgraphs}") -eq 0 -a ${index} -gt ${max_value} ]; then break; fi

    index=$(expr "$index" + 1)

    if [ -e "supgraphs_${prefix}_value_${index}" ]
    then echoeval "cat ${supgraphs} | add_edge | (cat && cat supgraphs_${prefix}_value_${index}) | shortg | ${f} > supgraphs_${prefix}_${index}"
    else echoeval "cat ${supgraphs} | add_edge | shortg | ${f} > supgraphs_${prefix}_${index}"
    fi
done

echoeval "rm supgraphs_${prefix}_value_*"
echoeval "cat supgraphs_${prefix}_* | shortg > supgraphs_${prefix}"
echoeval "rm supgraphs_${prefix}_*"
