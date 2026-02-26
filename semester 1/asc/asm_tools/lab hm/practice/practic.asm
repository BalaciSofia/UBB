bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 0
    b db 0
    message1 db "a=",0
    message2 db "b=",0
    format1 db "%d",0
    format2 db "%d",0
    prod resd 1
    format3 db "result=%d",0
; our code starts here
;se citesc doua numere de la tastatura si se afiseaza prdusul lor
segment code use32 class=code
    start:
        ; ...
        push dword message1
        call [printf]
        add esp,4
        
        ;citire a
        push dword a
        push dword format1
        call [scanf]
        add esp,2*4
        
        push dword message2
        call [printf]
        add esp,4
        
        ;citire b
        push dword b
        push dword format2
        call [scanf]
        add esp,2*4
        
        ;calculare prod
        mov al,[a]
        imul byte [b]
        ;result in ax
        cwde
        mov dword [prod],eax
            
     
        ;afisare
        
        push dword [prod]
        push dword format3
        call [printf]
        add esp,2*4
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
