ret=$?
ret=1diff.txt

green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'

make;

for i in $(seq 1 $1); do
	champ1=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ2=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ3=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	champ4=$(ls ./tests/champ/*.cor |sort -R |tail -n 1);
	args="'$champ1' '$champ2' '$champ3' '$champ4' '-v' '0'";	
	eval ./corewar_linux $args > 1origin.txt;
	eval ./corewar $args > 1177.txt;
	diff 1177.txt 1origin.txt > 1diff.txt;
	if [[ -s $ret ]]; then
    echo -ne $red"\nDIFFERENCE"$norm $filename
	echo $champ1 $champ2 $champ3 $champ4
	else
    echo -ne $green'.'$norm #$green"NO DIFFERENCE"$norm $filename
	fi	
done
echo 'DONE'