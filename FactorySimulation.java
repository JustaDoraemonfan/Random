import java.util.Random;

public class FactorySimulation {

    static double generatePolishTime(Random rng) {
        double t;
        do {
            t = 20 + 7 * rng.nextGaussian();
        } while (t < 5);
        return t;
    }

    static int argmin(double[] arr) {
        int idx = 0;
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < arr[idx]) idx = i;
        }
        return idx;
    }

    static double simulate(int numMachines, int N) {
        Random rng = new Random();
        double[] workerAvail = new double[10];
        double[] machineAvail = new double[numMachines];
        double totalWait = 0;
        int itemCount = 0;

        while (itemCount < N) {
            int w = argmin(workerAvail);
            double workerStart = workerAvail[w];

            double assemblyTime = 100 + rng.nextDouble() * 200;
            double polishTime = generatePolishTime(rng);

            double assemblyDone = workerStart + assemblyTime;

            int k = argmin(machineAvail);
            double machineStart = Math.max(assemblyDone, machineAvail[k]);

            double waitTime = machineStart - assemblyDone;

            totalWait += waitTime;
            itemCount++;

            machineAvail[k] = machineStart + polishTime;
            workerAvail[w] = machineAvail[k];
        }

        return totalWait / N;
    }

    public static void main(String[] args) {
        int N = 10000;

        System.out.printf("Machines: 1 | Average wait: %.4f seconds%n", simulate(1, N));
        System.out.printf("Machines: 2 | Average wait: %.4f seconds%n", simulate(2, N));
        System.out.printf("Machines: 3 | Average wait: %.4f seconds%n", simulate(3, N));
    }
}
