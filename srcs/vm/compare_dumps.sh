make && ./corewar jumper.cor jumper.cor -d $1 > 1177.txt && ./corewar_copy -d $1 jumper.cor jumper.cor > origin.txt;
diff 1177.txt origin.txt > test.txt
ret=$?
green='\033[0;32m'
norm='\033[0m'
if [[ $ret -eq 0 ]]; then
    echo -e $green"NO DIFFERENCE"$norm
fi
