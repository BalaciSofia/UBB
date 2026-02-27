
%f(0,0):-!.
%f(I,Y):-
%    J is I-1,
%    f(J,V),
%    faux(V,I,Y).

%faux(V,I,Y):-
%         V>1,!,
%         Y is I-2.
%faux(V,_,Y):-
%     Y is V+1.
%4.0 -1 -2 -3 .... infinity

%red and yellow chairs
%one row contains 5 chairs
%on a row at most 3 y

length5([],N):-
    N=:=5.
length5([_|T],N):-
    N1 is N+1,
    length5(T,N1).

lengthmore5([],N):-
    N>5.
lengthmore5([_|T],N):-
    N1 is N+1,
    lengthmore5(T,N1).

countY([],C):-
    C=<3.
countY([H|T],C):-
    H=='Y',!,
    C1 is C+1,
    countY(T,C1).
countY([_|T],C):-
    countY(T,C).

generate(X,R):-
    lengthmore5(X,0),!,fail.
generate(X,X):-
    length5(X,0),
    countY(X,0),!.
generate(X,R):-
    X1=['Y'|X],
    generate(X1,R).
generate(X,R):-
    X1=['R'|X],
    generate(X1,R).

solution(Rez):-
    findall(R,generate([],R),Rez).
