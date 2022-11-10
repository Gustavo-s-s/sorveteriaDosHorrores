## SorveteriaDosHorrores ##

## Problema ##

A partir do enunciado, nota-se que possuímos um problema a ser resolvido que fala
de um primo que abre uma sorveteria. Porém sua sorveteria possuirá algumas regras de negócio 
que constitui:

•	Sua sorveteria possui copos de 2 e 3 sabores.
•	Nunca botar sabor forte em cima de um fraco.
•	Nunca repetir sabores, somente combinações de sabores diferentes.

Dado um Grafo qualque nos temos que determinar 
a quantidade de posibilidades de se fazer um copo de sorvete
com duas e três bolas, onde um **Node Parent** não pode ser colocado
antes de um **Node Child** com forme as especificações do trabaho.


Para inicializar o projeto criamos um Grafo com um arquivo
que deve seguir o seguinte formato "Abobora -> Melao"
onde o primeiro valor antes de '->' será o "parent (pais)" 
e o segundo é o "child (filho)".
Essa relação de pai e filho vai ser importante mais tarde,
pois todos os pais sabem quais serão seus filhos e todos os filhos 
sabem quem serão seus pais, ou seja, de um "pai" podemos
chegar num "filho k" qualquer por **busca em largura** ou em **profundidade**.

 Neste exemplo sera utilizado um grafo arbitrário onde os Nodos mais acimas
 são considerados mais forte que os abaixo. 
