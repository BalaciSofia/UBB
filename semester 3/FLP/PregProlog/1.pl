%Se dau doua liste A si B sa se determine valorile maxime din cele doua
%si sa se creeze o lista noua care sa contina valorile maxime obtinute

%maxim(L,R)
%L-lista
%R-maximul obtinut
%(i,i,o)
maxim([],Acc,R):-R is Acc.
maxim([H|T],Acc,R):-
    H > Acc,
    Acc1 is H,
    maxim(T,Acc1,R).
maxim([H|T],Acc,R):-
    H =< Acc,
    maxim(T,Acc,R).

maximwrapper(L,R):-maxim(L,0,R).
%new_list(A,B,R)
%A first list
%B second list
newlist(A,B,R):-
    maximwrapper(A,M1),
    maximwrapper(B,M2),
    R = [M1,M2].

