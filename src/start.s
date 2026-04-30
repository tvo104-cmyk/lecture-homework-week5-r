/*********** ts.s file of C2.6 *********/
    .global start
start:
    LDR sp, =stack_top // set SVC stack pointer
    BL main
    B .
    