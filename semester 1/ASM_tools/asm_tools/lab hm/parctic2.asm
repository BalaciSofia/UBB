bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fread,printf ,fopen,fclose              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file_descriptor dd 0
    file_name db "cuvinte.txt",0
    access_mode db "r",0
    text db 0
    L db 0
    format db "%d",0
    message db "lenght=",0
    count equ 100
; our code starts here
;Se da un fisier cuvinte.txt care contine cuvinte separate prin spatii.
;Sa se determine si sa se afiseze pe ecran numarul de cuvinte care au lungimea (numarul de caractere din fiecare cuvant) mai mica decat o valoare L ;citita de la tasatura, daca lungimea acestora este impara.

segment code use32 class=code
    start:
        ; ...
        ;open file
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp,4*2
        
        mov dword [file_descriptor],eax
        cmp eax,0
        je final
        
        ;citire din fisier
        push dword [file_descriptor]
        push dword count
        push dword 1
        push dword text
        add esp,4*4
        ;
        
        ;citire L
        push dword message
        call [printf]
        add esp,4
        
        push dword L
        push dword format
        call [scanf]
        add esp,8
        
        
        mov ebx,0
        mov ecx,0
        mov edx,0
        
        search_word:
        mov al,[text+ebx]
        cmp al,32
        je word_found
        cmp al,0
        je done
        inc ebx
        jmp search_word
        
        word_found:
            mov edx, ebx
            sub edx,ecx
            test edx,1
            je lenght_odd
            inc ebx
            mov ecx,ebx
            jmp search_word
            
        lenght_odd:
            mov eax,0
            mov al,byte [L]
            cmp eax,edx
            jge print_word
            inc ebx
            mov ecx,ebx
            jmp search_word
        
        print_word:
        ;nu stiu cum
            
        ;text+ecx->text+ebx
        done:
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
