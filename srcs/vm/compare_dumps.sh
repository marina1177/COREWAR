./corewar jumper.cor jumper.cor -d $1 > team.txt && 
../../../corewar-eleonard/corewar -d $1 jumper.cor jumper.cor > elen.txt &&
diff team.txt elen.txt
