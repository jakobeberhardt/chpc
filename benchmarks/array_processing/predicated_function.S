// predicated_function.S

    .text
    .global predicated_function
    .type predicated_function, %function

predicated_function:
    // Prologue
    stp x29, x30, [sp, #-16]!       // Save frame pointer and link register
    mov x29, sp                     // Set frame pointer
    stp x19, x20, [sp, #-16]!       // Save x19 and x20
    mov x19, x0                     // x19 = data pointer
    mov w20, w1                     // w20 = size (using 32-bit register)
    mov w21, #0                     // w21 = index i = 0

loop_predicated:
    cmp w21, w20                    // compare i with size
    b.ge end_predicated             // if i >= size, exit loop

    ldr w0, [x19, w21, UXTW #2]     // w0 = data[i]; extend w21 to x21
    cmp w0, #50
    csel w0, wzr, w0, lt            // if w0 < 50, w0 = 0; else w0 = w0
    str w0, [x19, w21, UXTW #2]     // data[i] = w0

    add w21, w21, #1                // i++
    b loop_predicated

end_predicated:
    // Epilogue
    ldp x19, x20, [sp], #16         // Restore x19 and x20
    ldp x29, x30, [sp], #16         // Restore frame pointer and link register
    ret
