%remove(Poz,[],R)
%flow model(i,i,o)
remove(1,[_|List],List):-!.
remove(Poz,[First|List],[First|R]):-
    Poz>1,
    Poz1 is Poz-1,
    remove(Poz1,List,R).
