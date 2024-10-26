.text
.global speculative_function
.type speculative_function, %function

speculative_function:
    // Prologue
    stp x29, x30, [sp, #-16]!       // Save frame pointer and link register
    mov x29, sp                     // Set frame pointer
    stp x19, x20, [sp, #-16]!       // Save x19 and x20
    mov x19, x0                     // x19 = data pointer
    mov x20, x1                     // x20 = size (64-bit register)
    mov x21, #0                     // x21 = index i = 0

loop_speculative:
    cmp x21, x20                    // compare i with size
    b.ge end_speculative            // if i >= size, exit loop

    ldr w0, [x19, x21, LSL #2]      // w0 = data[i]
    cmp w0, #50
    b.ge skip_update                // if data[i] >= 50, skip update
    mov w0, #0                      // w0 = 0
    str w0, [x19, x21, LSL #2]      // data[i] = w0
skip_update:
    add x21, x21, #1                // i++
    b loop_speculative

end_speculative:
    // Epilogue
    ldp x19, x20, [sp], #16         // Restore x19 and x20
    ldp x29, x30, [sp], #16         // Restore frame pointer and link register
    ret
