import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.Scanner;

public class Main implements Runnable{

    public static void main(String[] args) throws IOException {
        new Thread(null, new Main(), "", 64 * 1024 * 1024).start();
    }
    public void run(){
        Tree treeInt = null;
        try {
            treeInt = new Tree ();
        } catch (IOException e) {
            e.printStackTrace();
        }
        File input = new File("in.txt");

        try {
            Scanner scan = new Scanner(input);
            while (scan.hasNext()) {
                treeInt.insert(scan.nextLong());

            }

            treeInt.calculateFirstStep();
            treeInt.deleteCenterRoot();
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


class Tree {

    FileWriter writer = new FileWriter("out.txt");

    class Node {
        public long getKey() {
            return key;
        }


        long h;
        long sum;
        long msl;
        long maxSum;
        long key;
        Node left, right;

        public Node(long item) {
            key = item;
            left = right = null;

        }
    }


    public Node getRoot() {
        return root;
    }

    private Node root;
    private long mslT;
    private long maxSumT;
    private Node maxRootT;


    Tree() throws IOException {
        root = null;
    }

    // Добавление вершины
    public void insert(long key) {
        root = insert(root, key);
    }

    private Node insert(Node root, long key) {
        if (root == null) {
            root = new Node(key);
            return root;
        }

        if (key<root.key)
            root.left =

                    insert(root.left, key);
        else if (key>root.key)
            root.right =

                    insert(root.right, key);


        return root;
    }


    // Удаление вершины
    public void deleteKey(long key) {
        root = deleteKey(root, key);
    }


    private Node deleteKey(Node root, long key) {
        // Если дерево пустое
        if (root == null) return root;

        //Ищем есть ли вершина, которую нкобходимо удадлить в дереве
        if (key<root.key)
            root.left = deleteKey(root.left, key);
        else if (key>root.key)
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

    private long alwaysLeft(Node root) {
        long minv = root.key;
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
                    node.h = 0;
                    node.msl = 0;
                    node.sum = node.key;
                    node.maxSum = node.sum;
                } else {
                    node.h = 1 + node.left.h;
                    node.msl = node.left.h + 1;
                    node.sum = node.left.sum +  node.key;
                    node.maxSum = node.sum;
                }
            } else if (node.left == null) {
                node.h = 1 + node.right.h;
                node.msl = 1 + node.right.h;
                node.sum = node.right.sum +  node.key;
                node.maxSum = node.sum;
            } else {
                if (node.left.h > node.right.h) {
                    node.sum = node.left.sum + node.key;
                }
                else if (node.right.h > node.left.h)
                    {
                        node.sum = node.right.sum +  node.key;
                    }
                else
                {
                    node.sum = Math.max(node.left.sum, node.right.sum)+ node.key;
                }
                node.h = Math.max(node.right.h, node.left.h)+1;
                node.msl  = node.right.h + node.left.h + 2;
                node.maxSum = node.left.sum+ node.right.sum + node.key;
            }

            if (node.msl > mslT) {
                mslT = node.msl;
                maxSumT = node.maxSum;
                maxRootT = node;
            }
            else if (node.msl == mslT)
            {
                if (node.maxSum >= maxSumT)
                {
                    maxSumT = node.maxSum;
                    maxRootT = node;
                }
            }
        }

    }


    public void deleteCenterRoot() throws IOException {
        if (mslT % 2 != 0)
            deleteKey(maxRootT.key);

        else {

            Node temp = maxRootT;
            long height = mslT / 2;
            while (temp.h != height) {
                if (temp.right == null) {
                    if (temp.left != null) {
                        temp = temp.left;
                    }
                } else if (temp.left == null) {
                    temp = temp.right;

                } else {
                    if (temp.left.h > temp.right.h)
                        temp = temp.left;
                    else
                        temp = temp.right;
                }
                }
            if (temp!=maxRootT)
                deleteKey(temp.key);
            deleteKey(maxRootT.key);

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
        writer.write(node.key+ "\n");

        printPrefix(node.left);

        printPrefix(node.right);
    }
}
