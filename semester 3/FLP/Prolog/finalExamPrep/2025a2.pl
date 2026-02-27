%sublists with odd length
%elemets asscending
mysort([],_).
mysort([H|T],R):-
    mysort(T,R1),
    insert(R1,H,R).

insert([],E,[E]):-!.
insert([H|T],E,[E,H|T]):-
    H>E,!.
insert([H|T],E,[H|R]):-
    H<E,
    insert(T,E,R).


lengthodd([],Len):-
    1 =:= (Len mod 2).
lengthodd([_|T],Len):-
    Len1 is Len+1,
    lengthodd(T,Len1).
assc([],_).
assc([H|T],P):-
    H>P,
    assc(T,H).
candidate([H|T],H,T).
addback([],E,[E]).
addback([H|T],E,[H|R]):-
    addback(T,E,R).
generate([],X,X):-
    X=[H|T],
    assc(T,H),
    lengthodd(X,0).
generate(L,X,R):-
    candidate(L,C,T),
    addback(X,C,X1),
    generate(T,X1,R).
generate(L,X,R):-
    candidate(L,_,T),
    generate(T,X,R).
solve(L,Rez):-
    mysort(L,L1),
    findall(R,generate(L1,[],R),Rez).

