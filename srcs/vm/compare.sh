ret=$?
green='\033[0;32m'
norm='\033[0m'

make && ./corewar-eleonardo $2 $2 -d $1 > 1origin.txt && ./corewar $2 $2 -d $1 > 1177.txt;
diff 1177.txt 1origin.txt > 1diff.txt
ret=1diff.txt
green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'
if [[ -s $ret ]]; then
    echo -e $red"DIFFERENCE"$norm $2
else
    echo -e $green"NO DIFFERENCE"$norm $2
fi
