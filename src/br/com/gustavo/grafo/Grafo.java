package br.com.gustavo.grafo;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Collectors;

public class Grafo<T> {

    private int quantVertice; // tamanho de nodes que o grafo irá ter
    private int index; // serve como ponteiro
    private Node<T> nodes[]; //vertices

    @Deprecated
    public Grafo(int vertice) {
        this.quantVertice = vertice;
        this.nodes = new Node[this.quantVertice];
        this.index = 0;
    }

    public Grafo(File file, Tranformacao<T> tranform) throws FileNotFoundException {
        this.fileExists(file);
        this.index = 0;

        HashSet<String> vertices = (HashSet<String>) this.getFileVertices(file);
        this.quantVertice = vertices.size() * 2;
        this.nodes = new Node[this.quantVertice];

        parse(tranform, vertices);

        ArrayList<Node<T>> list = new ArrayList<>(Arrays.asList(this.nodes));
        list = (ArrayList<Node<T>>) list.stream().filter(Objects::nonNull).collect(Collectors.toList());
        Node<T>[] aux = new Node[list.size()];
        for (int i = 0; i < list.size(); i++) {
            aux[i] = list.get(i);
        }
        this.quantVertice = aux.length;
        this.nodes = aux;
    }

    private void parse(Tranformacao<T> tranform, HashSet<String> vertices) {
        for (String vertice : vertices) { // itera em todas as linhas do arquivo excluindo a primeira
            String[] splited = vertice.split("[ ][-][>][ ]");
            T father = tranform.transform(splited[0]);
            T child = tranform.transform(splited[1]);
            this.addElemento(father);
            this.addElemento(child);
            this.addEdge(father, child);
        }
    }

    private void fileExists(File file) throws FileNotFoundException {
        if (!file.exists()) {
            throw new FileNotFoundException();
        }
    }

    private Collection<String> getFileVertices(File file) throws FileNotFoundException {
        Scanner scanner = new Scanner(file);
        String str = null;
        HashSet<String> vertices = new HashSet<>();

        while (scanner.hasNextLine()) { // se houver linha passa para a próxima
            str = scanner.nextLine(); // pega a linha atual
            if (str.equals("}")) { // exclui a última linha
                break;
            }
            vertices.add(str); // adiciona linha na lista
        }

        return vertices; // retorna uma lista com todas as linhas
    }

    public void addElemento(T elemento) {
        if (index >= this.quantVertice) {
            throw new IndexOutOfBoundsException("elemento: [" + elemento + "] não adicionado - " + this.index);
        }

        if (findElement(elemento) == null) {
            this.nodes[this.index] = new Node<>(elemento);
            this.index++;
        }
    }

    public void addEdge(T father, T child) {
        findElement(father).addChild(findElement(child));
    }

    public Node<T> findElement(T elemento) {
        Node<T> n = null;
        for (Node<T> node : this.nodes) {
            if (node != null && node.getValue().equals(elemento)) {
                n = node;
                break;
            }
        }
        return n;
    }

    public Node<T>[] getNodes() {
        return this.nodes;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (var node : this.getNodes()) {
            LinkedList<Node<T>> children = node.hasChildren() ? node.getChildren() : null;
            while (!children.isEmpty()) {
            }
        }
        return builder.toString();
    }
}


