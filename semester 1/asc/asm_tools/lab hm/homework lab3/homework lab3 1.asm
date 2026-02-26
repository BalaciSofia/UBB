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
    a db 10
    b dw 6  
    c dd 17 
    d dq 800 
;(a+c)-b+a + (d-c)-unsigned
; our code starts here
segment code use32 class=code
    start:
        mov eax, 0 
        mov al,[a] ;al=[a]
        add eax,[c] ;eax=a+c
        mov ebx,0
        mov bx,[b]
        sub eax,ebx  ;eax=(a+c)-b
        mov ecx,0
        mov cl,[a]
        add eax,ecx ;eax=(a+c)-b+a
        mov ebx, dword [d] 
        mov ecx, dword [d+4]    ;ecx:ebx=d
        sub ebx,[c]
        sbb ecx,0
        clc
        mov edx,0           ;edx:eax=(a+c)-b+a +
        add eax,ebx         ;ecx:ebx=(d-c)
        adc edx,ecx         ;result in edx:eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
