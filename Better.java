import java.util.Random;

public class FactorySimulationTimeBased {

    static Random rng = new Random();

    static double uniformRandom(double min, double max) {
        return min + rng.nextDouble() * (max - min);
    }

    static double normalRandom(double mean, double stddev) {
        double u1 = rng.nextDouble();
        double u2 = rng.nextDouble();

        double z = Math.sqrt(-2.0 * Math.log(u1))
                 * Math.cos(2.0 * Math.PI * u2);

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
            if (arr[i] < arr[idx]) {
                idx = i;
            }
        }

        return idx;
    }

    static void simulateTimeBased(int numMachines, double T) {

        double[] workerAvail = new double[10];
        double[] machineAvail = new double[numMachines];

        double totalWait = 0.0;

        int itemsStarted = 0;
        int itemsCompleted = 0;

        while (true) {

            int w = argmin(workerAvail);

            double workerStart = workerAvail[w];

            // Stop if next worker becomes available after T
            if (workerStart >= T) {
                break;
            }

            double assemblyTime = uniformRandom(100, 300);

            double polishTime = generatePolishTime();

            double assemblyDone = workerStart + assemblyTime;

            int k = argmin(machineAvail);

            double machineStart = Math.max(
                assemblyDone,
                machineAvail[k]
            );

            double waitTime = machineStart - assemblyDone;

            totalWait += waitTime;

            itemsStarted++;

            // Machine completion time
            double completionTime = machineStart + polishTime;

            machineAvail[k] = completionTime;

            // Worker becomes free after polishing
            workerAvail[w] = completionTime;

            // Count completed items within T
            if (completionTime <= T) {
                itemsCompleted++;
            }
        }

        double avgWait =
            (itemsStarted == 0)
            ? 0.0
            : totalWait / itemsStarted;

        System.out.printf(
            "Machines: %d | Avg Wait: %.4f sec | Items Started: %d | Items Completed: %d%n",
            numMachines,
            avgWait,
            itemsStarted,
            itemsCompleted
        );
    }

    public static void main(String[] args) {

        // 8 hours simulation
        double T = 8 * 60 * 60;

        System.out.printf(
            "Simulation Horizon: %.0f sec (%.2f hours)%n%n",
            T,
            T / 3600.0
        );

        simulateTimeBased(1, T);

        simulateTimeBased(2, T);

        simulateTimeBased(3, T);
    }
}
