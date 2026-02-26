bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fread,fopen,fclose,printf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    descr dd 0
    filename db "C:\\Users\\balac\\OneDrive\\Desktop\\ASM_tools\\asm_tools\\lab hm\\fisier.txt",0
    accesmode db "r",0
    string resb 100
    len equ 100
    many resd 1
    format db "%d",0
    ;A text file is given. The text contains letters, spaces and points. Read the content of the file, determine the number of words and display the result on the screen. (A word is a sequence of characters separated by space or point)
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;deschid fisier
        push dword accesmode
        push dword filename
        call [fopen]
        add esp,2*4
        
        mov dword [descr],eax
        
        cmp eax,0
        je final
        
        ;citim din fisier
        push dword [descr]
        push dword len
        push dword 1
        push dword string
        call [fread]
        add esp,4*4
        
        ;in eax cate am citit
        mov dword[many],eax
        
        mov ebx,0
        mov ecx,0
        
        parcurgere:
            cmp ebx,[many]
            jge done
            
            mov al,[string+ebx]
            
            cmp al,32
            je word_found
            cmp al,46
            je word_found
            jmp not_word
           
        word_found:
        inc ecx
        inc ebx
        jmp parcurgere
        
        not_word:
        inc ebx
        jmp parcurgere
        
        done:
        
        pushad
        
        push dword [descr]
        call [fclose]
        add esp,4
        
        popad
        
        push dword ecx
        push dword format
        call [printf]
        add esp,4*2
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
