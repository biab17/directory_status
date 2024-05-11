#!/bin/bash

count_non_ascii() {
    local file="$1"
    local non_ascii_count=$(grep -P -c '[^\x00-\x7F]' "$file")
    echo "$non_ascii_count"
}

count_keywords() {
    local file="$1"
    local keywords=("corrupted" "dangerous" "risk" "attack" "malware" "malicious")
    local keyword_count=0
    for keyword in "${keywords[@]}"; do
        local count=$(grep -o -i "$keyword" "$file" | wc -l)
        ((keyword_count += count))
    done
    echo "$keyword_count"
}

if [ $# -ne 1 ];
then
    exit 1
fi

file="$1"
line_count=$(wc -l < "$file")
word_count=$(wc -w < "$file")
char_count=$(wc -m < "$file")

if [ "$line_count" -lt 3 ] && [ "$word_count" -gt 1000 ] && [ "$char_count" -gt 2000 ];
then
    exit 0
fi

non_ascii_count=$(count_non_ascii "$file")
keyword_count=$(count_keywords "$file")

if [ "$non_ascii_count" -gt 0 ] || [ "$keyword_count" -gt 0 ];
then
      exit 0
fi

exit 1
