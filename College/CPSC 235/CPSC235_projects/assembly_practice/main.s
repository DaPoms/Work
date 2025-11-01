.intel_syntax noprefix
.global _start

.data

_start:
    mov edx, 20
    mov eax, 1
    mov ebx, 0
    int 0x80
