.text
    .code 32                // 32-bit cmd

    .global vector_start
    .global vector_end      // make symbol to be used outside of this file
                            // like extern
    vector_start:
        LDR R0, =0x10000000
        LDR R1, [R0]
    vector_end:
        .space 1024, 0      // from current poisiton, fill 0 in 1024-bit space
.end
