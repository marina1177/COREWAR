make;
#./corewar_copy $1 $2 $3 $4 > origin.txt;
#./corewar $1 $2 $3 $4 > 1177.txt;
./corewar_linux $1 $2 $3 $4 -v $5 -d $6 > origin.txt;
./corewar $1 $2 $3 $4 -v $5 -d $6 > 1177.txt;
#./corewar_riz $1 $2 $3 $4 -v $5 -dump $6 > origin.txt;
#./corewar		$1 $2 $3 $4 -v $5 -d $6 > 1177.txt;
diff 1177.txt origin.txt
ret=$?
green='\033[0;32m'
norm='\033[0m'
if [[ $ret -eq 0 ]]; then
    echo -e $green"NO DIFFERENCE"$norm
fi