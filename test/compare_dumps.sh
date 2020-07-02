source ./get_os.sh
make -C ../;
#./corewar_copy $1 $2 $3 $4 > origin.txt;
#./corewar $1 $2 $3 $4 > 1177.txt;
os=$(get_os)
corewar1="../corewar"
corewar2="./other_exec/corewar_${os}"

$corewar2   $1 $2 $3 $4 -v $5 -d $6 > origin.txt;
$corewar1   $1 $2 $3 $4 -v $5 -d $6 > 1177.txt;
#./corewar_riz $1 $2 $3 $4 -v $5 -dump $6 > origin.txt;
#./corewar		$1 $2 $3 $4 -v $5 -d $6 > 1177.txt;
diff 1177.txt origin.txt
ret=$?
green='\033[0;32m'
norm='\033[0m'
if [[ $ret -eq 0 ]]; then
    echo -e $green"NO DIFFERENCE"$norm
fi