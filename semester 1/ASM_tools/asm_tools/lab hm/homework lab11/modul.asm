
%ifndef _modul_ASM_ 
%define _modul_ASM_ 

is_prime:
    mov eax, [esp+4]
    cmp eax, 2;compar cu 2
    jl not_prime;if n<2 not prime
    je prime;if n==2 is prime
    test eax, 1 ;if n is even not prime
    jz not_prime
    cmp eax, 3 ;verify for 3 separat
    je prime
    mov ecx, 3 ;ecx=divisor
check_loop:
    mov edx, 0
    div ecx         ;edx:eax/ecx
    test edx, edx   ;if rest==0
    jz not_prime    ;it has a divisor so not prime
    add ecx, 2    ;divisor+=2
    cmp ecx, eax ;divisor<number
    jl check_loop
    prime:
        mov eax, 1
        ret
    not_prime:
        xor eax, eax
        ret
%endif


