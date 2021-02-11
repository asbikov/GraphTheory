prefix="$1"
f="$2"

if [ $(stat -c %s "${prefix}") -eq 0 ]
then
echoeval "touch subgraphs_${prefix}"
exit
fi

echoeval "cat ${prefix} | divide_by -prefix \"subgraphs_${prefix}_value\" -E > subgraphs_${prefix}_values.txt"
min_value=$(cat subgraphs_${prefix}_values.txt | head -n1 | awk '{print $1}')
max_value=$(cat subgraphs_${prefix}_values.txt | tail -n1 | awk '{print $1}')
echoeval "rm subgraphs_${prefix}_values.txt"

index=$max_value
echoeval "cp subgraphs_${prefix}_value_${index} subgraphs_${prefix}_${index}"

while true
do
    subgraphs="subgraphs_${prefix}_${index}"

    if [ $(stat -c %s "${subgraphs}") -eq 0 -a ${index} -lt ${min_value} ]; then break; fi

    index=$(expr "$index" - 1)

    if [ -e "subgraphs_${prefix}_value_${index}" ]
    then echoeval "cat ${subgraphs} | remove_edge | (cat && cat subgraphs_${prefix}_value_${index}) | shortg | ${f} > subgraphs_${prefix}_${index}"
    else echoeval "cat ${subgraphs} | remove_edge | shortg | ${f} > subgraphs_${prefix}_${index}"
    fi
done

echoeval "rm subgraphs_${prefix}_value_*"
echoeval "cat subgraphs_${prefix}_* | shortg > subgraphs_${prefix}"
echoeval "rm subgraphs_${prefix}_*"
