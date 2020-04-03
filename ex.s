.name "zork"
.comment "just a basic living prog"

ld		%-16, r5				# r2 = soustraction de start pr aller a r2 : carry a 1
ld		%-12, r4				# r4 = suite (soustraction de start pr aller a r3 : suite du carry)
ld		%-8, r6					# r6 = soustration de start pr aller a r10 : zjmp
ld		%150994944, r10			# r10 = zjmp
