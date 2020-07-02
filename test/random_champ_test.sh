source ./get_os.h

ret=$?
ret=1diff.txt
green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'
make;

os=$(get_os)
corewar1="../corewar"
corewar2="./other_exec/corewar_${os}"

for i in $(seq 1 $1); do
	champ1=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ2=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ3=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ4=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	args="'$champ1' '$champ2' '$champ3' '$champ4'";	
	eval $corewar1 $args > 1origin.txt;
	eval $corewar2 $args > 11177.txt;
	diff 11177.txt 1origin.txt > 1diff.txt;
	if [[ -s $ret ]]; then
    echo -ne $red"\nDIFFERENCE"$norm $filename
	echo $champ1 $champ2 $champ3 $champ4
	else
    echo -ne $green'.'$norm #$green"NO DIFFERENCE"$norm $filename
	fi	
done
echo 'DONE'