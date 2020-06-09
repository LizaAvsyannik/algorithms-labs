/*
Problem 16
Input file name: input.txt
Output file name: output.txt
Time limit: 1 s
Memory limit: 1024 MB
Необходимо удалить (правым удалением) корень дерева, а затем для каждой вершины определить, сколько наибольших полупутей проходят через неё. Если после удаления в дереве остается одна вершина, то считаем, что имеется один наибольший полупуть длины 0.

Input
Входной файл содержит последовательность чисел — ключи вершин в порядке добавления в дерево. Гарантируется, что в дереве не менее двух вершин.
Output
Выполните прямой левый обход итогового дерева. Для каждой вершины в отдельной строке выведите через пробел её ключ и число полупутей наибольшей длины, проходящих через неё.
Example
input.txt	
1
5
3
7
2
4
6
8
output.txt
5 4
3 4
2 2
4 2
7 4
6 2
8 2
*/
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main implements Runnable{

    public static void main(String[] args) throws IOException {
        new Thread(null, new Main(), "", 64 * 1024 * 1024).start();
    }
    public void run(){
        Tree<Long> treeInt = null;
        try {
            treeInt = new Tree<Long>();
        } catch (IOException e) {
            e.printStackTrace();
        }
        File input = new File("input.txt");

        try {
            Scanner scan = new Scanner(input);
            while (scan.hasNext()) {
                treeInt.insert(scan.nextLong());

            }

                long rootToDelete = treeInt.getRoot().getKey();
                treeInt.deleteKey(rootToDelete);
                treeInt.calculateFirstStep();
                treeInt.calculateSecondStep();
                treeInt.printPrefix();

        } catch (FileNotFoundException ex) {
            System.out.println("FileNotFound!");
        } catch (NoSuchElementException ex) {
            System.out.println("Problems with elems!");
        } catch (IOException ex)
        {
            System.out.println("Problems!");
        }

    }
}


class Tree <T extends Comparable <T>> {

    FileWriter writer = new FileWriter("output.txt");

    class Node {
        public T getKey() {
            return key;
        }

        long h;
        long l;
        long msl;
        long b;
        long a;
        long c;
        T key;
        Node left, right;

        public Node(T item) {
            key = item;
            left = right = null;

        }
    }


    public Node getRoot() {
        return root;
    }

    private Node root;
    private long mslT;


    Tree() throws IOException {
        root = null;
    }

    // Добавление вершины
    public void insert(T key) {
        root = insert(root, key);
    }

    private Node insert(Node root, T key) {
        if (root == null) {
            root = new Node(key);
            return root;
        }

        if (key.compareTo(root.key) < 0)
            root.left =

                    insert(root.left, key);
        else if (key.compareTo(root.key) > 0)
            root.right =

                    insert(root.right, key);


        return root;
    }


    // Удаление вершины
    public void deleteKey(T key) {
        root = deleteKey(root, key);
    }


    private Node deleteKey(Node root, T key) {
        // Если дерево пустое
        if (root == null) return root;

        //Ищем есть ли вершина, которую нкобходимо удадлить в дереве
        if (key.compareTo(root.key) < 0)
            root.left = deleteKey(root.left, key);
        else if (key.compareTo(root.key) > 0)
            root.right = deleteKey(root.right, key);

            // Если нашли
        else {
            // вершина без или с одним сыном
            if (root.left == null)
                return root.right;
            else if (root.right == null)
                return root.left;

            // с двумя сыновьями: один раз направо, всю жизнь налево
            root.key = alwaysLeft(root.right);

            root.right = deleteKey(root.right, root.key);
        }

        return root;
    }

    private T alwaysLeft(Node root) {
        T minv = root.key;
        while (root.left != null) {
            minv = root.left.key;
            root = root.left;
        }
        return minv;
    }


    public void calculateFirstStep() {
        calculateFirstStep(root);
    }

    private void calculateFirstStep(Node node) {
        if (node != null) {

            calculateFirstStep(node.left);
            calculateFirstStep(node.right);
            if (node.right == null) {
                if (node.left == null) {
                    node.l = 1;
                    node.h = 0;
                    node.msl = 0;
                } else {
                    node.h = 1 + node.left.h;
                    node.msl = node.left.h + 1;
                    node.l = node.left.l;
                }
            } else if (node.left == null) {
                node.h = 1 + node.right.h;
                node.msl = 1 + node.right.h;
                node.l = node.right.l;
            } else {
                node.h = 1 + Math.max(node.left.h, node.right.h);
                node.msl = node.left.h + node.right.h + 2;
                if (node.left.h == node.right.h)
                    node.l = node.left.l + node.right.l;
                else
                    node.l = Math.max(node.right.l, node.left.l);
            }

            if (node.msl > mslT) {
                mslT = node.msl;
            }
        }

    }


    private void calculateB(Node node)
    {
        if (node!=null)
        {
            if (node.msl == mslT){
                if (node.right == null)
                {
                    if (node.left == null)
                    {
                        node.b = 1;
                    }
                    else {
                        node.b = node.left.l;
                    }
                }
                else if (node.left == null)
                {
                    node.b = node.right.l;
                }
                else
                {
                    node.b = node.right.l*node.left.l;
                }
            }
            else
                node.b = 0;
        }
    }

    public void calculateSecondStep()
    {
        calculateSecondStep(root);
    }



    private void calculateSecondStep (Node node) {
        if (mslT == 0)
            root.a = 1;
        else {
            if (node != null) {
                calculateB(node);
                if (node.right == null) {
                    if (node.left != null) {
                        node.left.a = node.a + node.b;
                    }
                } else if (node.left == null) {
                    node.right.a = node.a + node.b;
                } else {
                    if (node.left.h > node.right.h) {
                        node.left.a = node.a + node.b;
                        node.right.a = node.b;
                    } else if (node.left.h < node.right.h) {
                        node.right.a = node.a + node.b;
                        node.left.a = node.b;
                    } else {
                        node.left.a = node.b + node.left.l * node.a / node.l;
                        node.right.a = node.b + node.right.l * node.a / node.l;
                    }

                }
                calculateSecondStep(node.left);
                calculateSecondStep(node.right);
            }
        }


    }
    //Обход дерева «Корень-Левый-Правый»
    public  void printPrefix() throws IOException
    {
        printPrefix(root);
        writer.close();
    }

    private void printPrefix(Node node) throws IOException {
        if (node == null)
            return;
        node.c =  node.a + node.b;
        writer.write(node.key.toString()+ " " + node.c+"\n");

        printPrefix(node.left);

        printPrefix(node.right);
    }
}
