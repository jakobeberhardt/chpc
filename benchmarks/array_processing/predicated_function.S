.text
.global predicated_function
.type predicated_function, %function

predicated_function:
    // Prologue
    stp x29, x30, [sp, #-16]!       // Save frame pointer and link register
    mov x29, sp                     // Set frame pointer
    stp x19, x20, [sp, #-16]!       // Save x19 and x20
    mov x19, x0                     // x19 = data pointer
    mov x20, x1                     // x20 = size (64-bit register)
    mov x21, #0                     // x21 = index i = 0

loop_predicated:
    cmp x21, x20                    // compare i with size
    b.ge end_predicated             // if i >= size, exit loop

    ldr w0, [x19, x21, LSL #2]      // w0 = data[i]; x21 is index, LSL #2 to multiply by 4
    cmp w0, #50
    csel w0, wzr, w0, lt            // if w0 < 50, w0 = 0; else w0 = w0
    str w0, [x19, x21, LSL #2]      // data[i] = w0

    add x21, x21, #1                // i++
    b loop_predicated

end_predicated:
    // Epilogue
    ldp x19, x20, [sp], #16         // Restore x19 and x20
    ldp x29, x30, [sp], #16         // Restore frame pointer and link register
    ret
