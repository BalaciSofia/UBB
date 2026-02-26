bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    y dw 16
    z dw 13
    SI_val dw 17
    DX_val dw 15
    AX_val dw 18 

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;calculam (ax-z)
        mov ebx,0
        mov bx,[AX_val];bx=AX_val
        sub bx,[z];bx=AX_val-z
        ;bx contine ax-z
        
        ;calculam (11-ax)
        mov ax,11;ax=11
        mov cx,[AX_val];cx=AX_val
        sub ax,cx;ax=ax-cx=11-AX_val
        
        ;calculam (11-ax)^2
        imul ax;dx:ax=ax*ax=(11-AX_val)*(11-AX_val)
        ;mutam rezultatul de pe dx:ax pe eax
        push dx
        push ax
        pop eax
        ;acum eax contine (11-AX_val)*(11-AX_val)
        
        ;calculam (11-ax)^2+19
        add eax,19;eax=(11-ax)^2+19
        ;calculam (ax-z)*((11-ax)^2+19)
        mul ebx;edx:eax=eax*ebx=(ax-z)*((11-ax)^2+19)
        
        ;acuma edx:eax=eax*ebx=(ax-z)*((11-ax)^2+19)
        
        ;mut edx:eax in ebx:ecx ca imi trebe eax sa fac inmultirea dx*y
        mov ebx,eax
        mov ecx,edx
        ;deci acuma ecx:ebx=(ax-z)*((11-ax)^2+19)
        
        ;calculam dx*y
        mov eax,0
        mov ax,[DX_val];ax=DX_val
        mov dx,[y];bx=y
        
        mul dx;dx:ax=ax*dx=DX_val*y
        ;calculez SI_val+DX_val
        push ebx;salvez ebx pe stiva 
        mov ebx,0
        mov bx,[SI_val]
        add bx,[DX_val]
                
        ;impart dx:ax la cx
        ;adica (DX_val*y)/(SI_val+DX_val)
        div bx;
        ;acum ax=(DX_val*y)/(SI_val+DX_val)
        
        pop ebx;
        ;deci acum avem ecx:ebx=(ax-z)*((11-ax)^2+19)
        ;ax=(DX_val*y)/(SI_val+DX_val)
        
        ;adunam ax cu ecx:ebx
        add eax,ebx
        adc ecx,0
        
  
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
