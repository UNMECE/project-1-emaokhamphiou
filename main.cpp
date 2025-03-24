#include <iostream>
#include <iomanip>
using namespace std;

struct Capacitor {
    double *time;  
    double *voltage;
    double *current;
    double C;
};

int main() {
    const double dt = 1e-10;
    const double final_time = 5e-6;
    const int num_steps = final_time / dt;
    const double R = 1000;
    const double C = 100e-12;
    const double I_const = 1e-2;
    const double V0 = 10.0;

    Capacitor cap;
    cap.time = new double[num_steps];
    cap.voltage = new double[num_steps];
    cap.current = new double[num_steps];
    cap.C = C;

    cap.time[0] = 0;
    cap.voltage[0] = 0;
    cap.current[0] = V0 / R;

    for (int t = 1; t < num_steps; ++t) {
        cap.time[t] = t * dt;

        cap.voltage[t] = cap.voltage[t - 1] + I_const * dt / C;

        cap.current[t] = cap.current[t - 1] - (cap.current[t - 1] * dt / (R * C));

        if (t % 200 == 0) {
            cout << "Time: " << fixed << setprecision(6) << cap.time[t]
                 << " s, Voltage: " << setprecision(3) << cap.voltage[t]
                 << " V, Current: " << setprecision(6) << cap.current[t]
                 << " A" << endl;
        }
    }

    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}