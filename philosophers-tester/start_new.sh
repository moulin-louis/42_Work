#!/bin/zsh
#Made in loumouli

#Define color constant
GREEN="\e[92m"
RED="\r\e[91m"
RESET="\e[0m"

#Check nbr of args and exit if not equal to 2 args
if [ "$#" -ne 1 ]; then
	echo "gib sh start.sh </path/to/project_folder>"
    exit
fi

echo "$GREEN- Working on folder : $1 $RESET"

#fn to launch philo and return its exit code
launch_philo ()
{
    if [ $# -eq 5 ];then
        ("$1" "$3 $4 $5 $6" > /dev/null)&
        return $?
    fi  

    if [ $# -eq 6 ];then
        ("$1" "$3 $4 $5 $6 $7" > /dev/null)&
        return $?
    fi

    echo "Wrong nbr of arg for launch philo"
    return 1
}

#Will check if philo process still run
parsing_check_process ()
{
    #sleep for 0.1 sec to be sure the process has quitten if work correctly
    sleep 0.05
    #look for philo process currently running, pgrep return 0 if he found a process or 1 if he doesnt
    pgrep philo > /dev/null
    if [ "$?" -eq 0 ];then
        echo "\r\e[91m- Test Parsing Failed\e[0m"
        return 1
    fi
    return 0
}

#Lots of test for the parsing of philosophers
test_parsing ()
{
    #run philo program in the background
    ("$1" > /dev/null)&
    #check if the process still exist
    parsing_check_process
    #if the process still exist, parsing is bad
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo should not work\e[0m"
        exit 1
    fi
    #do it again with different arguments
    ("$1" 1 > /dev/null)&
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 1 should not work\e[0m"
        exit 1
    fi  
    ("$1" 1 2 > /dev/null)&
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 1 2 should not work\e[0m"
        exit 1
    fi
    ("$1" 1 2 3 > /dev/null)&
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 1 2 3 should not work\e[0m"
        exit 1
    fi
    launch_philo $1 $2 4 500 abc 200
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 4 500 abc 200 should not work\e[0m"
        exit 1
    fi
    launch_philo $1 $2 4 500 200 2.9
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 4 500 200 2.9 should not work\e[0m"
        exit 1
    fi
    launch_philo $1 $2 4 -500 200 200
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 4 -500 200 200 should not work\e[0m"
        exit 1
    fi
    launch_philo $1 $2 4 2147483648 200 200
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 4 2147483648 200 200 should not work\e[0m"
        exit 1
    fi
    launch_philo $1 $2 0 800 200 200
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 0 800 200 200  should not work\e[0m"
    	exit 1
    fi
    launch_philo $1 500 100 200 200
    parsing_check_process
    if [ "$?" -eq 1 ];then
        echo "\r\e[91m- ./philo 500 100 200 200  should not work\e[0m"
        exit 1
    fi
    echo "\e[92m- Test Parsing Succeeded !\e[0m"       
}

test_that_dont_die()
{
	philo_exe=$1
	nbr_philo=$2
	ttd=$3
	tte=$4
	tts=$5
	nbr_run=0
	sec=1
	time_to_run=20

	echo -n "$GREEN- Launching 3 run of $time_to_run sec for PATH/philo $nbr_philo $ttd $tte $tts : $RESET"
	("$philo_exe" $nbr_philo $ttd $tte $tts > /dev/null)&
	# while [ $nbr_run -ne 3 ];do
	# 	sec=0
		
	# 	nbr_run=$(( $nbr_run + 1 ))
	# done
	while [ $sec -lt $time_to_run ];do
		pgrep philo > /dev/null
		if [ "$?" -eq 1 ];then
			return 1
		fi
		sleep 1
		sec=$(( $sec + 1 ))
	done
	pkill philo
	("$philo_exe" $nbr_philo $ttd $tte $tts > /dev/null)&
	sec=0
	while [ $sec -lt $time_to_run ];do
		pgrep philo > /dev/null
		if [ "$?" -eq 1 ];then
			return 1
		fi
		sleep 1
		sec=$(( $sec + 1 ))
	done
	pkill philo
	("$philo_exe" $nbr_philo $ttd $tte $tts > /dev/null)&
	sec=0
	while [ $sec -lt $time_to_run ];do
		pgrep philo > /dev/null
		if [ "$?" -eq 1 ];then
			return 1
		fi
		sleep 1
		sec=$(( $sec + 1 ))
	done
	pkill philo

	echo "$GREEN ✅ $RESET"
}

launch_test_that_dont_die()
{
	error=0
	test_that_dont_die $1 4 2147483647 200 200
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 4 2147483647 200 200 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 2 800 200 200
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 2 800 200 200 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 5 800 200 200
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 5 800 200 200 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 5 800 0 200
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 5 800 0 200 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 5 800 200 0
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 5 800 200 0 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 5 800 0 0
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 5 800 0 0 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 4 410 200 200
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 4 410 200 200 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	test_that_dont_die $1 4 2147483647 0 0
	if [ $? -eq 1 ];then
		echo "❌"
		echo "$RED- ./philo 4 2147483647 0 0 shouldnt die $RESET"
		error=$(( $error + 1 ))
	fi
	
	if [ $error -eq 1 ];then
		echo "$RED- Test where philo shouldnt died has failed $RESET"
		return 1
	fi
	echo "$GREEN- Test where philo shouldnt died succeeded !$RESET"
}

echo "$GREEN- Start testing philosphers program... $RESET"
echo "$GREEN- This is a long test (3 run of 20 sec for 8 different test) so be patient pls"
philo_exe="$1/philo/philo"
philo_dir="$1/philo"

#make philo project based on user input path
make -C "$philo_dir" > /dev/null

if [ "$?" -ne 0 ];then
	echo "$RED problem while compiling, check folder input $RESET"
	exit 1
fi

#launch a bunch of test for parsing
test_parsing $philo_exe

#launch a bunch of test for situation where 0 philo should die
launch_test_that_dont_die $philo_exe