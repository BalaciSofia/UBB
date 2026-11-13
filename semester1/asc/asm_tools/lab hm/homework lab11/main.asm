bits 32
global start

extern scanf
import scanf msvcrt.dll

extern printf
import printf msvcrt.dll

extern exit
import exit msvcrt.dll

%include "modul.asm"

segment data use32 class=data
    prompt db "Enter numbers (press Enter to stop): ", 0
    format_input db "%d", 0
    format_prime db "%d ", 0
    buffer db 10, 0   

segment code use32 class=code
start:
    push prompt
    call [printf]
    add esp, 4

    read_input:
    ;citire numar
        lea eax, [buffer]
        push eax
        push format_input
        call [scanf]
        add esp, 8
    ;verific daca s au terminat numerele
        test eax, eax
        jz end_program
    
    
        movzx eax, byte [buffer]
        cmp eax, 0x20
        je end_program

        push dword [buffer]
        call is_prime
        add esp, 4
        
    ;daca e zero nu e prim
        test eax, eax
        jz read_input
    ;daca e diferit de zero il afisez
        push dword [buffer]
        push format_prime
        call [printf]
        add esp, 8
        jmp read_input

    end_program:
        push 0
        call [exit]
