package domain;

public enum Symbol {
    X,
    O;

    public Symbol other() {
        return this == X ? O : X;
    }
}
