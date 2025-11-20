bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    A db 2, 1, 3, 3, 4, 2, 6
    l1 equ $-A
    B db 4, 5, 7, 6, 2, 1
    l2 equ $-B
    R times (l1+l2) db 0
    ;Two byte strings A and B are given. Obtain the string R by concatenating the elements of B in reverse order and the even elements of A.
; our code starts here
segment code use32 class=code
    start:
        mov ecx,l2
        mov esi,0
        mov edi,l2-1
        start_loop:
            mov al,[B+edi]
            mov [R+esi],al
            inc esi
            dec edi
        loop start_loop
        mov ecx,l1
        mov edi,esi
        mov esi,0
        start_loop2:
            mov al,[A+esi]
            test al,1
            jnz s_even
            mov [R+edi],al
            inc edi
            s_even:
            inc esi
        loop start_loop2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
