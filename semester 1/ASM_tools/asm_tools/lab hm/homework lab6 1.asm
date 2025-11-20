bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 'cojoc are multe capac rosu'
    l equ $-s
    format db "%s",0
;Being given a string of bytes representing a text (succession of words separated by spaces), determine which words are palindromes (meaning may be interpreted the same way in either forward or reverse direction); ex.: "cojoc", "capac" etc.
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx,l
        mov esi,0
        mov edi,0
        mov ebx,0
        next:
            cmp byte [s+esi],' '
                je next_word; if s+esi==' ' next word
            ;else
            cmp byte [s+esi], 0  ; end of string check
                je done
            mov edi,esi ;edi has the adress where the word starts
            
                find_end:;loop until we find the end of the word
                    cmp byte[s+esi],' '
                    je check_palindrome ;if it s the end of  the word we check if is palindrom
                    cmp byte [s+esi], 0     ; end of string check
                    je check_palindrome
                    inc esi;next charachter
                    jmp find_end
            next_word:
                inc esi
                jmp next
            check_palindrome:
                dec esi ;esi is dec bc the poz of it is at the space not the last character of the word
                mov edx,edi ;edx has the strat adress of word
                check:
                    mov al,[s+edx]
                    mov cl,[s+esi]
                    cmp al,cl;compare character first last, second second last and so on
                    jne not_palindrome;if they not equal the word is not palindrom
                    inc edx ;first->second charachter
                    dec esi ;last->second last charachter
                    cmp edx,esi ;compare the indexes
                    jl check ;if edx<esi continue to check 
                    ;else
           
                    
                    inc ebx;which stores the number of palindrom words
            not_palindrome:
                cmp byte[s+esi],0;check if the string ended
                je done;if ended end program
                ;else continue
                inc esi
                jmp next
        done:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
