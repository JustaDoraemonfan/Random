import java.util.Random;

public class FactorySimulationTimeBased {

    static Random rng = new Random();

    static double uniformRandom(double min, double max) {
        return min + rng.nextDouble() * (max - min);
    }

    static double normalRandom(double mean, double stddev) {
        double u1 = rng.nextDouble();
        double u2 = rng.nextDouble();
        double z = Math.sqrt(-2.0 * Math.log(u1)) * Math.cos(2.0 * Math.PI * u2);
        return mean + stddev * z;
    }

    static double generatePolishTime() {
        double t;
        do {
            t = normalRandom(20, 7);
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

    // Simulate until time horizon T (seconds). Start jobs only if worker is free before T.
    static double simulateTimeBased(int numMachines, double T) {
        double[] workerAvail = new double[10];
        double[] machineAvail = new double[numMachines];

        double totalWait = 0.0;
        int itemsStarted = 0;

        while (true) {
            int w = argmin(workerAvail);
            double workerStart = workerAvail[w];

            // If the earliest available worker can't start before T, stop launching new items
            if (workerStart >= T) break;

            double assemblyTime = uniformRandom(100, 300);
            double polishTime = generatePolishTime();

            double assemblyDone = workerStart + assemblyTime;

            int k = argmin(machineAvail);
            double machineStart = Math.max(assemblyDone, machineAvail[k]);

            double waitTime = machineStart - assemblyDone;

            totalWait += waitTime;
            itemsStarted++;

            // Update resource availability (worker gets free only after polishing completes)
            machineAvail[k] = machineStart + polishTime;
            workerAvail[w] = machineAvail[k];
        }

        return (itemsStarted == 0) ? 0.0 : (totalWait / itemsStarted);
    }

    public static void main(String[] args) {
        // Example: simulate 8 hours
        double T = 8 * 60 * 60; // seconds

        System.out.printf("Horizon: %.0f sec (%.2f hours)%n", T, T / 3600.0);
        System.out.printf("Machines: 1 | Avg wait: %.4f sec%n", simulateTimeBased(1, T));
        System.out.printf("Machines: 2 | Avg wait: %.4f sec%n", simulateTimeBased(2, T));
        System.out.printf("Machines: 3 | Avg wait: %.4f sec%n", simulateTimeBased(3, T));
    }
}
