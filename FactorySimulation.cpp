#include <bits/stdc++.h>
using namespace std;

#define WORKERS  10
#define N        10000

// Given: Uniform random
double uniform_random(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Given: Normal random (Box-Muller)
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
    vector<double> worker(WORKERS, 0.0);
    vector<double> machine(machines, 0.0);

    double totalWait = 0;

    for (int item = 0; item < N; item++) {
        int w       = argmin(worker);
        double done = worker[w] + uniform_random(100.0, 300.0);

        int m           = argmin(machine);
        double mStart   = max(done, machine[m]);

        totalWait  += mStart - done;
        machine[m]  = mStart + polishTime();
        worker[w]   = machine[m];
    }

    return totalWait / N;
}

int main() {
    srand(time(NULL));

    cout << fixed << setprecision(4);
    cout << "Machines: 1 | Avg wait: " << simulate(1) << " seconds\n";
    cout << "Machines: 2 | Avg wait: " << simulate(2) << " seconds\n";
    cout << "Machines: 3 | Avg wait: " << simulate(3) << " seconds\n";
}
