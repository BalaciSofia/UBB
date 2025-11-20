%substitute(IList,Val,SubList,R)
%flow model:(i,i,i,O)
substitute([],_,_,[]).
substitute([First|IList],Val,SubList,R):-
    First=Val,!,
    substitute(IList,Val,SubList,R1),
    append(SubList,R1,R).
substitute([First|IList],Val,SubList,[First|R1]):-
    substitute(IList,Val,SubList,R1).
