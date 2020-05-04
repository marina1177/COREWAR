ret=$?
ret=1diff.txt

green='\033[0;32m'
norm='\033[0m'
red='\033[0;31m'

for filename in ./tests/op/*.cor; do
	./corewar-eleonardo $filename $filename > 1origin.txt && ./corewar $filename $filename > 1177.txt &&
	diff 1177.txt 1origin.txt > 1diff.txt
	if [[ -s $ret ]]; then
    echo -e $red"DIFFERENCE"$norm $filename
	else
    echo -e $green"NO DIFFERENCE"$norm $filename
	fi
done