bits 32 ; Assembling for the 32-bit architecture

global start        

; Declare external functions needed by our program
extern exit, fopen, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; Our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "result.txt", 0  ; Filename to be created
    access_mode db "w", 0         ; File access mode: "w" (write mode)
    file_descriptor dd -1       
    text db "as rae ik", 0        
    output resb 256               
;A file name and a text (defined in the data segment) are given. The text contains lowercase letters and spaces. Replace all the letters on even positions with their position. Create a file with the given name and write the generated text to file.
; Our code starts here
segment code use32 class=code
start:
    ;Process the text
    lea esi, [text]                 ; esi-address of text
    lea edi, [output]               ; edi-address of output
    mov ecx,0                 ;index
    mov edx,0             

process_text:
    mov al, byte [esi]              ; al=current character             
    cmp al, 0                    ; Check for end of string
    je write_to_file             
    inc ecx
    test ecx, 1                      ; Test if position is even 
    jz replace_with_position         ; Jump if even
    ; If the position is odd, just copy the character
    stosb                            ; store the character into output (edi address)
    inc esi                          ;next character in text
    inc edx                          ; Increment the byte count
    jmp process_text

replace_with_position:
    ; Convert the position (ECX) to ASCII and store it in output
    mov eax,ecx         ;eax=index
    add eax,'0'                     ;convert index to ascii
    stosb      ; Store the position (as a character) in output
    inc esi                          ;next character in text
    inc edx  
    jmp process_text
write_to_file:
    ; opening file

    push dword access_mode         
    push dword file_name            
    call [fopen]                    
    add esp, 4*2                    
    mov [file_descriptor], eax      

    ; Check if fopen() has successfully opened the file (EAX != 0)
    cmp eax, 0
    je final                        ; If file opening failed (EAX == 0), jump to final section
    ; write the processed text to the file 
    push edx                         ; Push the number of bytes to write 
    lea eax, [output]                ; eax=address of output
    push eax                         
    push dword [file_descriptor]     
    call [fprintf]                    ; Write the data to the file
    add esp, 12                      

    ;close file
    push dword [file_descriptor]     
    call [fclose]                    
    add esp, 4                      

final:
  
    push dword 0                     ; Push exit code (0 for success)
    call [exit]                      ; Call exit to terminate the program
