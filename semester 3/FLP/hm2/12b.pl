%add_divisorsinsublist(L,R)
%flow model(i,o)
add_divisorsinsublist([],[]).
add_divisorsinsublist([F|T],[R1|R2]):-
    is_list(F),
    add_divisors(F,R1),
    add_divisorsinsublist(T,R2).

add_divisorsinsublist([F|T],[F|R]):-
    number(F),
    add_divisorsinsublist(T,R).
%add_divisors(L,R)
%flow model (i,o)
add_divisors([],[]).
add_divisors([H|T],R):-
    divisors(H,R1),
    add_divisors(T,R2),
    append([H|R1],R2,R).
%divisors(E,D,R)
%flow model(i,i,o)
divisors(E,D,[]):-D>=E.
divisors(E,D,[D|R]):-
    0 is E mod D,
    D1 is D+1,
    divisors(E,D1,R).
divisors(E,D,R):-
    0 =\= E mod D,
    D1 is D+1,
    divisors(E,D1,R).

divisors(E, R) :-
    divisors(E, 2, R).
