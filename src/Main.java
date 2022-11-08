import br.com.gustavo.grafo.Grafo;
import br.com.gustavo.grafo.Node;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {
    private static int cupOfTree = 0;
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("casos_de_teste_04");
        Grafo<String> teste = new Grafo<>(file, String::toString);
        Scanner scan = new Scanner(file);
        Map<Node<String>, Set<Node<String>>> nodeSetMap = GeraValores(teste);
        System.out.println("\n (☞ﾟヮﾟ)☞ Combinações de dois sabores = " + somaCombinacoesDoisSabores(nodeSetMap) + "\n");
        System.out.println("\n (☞ﾟヮﾟ)☞ Combinações de três sabores = " +somaCombinacoesTresSabores(nodeSetMap));
    }

    public static Map<Node<String> , Set<Node<String>>> GeraValores(Grafo<String> grafo){
        Map<Node<String>,Set<Node<String>>> map = new HashMap<>();
        for (Node <String> e : grafo.getNodes()){
            map.put(e,new HashSet<>());
            ArrayDeque<Node<String>> interator =  new ArrayDeque<>();
            interator.add(e);
            while (!interator.isEmpty()){
                Node<String> n = interator.pollFirst(); //tira e ruduz o tamanho da lista
                if(n.hasFather()){
                    map.get(e).addAll(n.getFathers());
                    interator.addAll(n.getFathers());
                }
            }
        }
        return map;
    }

    public static long somaCombinacoesDoisSabores(Map<Node<String>,Set<Node<String>>> map){
        int somaTotal = 0;
        for(var node : map.keySet()){
            somaTotal += map.get(node).size();
            System.out.printf("{%s} -> %s \n", node,map.get(node));
        }
        return somaTotal;
    }

    public static long somaCombinacoesTresSabores(Map<Node<String>,Set<Node<String>>> map){
        int somaTotal = 0;
        for(var node : map.keySet()){
            Set<Node<String>> nodes = map.get(node);
            for(var n : nodes){
                somaTotal += map.get(n).size();
                System.out.printf("{%s, %s} -> %s\n ", node,n,map.get(n));
            }
        }
        return somaTotal;
    }
}
