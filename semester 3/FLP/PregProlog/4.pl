%se da o lista se sterg atomii si numerele impare
%se face cmmdc la lista
%se dubleaza elementele ramase
%
delete([H|T],R):-
    atom(H),
    delete(T,R).
delete([H|T],R):-
    number(H),
    1 is H mod 2,
    delete(T,R).
delete([H|T],[H|R]):-
    number(H),
    delete(T,R).
delete([],[]).

cmmdc(A,B,A):-
    A=:=B.
cmmdc(A,B,R):-
    A>B,
    A1 is A-B,
    cmmdc(A1,B,R).
cmmdc(A,B,R):-
    B >= A,
    B1 is B-A,
    cmmdc(A,B1,R).

cmmdclist([H|T],Prev,R):-
    cmmdc(H,Prev,R1),
    cmmdclist(T,R1,R).
cmmdclist([],Prev,Prev).

double([H|T],[H,H|R]):-
    double(T,R).
double([],[]).

problema(L,R1,R2,R3):-
    delete(L,R1),
    R1=[H|T],
    cmmdclist(T,H,R2),
    double(R1,R3).
