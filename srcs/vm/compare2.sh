ret=$?
green='\033[0;32m'
norm='\033[0m'

for filename in ../../champions/*.cor; do
	./corewar_copy $filename $filename > origin.txt && ./corewar $filename $filename > 1177.txt;
	diff 1177.txt origin.txt
	if [[ $ret -eq 0 ]]; then
    	echo -e $green"NO DIFFERENCE"$norm
	fi
done