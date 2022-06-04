#!/bin/bash

_GREEN="\033[1;32m"
_YELLOW="\033[1;33m"
_WHITE="\033[m"

if ![ -f words-stats.txt ]
then
    WordHelperInit 
fi

cat wordle-init.txt
echo -e $_YELLOW"Write exit to stop the game"$_WHITE
echo -e $_GREEN"Write help to launch wordle statistique"$_WHITE
# echo -e $_GREEN"Write clue to have help"$_WHITE

max_index=$((`< words.txt wc -l` + 1))
index=$(( RANDOM % (${max_index}-1) )) 

guess=`sed -n "${index}p" words.txt`

CheckInDict () {
    
    if [ ${#1} -eq 5 ]; # five char + \0
    then
        local isInDict=$(grep -c "${1}" words.txt)
        if [ $isInDict -eq 0 ]; then
            echo "Not in word list "
            return 0
        else
            return 1
        fi
    else
        echo "$1 is not a word of 5 characters."
        return 0
	fi
}

PrintWord () {
    local word_print=""
    local unfound_letters=""

    for i in $(seq 1 ${#1})
    do
        if [ ${1:${i}-1:1} == ${guess:${i}-1:1} ]
        then
            word_print+=$_GREEN"${1:${i}-1:1} "
        else
            word_print+=$_WHITE"${1:${i}-1:1} "
            unfound_letters+="${guess:${i}-1:1}"
        fi
    done
    word_print+=$_WHITE
    for i in $(seq 1 ${#unfound_letters})
    do
        ch=${unfound_letters:${i}-1:1}
        word_print=${word_print/$_WHITE$ch/033[1;33m"${ch}"}
    done

    echo -e "\t\t${word_print}"
    if [ ${1} == ${guess} ]
    then
        return 1
    else
        return 0
    fi
}

WordHelperInit () {
    local string_letter="abcdefghiklmonpqrstuvwxyz"

    for i in $(seq 1 ${#string_letter})
    do
        local ch=${string_letter:${i}-1:1}
        local occ=`grep -c "$ch" words.txt`
        local occ_1=`grep -c "^[^$ch]*$ch[^$ch]*$" words.txt`
        local occ_2=`grep -c "^[^$ch]*$ch[^$ch]*$ch[^$ch]*$" words.txt`
        local occ_3=`grep -c "^[^$ch]*$ch[^$ch]*$ch[^$ch]*$ch[^$ch]*$" words.txt`
        local occ_4=`grep -c "^[^$ch]*$ch[^$ch]*$ch[^$ch]*$ch[^$ch]*$ch[^$ch]*$" words.txt`
        echo "$ch $occ $occ_1 $occ_2 $occ_3 $occ_4" >> words-stats.txt
    done    
}

WordHelper () {
    local words=`sort -n -k 3 words-stats.txt | tail -5 | cut -d " " -f1,1`
    local regex=`echo $words | tr ' ' '|'`
    local possib= `grep "^[$regex]\+$" words.txt | grep -vE '^.*(.).*\1.*$'`
    #simply capture one of the character and check whether it has a copy elsewhere 




}

attemp_dict=""

for j in $(seq 1 6)
do
    while :
    do
        read -p "Your guess is: " try 
        try=${try,,}
        if [ $try == "exit" ]
        then
            exit
        elif [ $try == "help" ] && [ $j -eq 1 ]
        then
            rm words-stats.txt
            WordHelperInit
            continue
        # elif [ $try == "clue" ]
        # then
        #     WordHelper
        fi
        CheckInDict $try
        if [ $? -eq 1 ] # if word in dict print word
        then
            break
        fi
    done
    #attemp_dict+= $try
    PrintWord $try
    if [ $? -eq 1 ]
    then
        echo "Well done ! You found the word ${guess} in $j attemps!" ; exit
    fi
done

echo "Too bad! The word to guess was ${guess}" ; exit


