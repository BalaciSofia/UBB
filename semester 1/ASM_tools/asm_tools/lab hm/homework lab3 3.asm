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
    b db 4
    a dw 10
    e dd 5
    x dq 700
;x-b+8+(2*a-b)/(b*b)+e; 710
;a-word; b-byte; e-doubleword; x-qword unsigned
; our code starts here
segment code use32 class=code
    start:
        mov bx,0
        mov bl,2 ;bl=2
        mov ax,[a];ax=a
        mul bx ;dx:ax=2*a
        push dx
        push ax
        pop eax;eax=2*a
        mov ebx,0
        mov bl,[b]
        sub eax,ebx ;eax=2*a-b
        mov ecx,eax ;ecx=eax (retinut) ecx=2*a-b
        mov eax,0
        mov al,[b]
        mul al ;ax=b*b
        ;ecx/ax 
        ;div <reg16>; AX ← DX:AX / <reg16>, DX ← DX:AX % <reg16>
        ;ecx mutat in dx:ax
        ;ax mutat in bx
        mov bx,ax;bx=b*b
        push ecx
        pop ax
        pop dx
        div bx
        ;ax=(2*a-b)/(b*b)
        mov ebx,[x]
        mov edx,[x+4];edx:ebx=x
        mov ecx,0
        mov cl,[b]
        clc
        ;edx:ebx-    x-
        ;    ecx     b
        sub ebx,ecx
        sbb edx,0
        clc
        ;edx:ebx+8  x-b+8
        add ebx,8
        adc edx,0
        clc
        ;edx:ebx+eax  x-b+8+(2*a-b)/(b*b)
        add ebx,eax 
        adc edx,0
        clc
        mov ecx,[e]
        ;edx:ebx+e   x-b+8+(2*a-b)/(b*b)+e
        add ebx,ecx
        adc edx,0
        ; result in edx:ebx
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
