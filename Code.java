import java.io.*;
import java.util.Scanner;

public class MergeSortedFilesBR {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter file name for File 1: ");
        String f1 = sc.nextLine();

        System.out.print("Enter file name for File 2: ");
        String f2 = sc.nextLine();

        System.out.print("Enter output file name: ");
        String out = sc.nextLine();

        try {
            // Write data to File 1
            BufferedWriter bw1 = new BufferedWriter(new FileWriter(f1));
            System.out.print("Enter number of elements in File 1: ");
            int n1 = sc.nextInt();

            System.out.println("Enter " + n1 + " sorted numbers for File 1:");
            for (int i = 0; i < n1; i++) {
                long num = sc.nextLong();
                bw1.write(Long.toString(num));
                bw1.newLine();
            }
            bw1.close();

            // Write data to File 2
            BufferedWriter bw2 = new BufferedWriter(new FileWriter(f2));
            System.out.print("Enter number of elements in File 2: ");
            int n2 = sc.nextInt();

            System.out.println("Enter " + n2 + " sorted numbers for File 2:");
            for (int i = 0; i < n2; i++) {
                long num = sc.nextLong();
                bw2.write(Long.toString(num));
                bw2.newLine();
            }
            bw2.close();

            // Merge the two files
            merge(f1, f2, out);

            System.out.println("Merged successfully into: " + out);

        } catch (FileNotFoundException e) {
            System.out.println("Error: File not found -> " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid numeric input.");
        } catch (IOException e) {
            System.out.println("I/O Error: " + e.getMessage());
        }

        sc.close();
    }

    private static void merge(String f1, String f2, String out) throws IOException {
        try (BufferedReader br1 = new BufferedReader(new FileReader(f1));
             BufferedReader br2 = new BufferedReader(new FileReader(f2));
             BufferedWriter bw = new BufferedWriter(new FileWriter(out))) {

            String s1 = br1.readLine();
            String s2 = br2.readLine();

            while (s1 != null && s2 != null) {
                long n1 = Long.parseLong(s1.trim());
                long n2 = Long.parseLong(s2.trim());

                if (n1 <= n2) {
                    bw.write(Long.toString(n1));
                    bw.newLine();
                    s1 = br1.readLine();
                } else {
                    bw.write(Long.toString(n2));
                    bw.newLine();
                    s2 = br2.readLine();
                }
            }

            while (s1 != null) {
                long n1 = Long.parseLong(s1.trim());
                bw.write(Long.toString(n1));
                bw.newLine();
                s1 = br1.readLine();
            }

            while (s2 != null) {
                long n2 = Long.parseLong(s2.trim());
                bw.write(Long.toString(n2));
                bw.newLine();
                s2 = br2.readLine();
            }
        }
    }
}








import java.util.Random;

import java.util.concurrent.Semaphore;

class PingThread extends Thread {

Semaphore pingSem;

Semaphore pongSem;



public PingThread(Semaphore pingSem, Semaphore pongSem) {

    this.pingSem = pingSem;

    this.pongSem = pongSem;

}



public void run() {

    Random rand = new Random();



    try {

        while (true) {

            pingSem.acquire();



            int s = rand.nextInt(10);

            for (int i = 0; i < s; i++) {

                System.out.print(" ");

            }

            System.out.println("PING");

            Thread.sleep(1000);

            pongSem.release();

        }

    } catch (Exception e) {

        System.out.println("PING THREAD interrupted");

    }

}

}

class PongThread extends Thread {

Semaphore pingSem;

Semaphore pongSem;



public PongThread(Semaphore pingSem, Semaphore pongSem) {

    this.pingSem = pingSem;

    this.pongSem = pongSem;

}



public void run() {

    Random rand = new Random();



    try {

        while (true) {

            pongSem.acquire();



            int s = rand.nextInt(10);

            for (int i = 0; i < s; i++) {

                System.out.print(" ");

            }

            System.out.println("PONG");

            Thread.sleep(1000);

            pingSem.release();

        }

    } catch (Exception e) {

        System.out.println("PONG THREAD interrupted");

    }

}

}

public class PingPongMain {

public static void main(String[] args) {

    Semaphore ping = new Semaphore(1);

    Semaphore pong = new Semaphore(0);



    PingThread obj1 = new PingThread(ping, pong);

    PongThread obj2 = new PongThread(ping, pong);



    obj1.start();

    obj2.start();

}

}





import java.util.Scanner;

public class ProduceNConsume {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the size of the buffer: ");
        int size = sc.nextInt();

        if (size <= 0) size = 5;

        Queue q = new Queue(size);

        new NewTh("Producer", q);
        new NewTh("Consumer", q);

        // (Not closing sc because producer thread uses Scanner too)
    }
}

class Queue {

    private int[] q;
    private int fr, rear, count, len;

    Queue(int len) {
        this.len = len;
        q = new int[len];
        fr = 0;
        rear = 0;
        count = 0;
    }

    public void offer(int x) {
        q[rear] = x;
        rear = (rear + 1) % len;
        count++;
    }

    public int pop() {
        int popped = q[fr];
        fr = (fr + 1) % len;
        count--;
        return popped;
    }

    public int getLen() {
        return len;
    }

    public int getCount() {
        return count;
    }
}

class NewTh implements Runnable {

    private Thread t;
    private Queue q;
    private Scanner sc = new Scanner(System.in);

    NewTh(String action, Queue q) {
        t = new Thread(this, action);
        this.q = q;
        t.start();
    }

    public void run() {

        if (t.getName().equals("Producer")) {
            while (true) {
                produce();
            }
        } else {
            while (true) {
                consume();
            }
        }
    }

    void produce() {
        try {
            System.out.print("Enter Data: ");
            int x = sc.nextInt();

            synchronized (q) {

                while (q.getCount() == q.getLen()) {
                    System.out.println("Buffer Full! Producer Halts");
                    q.wait();
                }

                q.offer(x);
                System.out.println("Produced Data: " + x + " | Buffer Size: " + q.getCount());

                q.notifyAll();
            }

        } catch (InterruptedException e) {
            System.out.println(e);
            Thread.currentThread().interrupt();
        }
    }

    void consume() {
        try {
            int consumed;

            synchronized (q) {

                while (q.getCount() == 0) {
                    System.out.println("Buffer Empty! Consumer Halts");
                    q.wait();
                }

                consumed = q.pop();
                System.out.println("Consumed Data: " + consumed + " | Buffer Size: " + q.getCount());

                q.notifyAll();
            }

            Thread.sleep(3000);

        } catch (InterruptedException e) {
            System.out.println(e);
            Thread.currentThread().interrupt();
        }
    }
}















import java.util.Scanner;

class MaxThread extends Thread {

    private int[] array;
    private int max;

    public MaxThread() {
        array = new int[]{1, 2, 3};
        max = 0;
    }

    public MaxThread(int[] array) {
        this.array = array;
    }

    public int getMax() {
        return max;
    }

    public void run() {

        max = array[0];

        for (int i = 1; i < array.length; i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }

        System.out.println("Maximum Element = " + max);
    }
}

class AvgThread extends Thread {

    private int[] array;
    private double average;

    public AvgThread() {
        array = new int[]{1, 2, 3};
        average = 0.0;
    }

    public AvgThread(int[] array) {
        this.array = array;
    }

    public double getAverage() {
        return average;
    }

    public void run() {

        int sum = 0;

        for (int value : array) {
            sum += value;
        }

        average = (double) sum / array.length;

        System.out.println("Average = " + average);
    }
}

public class Main {

    public static void main(String[] args) throws InterruptedException {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter Number of elements for the array : ");
        int n = sc.nextInt();

        if (n <= 0) {
            System.out.println("Array size must be >= 1");
            sc.close();
            return;
        }

        int[] arr = new int[n];

        System.out.println("Enter elements of array :");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        MaxThread maxObj = new MaxThread(arr);
        AvgThread avgObj = new AvgThread(arr);

        maxObj.start();
        avgObj.start();

        maxObj.join();
        avgObj.join();

        double avg = avgObj.getAverage();

        if (avg == 0.0) {
            System.out.println("(Max / Average) is undefined (average is 0).");
        } else {
            double result = maxObj.getMax() / avg;
            System.out.println("(Max / Average) = " + result);
        }

        sc.close();
    }
}






import java.util.Scanner;

class MessagePrinter {
    private int turn = 1; // shared turn

    public synchronized void printMessage(String msg, int myTurn, int nextTurn) {
        for (int i = 0; i < msg.length(); i++) {
            while (turn != myTurn) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            System.out.print(msg.charAt(i));
            turn = nextTurn;
            notifyAll();
        }
    }
}

class MessageThread extends Thread {
    private final MessagePrinter printer;
    private final String msg;
    private final int myTurn;
    private final int nextTurn;

    MessageThread(MessagePrinter printer, String msg, int myTurn, int nextTurn) {
        this.printer = printer;
        this.msg = msg;
        this.myTurn = myTurn;
        this.nextTurn = nextTurn;
    }

    @Override
    public void run() {
        printer.printMessage(msg, myTurn, nextTurn);
    }
}

public class Message {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter message 1");
        String msg1 = sc.next(); // use nextLine() if you want spaces
        System.out.println("Enter message 2");
        String msg2 = sc.next();
        System.out.println("Enter message 3");
        String msg3 = sc.next();

        MessagePrinter printer = new MessagePrinter(); // ONE shared object

        MessageThread t1 = new MessageThread(printer, msg1, 1, 2);
        MessageThread t2 = new MessageThread(printer, msg2, 2, 3);
        MessageThread t3 = new MessageThread(printer, msg3, 3, 1);

        t1.start();
        t2.start();
        t3.start();
    }
}






import java.util.Scanner;

class NumberPrinter {

    private int cur;
    private int limit;

    public NumberPrinter() {
        this.cur = 1;
        this.limit = 10;
    }

    public NumberPrinter(int limit) {
        this.cur = 1;
        this.limit = limit;
    }

    public synchronized void printOdd() {

        while (cur <= limit) {

            while (cur % 2 == 0) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }

            if (cur <= limit) {
                System.out.print(cur + " ");
                cur++;
                notifyAll();
            }
        }
    }

    public synchronized void printEven() {

        while (cur <= limit) {

            while (cur % 2 != 0) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }

            if (cur <= limit) {
                System.out.print(cur + " ");
                cur++;
                notifyAll();
            }
        }
    }
}

class OddThread extends Thread {

    private NumberPrinter printer;

    public OddThread() {
        this.printer = new NumberPrinter();
    }

    public OddThread(NumberPrinter printer) {
        this.printer = printer;
    }

    public void run() {
        printer.printOdd();
    }
}

class EvenThread extends Thread {

    private NumberPrinter printer;

    public EvenThread() {
        this.printer = new NumberPrinter();
    }

    public EvenThread(NumberPrinter printer) {
        this.printer = printer;
    }

    public void run() {
        printer.printEven();
    }
}

public class Driver {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter N: ");
        int n = sc.nextInt();

        if (n <= 0) {
            System.out.println("N must be >= 1");
            sc.close();
            return;
        }

        NumberPrinter printer = new NumberPrinter(n);

        OddThread t1 = new OddThread(printer);
        EvenThread t2 = new EvenThread(printer);

        t1.start();
        t2.start();

        sc.close();
    }
}
