package br.com.gustavo.grafo;

@FunctionalInterface
public interface Tranformacao<T> {
    T transform(String attributes);
}
