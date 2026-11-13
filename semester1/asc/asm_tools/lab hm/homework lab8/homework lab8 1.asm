bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf
import printf msvcrt.dll
import scanf msvcrt.dll
               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    formata dd "%x",0
    formatb dd "%x",0
    sum resd 1
    dif resd 1
    message db "sum: sum=%x    ",0
    message2 db "difference: dif=%x",0
;Read two doublewords a and b in base 16 from the keyboard. Display the sum of the low parts of the two numbers and the difference between the high parts of the two numbers in base 16 Example:
;a = 00101A35h
;b = 00023219h
;sum = 4C4Eh
;difference = Eh
; our code starts here
segment code use32 class=code
    start:
        mov eax,0
        mov ebx,0
        ; read fisrt number
        push dword a
        push dword formata
        call [scanf]
        add esp,4*2
        
        
        
        ;read second number
        push dword b
        push dword formatb
        call [scanf]
        add esp,4*2
        
        
        mov eax, [a]
        mov ecx,[b]
        
        ;calculate the sum and differance
        and eax,0000FFFFh
        and ecx,0000FFFFh
        add eax,ecx;sum of low pars
        mov [sum],eax
        mov eax,[a]
        mov ecx,[b]
        shr eax,16
        shr ecx,16
        sub eax,ecx;dif of high parts
        mov [dif],eax
        
        push dword[sum]
        push dword message
        call [printf]
        add esp,4*2
        
        push dword[dif]
        push dword message2
        call [printf]
        add esp,4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
