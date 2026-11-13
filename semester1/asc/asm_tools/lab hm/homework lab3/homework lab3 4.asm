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
    b db 2;al
    a dw 3;ax
    e dd -5;eax
    x dq -7;edx:ebx
    ;x-b+8+(2*a-b)/(b*b)+e; 
    ;;a-word; b-byte; e-doubleword; x-qword signed
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al,2;al=2
        cbw;ax=2
        mov bx,[a];bx=a
        imul bx;dx:ax=2*a
        ;result on dx ax
        push dx
        push ax
        pop ebx;ebx=2*a
        mov al,[b];al=b
        cbw ;ax=b
        cwde ;eax=b
        ;2*a-b => ebx-eax
        sub ebx,eax
        ;ebx=2*a-b
        mov al,[b];al=b
        imul byte [b];ax=b*b
        mov cx,ax
        ;cx=b*b
        push ebx
        pop ax
        pop dx
        idiv cx
        ;ax:dx(2*a-b)/cx(b*b)=ax(2*a-b)/b*b
        cwde
        ;eax=(2*a-b)/b*b
        mov ecx,eax;ecx=(2*a-b)/b*b
        mov eax,[e]
        add ecx,eax;(2*a-b)/b*b+e
        mov al,8
        cbw
        cwde;eax=8
        add ecx,eax;ecx=(2*a-b)/b*b+e+8
        mov al,[b]
        cbw
        cwde;eax=b
        sub ecx,eax
        mov eax,ecx 
        cdq;edx:eax=(2*a-b)/b*b+e+8-b
        mov ebx,[x];ecx:ebx=x
        mov ecx,[x+4]
        clc
        add eax,ebx
        adc edx,ecx
        ;result edx:eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
