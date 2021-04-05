.name "Hero"
.comment "Work Work Work"

ld	%1, r2
ld	%100, r3
ld	%100, r4
xor  r3, r4, r5

sti	r1, %:one, %1
sti	r1, %:two, %1
live %1
fork %-10
live %1
fork %-10
live %1
fork %-10
live %1
fork %-10

one:
	live	%0
	fork	%:two

two:
    live %0
	st	r1, -28
	st	r2, -37
	st	r1, -46
	st	r2, -55

live:
    st r1, 6
	live %1
	fork %500
	zjmp %:live



