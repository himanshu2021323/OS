#!/bin/bash
mkdir -p Result
>Result/output.txt

while read -r line; do
    read -r x y operation <<< "$line"
    case "$operation" in
        "xor")
            result=$((x ^ y))
            ;;
        "product")
            result=$((x * y))
            ;;
        "compare")
            if [ "$x" -gt "$y" ]; then
                result="$x"
            else
                result="$y"
            fi
            ;;
        *)
            echo "Unknown operation: $operation"
            continue
            ;;
    esac
    echo "$result" >> Result/output.txt

done < input.txt

echo "Results have been calculated in 'Result/output'!"
