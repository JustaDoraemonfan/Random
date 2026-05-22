#include <bits/stdc++.h>
using namespace std;

#define WORKERS  10
#define SIM_TIME 1000000.0  // simulate for 1,000,000 seconds

double uniform_random(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double normal_random(double mean, double stddev) {
    double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
    double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
    double z  = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + stddev * z;
}

double polishTime() {
    double t;
    do { t = normal_random(20.0, 7.0); } while (t < 5);
    return t;
}

int argmin(vector<double>& arr) {
    return min_element(arr.begin(), arr.end()) - arr.begin();
}

double simulate(int machines) {
    vector<double> workerAvail(WORKERS, 0.0);
    vector<double> machineAvail(machines, 0.0);

    double totalWait = 0.0;
    int    itemCount = 0;
    double clock     = 0.0;   // current simulation time

    while (clock < SIM_TIME) {
        int    w          = argmin(workerAvail);
        clock             = workerAvail[w];        // time advances to next free worker

        if (clock >= SIM_TIME) break;              // stop if beyond sim window

        double assembly   = uniform_random(100.0, 300.0);
        double polish     = polishTime();
        double asmDone    = clock + assembly;

        int    m          = argmin(machineAvail);
        double mStart     = max(asmDone, machineAvail[m]);
        double waitTime   = mStart - asmDone;

        totalWait        += waitTime;
        itemCount++;

        machineAvail[m]   = mStart  + polish;
        workerAvail[w]    = machineAvail[m];
    }

    return totalWait / itemCount;
}

int main() {
    srand(time(NULL));

    cout << fixed << setprecision(4);
    cout << "Machines: 1 | Avg wait: " << simulate(1) << " seconds\n";
    cout << "Machines: 2 | Avg wait: " << simulate(2) << " seconds\n";
    cout << "Machines: 3 | Avg wait: " << simulate(3) << " seconds\n";
}
