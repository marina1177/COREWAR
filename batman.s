.name		"Batman"
.comment	"This city needs me"

loop:
        sti r1, %:live, %1
live:laf:
        live %0
        ld %0, r2
        zjmp %:loop
