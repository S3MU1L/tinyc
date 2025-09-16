#!/bin/sh

bindir=$1
srcdir=$2
input=$(realpath "$srcdir/$3")
expected=$4
action=$5

test "$expected" || expected=good
test "$action" || action=check

if [ "$expected" = ugly ]
then
    test "$action" = sanity && expected=good || expected=bad
fi

if [ "$action" != sanity ]
then
    tcc=$(realpath "$bindir/cc")
    tvm=$(realpath "$bindir/vm")
    test -x "$tcc" || exit 3
    test -x "$tvm" || exit 3
fi

test -f "$input" || exit 3
test "$expected" = good -o "$expected" = bad -o "$expected" = faulty || exit 3
test "$action" = check -o "$action" = grind -o "$action" = sanity || exit 3

testdir=$(mktemp -d -p.)
trap "rm -rf $(realpath "$testdir")" EXIT
cd "$testdir"

echo testdir: "$testdir"

check_cc() {
    echo "$@"
    $@
    rv=$?
    if [ "$rv" -ge 127 ]
    then
        echo "FAIL: Compiler died with a signal; exit code was $rv"
        exit 1
    elif [ "$rv" = 100 ]
    then
        echo "FAIL: Valgrind is dissatisfied."
        exit 1
    elif [ "$rv" = 0 -a "$expected" = bad ]
    then
        echo "FAIL: Expected failure, but compilation succeeded"
        exit 1
    elif [ "$rv" != 0 -a "$expected" != bad ]
    then
        echo "FAIL: Expected success, but compiler exited with code $rv"
        exit 1
    fi
    echo OK
}

binname=$(basename "$input".out)

if [ "$action" = grind ]
then
grind="valgrind --error-exitcode=100 -q --leak-check=full"
elif [ "$action" = sanity ]
then
echo Sanity check: Compiling with a standard C99 compiler
cat - "$input" << EOF \
    | check_cc /usr/bin/cc -std=c99 -pedantic -Werror=pedantic -Werror=vla -o "$binname" -x c - \
    || exit 2
#include <assert.h>
#include <stdbool.h>
#define NULL ((void *) 0)
EOF

if [ -x "$binname" -a "$expected" != faulty ]
then
    echo "Sanity check: Assertions should indeed hold (executing a.out)"
    ./"$binname" || exit 2
    echo OK

    rm "$binname"
fi

# sanity test only
exit 0
fi

echo
echo Compiling with tiny cc
check_cc $grind "$tcc" "$input" || exit 1

binname=tiny.out
vmpy=$srcdir/00/d1_tinyvm.p.py

if [ -f "$binname" ]
then
    expected_orig="$expected"
    test "$expected" = faulty && expected=bad

    echo Running on tiny vm
    check_cc $grind $tvm "$binname" || exit 1
    echo Running with tiny cc --run
    check_cc $grind $tcc --run "$input" || exit 1

    if [ -f $vmpy -a "$expected_orig" != faulty ]; then
        echo dep $vmpy 1>&3
        python $vmpy || exit 1
    fi
    rm "$binname"
fi

cd ..

exit 0
