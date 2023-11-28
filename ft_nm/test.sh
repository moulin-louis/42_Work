#!/bin/bash

##define function to check if the test is ok or not

function run_diff_null {
  diff diff1 diff2 > /dev/null
  return $?
}

function run_diff() {
    diff --color=always -y diff1 diff2
}

function check_test {
    run_diff_null
    ret=$?
    if [ $ret -eq 0 ]; then
        echo -n "TEST $1: "
        echo -e "\033[32mOK\033[0m"
    else
        echo -n "TEST $1: "
        echo -e "\033[31mKO\033[0m"
        run_diff
        exit 1
    fi
}

# run function test with variable len args
function run_test {
  all_args=("$@")
  len_args=$#
  args=${all_args[@]:0:$len_args-1}
  ./cmake-build-debug/ft_nm $args > diff1
  nm $args > diff2
  nbr_test=${all_args[$len_args-1]}
  check_test $nbr_test
}

run_test ./sample/test.o 1
run_test ./sample/test 2
run_test ./sample/test -r ./sample/test 3
run_test ./sample/test -p ./sample/test 4
run_test ./sample/test -a ./sample/test 5
run_test ./sample/test -g ./sample/test 6
run_test ./sample/test -u ./sample/test 7
run_test ./sample/test.o ./sample/test 8
run_test ./sample/test.o ./sample/test -r 9
run_test $(which fish) 10
rm diff1 diff2
