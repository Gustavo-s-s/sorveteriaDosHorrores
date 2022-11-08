package br.com.gustavo.grafo;

import java.util.LinkedList;

public class Node<T> {

    private final T value;
    private final LinkedList<Node<T>> children;
    private final LinkedList<Node<T>> fathers;

    public Node(T value) {
        this.value = value;
        this.children = new LinkedList<>();
        this.fathers = new LinkedList<>();
    }

    public void addChild(Node<T> elemento) {
        if (!this.children.contains(elemento)) {
            this.children.add(elemento);
            elemento.addFather(this);
        }
    }

    private void addFather(Node<T> elemento) {
        if (!this.fathers.contains(elemento)) {
            this.fathers.add(elemento);
        }
    }

    public T getValue() {
        return this.value;
    }

    public LinkedList<Node<T>> getChildren() {
        return this.children;
    }

    public LinkedList<Node<T>> getFathers() {
        return this.fathers;
    }

    public boolean hasChildren() {
        return !this.children.isEmpty();
    }

    public boolean hasFather() {
        return !this.fathers.isEmpty();
    }

    @Override
    public String toString() {
        return this.value.toString();
    }
}
