make;
./corewar_linux $1 $1 $1 $1 -v $2 -d $3 > origin.txt;
./corewar $1 $1 $1 $1 -v $2 -d $3 > 1177.txt;
diff 1177.txt origin.txt
ret=$?
green='\033[0;32m'
norm='\033[0m'
if [[ $ret -eq 0 ]]; then
    echo -e $green"NO DIFFERENCE"$norm
fi