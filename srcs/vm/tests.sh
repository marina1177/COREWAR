ret=$?
ret=1diff.txt

green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'

make;
for filename in ./tests/*/*.cor; do	
	args1="'$filename' '$filename' '-v' '3'";
	args2="'$filename' '$filename' '-v' '3'";
	eval ./corewar_linux $args1 > 1origin.txt;
	eval ./corewar $args2 > 1177.txt;
	diff 1177.txt 1origin.txt > 1diff.txt;
	if [[ -s $ret ]]; then
    echo -e $red"DIFFERENCE"$norm $filename
	else
    echo -e $green"NO DIFFERENCE"$norm $filename
	fi
done