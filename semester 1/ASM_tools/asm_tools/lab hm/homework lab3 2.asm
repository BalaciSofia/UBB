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
        a db 80
        b dw 200
        c dd 900
        d dq 1600
    ;a-b-(c-d)+d-signed 2180
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax,[c]
        cdq; edx:eax=c
        mov ebx, [d] ;ecx:ebx=d
        mov ecx, [d+4]
        sub eax,ebx 
        sbb edx,ecx ;edx:eax=c-d
        clc
        mov ebx,eax
        mov ecx,edx;mutat in ecx:ebx=c-d
        mov al,[a];al=a
        cbw ;ax=a
        sub ax,[b]; ax=a-b
        cwde ;eax=a-b
        cdq ;edx:eax=a-b
        ;edx:eax-
        ;ecx:ebx
        clc
        sub eax,ebx
        sbb edx,ecx
        ;edx:eax=a-b-(c-d)
        mov ebx,[d]
        mov ecx,[d+4]
        ;ecx:ebx
        add eax,ebx
        adc edx,ecx
        ;result in edx:eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
