%f([],-1).
%f([H|T],S):-
%    f(T,S1),
%    faux(H,S1,S).
%faux(H,S1,R):-
%    H>0,
%    S1<H,!,
%    R is H.
%faux(_,S1,R):-
%     R is S1.
%f([],0).
%f([H|T],S):-
%    f(T,S1),S1 is S-H.
%this does not work because S has no value
%
% generate all sets of prime numbers that att up to n, including n if it
% fits


isprime(N,D):-
    D*D > N,!.
isprime(N,D):-
    0 =:= (N mod D),!,fail.
isprime(N,D):-
    D1 is D+1,
    isprime(N,D1).

listprime(1,[]):-!.
listprime(N,[N|R]):-
    isprime(N,2),!,
    N1 is N-1,
    listprime(N1,R).
listprime(N,R):-
    N1 is N-1,
    listprime(N1,R).

candidate([H|T],H,T).

adduptoN([],N,S):-
    N=:=S.
adduptoN([H|T],N,S):-
    S1 is H+S,
    adduptoN(T,N,S1).

generateaux(N,_,X,X):-
    adduptoN(X,N,0),!.
generateaux(N,L,X,R):-
    candidate(L,C,T),
    addback(X,C,X1),
    generateaux(N,T,X1,R).
generateaux(N,L,X,R):-
    candidate(L,_,T),
    generateaux(N,T,X,R).

solve(N,Rez):-
    listprime(N,L),
    findall(R,generateaux(N,L,[],R),Rez).

addback([],E,[E]).
addback([H|T],E,[H|R]):-
    addback(T,E,R).

