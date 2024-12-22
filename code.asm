section .data
    hello db 'Hello, World!',0 ; Null-terminated string

section .text
    global _start

_start:
    ; Write the string to stdout
    mov eax, 4          ; System call number for sys_write
    mov ebx, 1          ; File descriptor 1 is stdout
    mov ecx, hello      ; Pointer to the string
    mov edx, 13         ; Length of the string
    int 0x80            ; Call kernel

    ; Exit the program
    mov eax, 1          ; System call number for sys_exit
    xor ebx, ebx        ; Exit code 0
    int 0x80            ; Call kernel
