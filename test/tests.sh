ret=$?
ret=1diff.txt

green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'

make;
for filename in tests/o*/*.cor; do	
	args="'$filename' '$filename' '-v' '0'";	
	eval ./corewar_linux $args > 1origin.txt;
	eval ./corewar $args > 11177.txt;
	diff 11177.txt 1origin.txt > 1diff.txt;
	if [[ -s $ret ]]; then
    echo -e $red"DIFFERENCE"$norm $filename
	else
    echo -ne $green'.'$norm #$green"NO DIFFERENCE"$norm $filename
	fi
done