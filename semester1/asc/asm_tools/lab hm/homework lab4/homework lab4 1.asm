bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        ;5432109876543210
    A dw 0111011101010111b
    B dw 1001101110111110b
    C resd 1
    ;=>0000000000000000 , 3>1011101 , 2>111, 1>101010
;Given the words A and B, compute the doubleword C as follows:
;>the bits 0-5 of C are the same as the bits 3-8 of A
;>the bits 6-8 of C are the same as the bits 2-4 of B
;>the bits 9-15 of C are the same as the bits 6-12 of A
;>the bits 16-31 of C have the value 0
segment code use32 class=code
    start:
        mov ebx,0
        mov ax,[A]
        and ax,0000000111111000b
        ror ax,3
        or bx,ax
        mov ax,[B]
        and ax,0000000000011100b
        rol ax,4
        or bx,ax
        mov ax,[A]
        and ax,0001111111000000b
        rol ax,3
        or bx,ax
        mov [C],ebx
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
