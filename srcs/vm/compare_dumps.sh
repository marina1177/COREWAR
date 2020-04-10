make && ./corewar jumper.cor jumper.cor -d $1 > 1177.txt && 
./corewar -d $1 jumper.cor jumper.cor > origin.txt && diff 1177.txt origin.txt
