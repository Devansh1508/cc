#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int exit;
    int turnaround;
    int waiting;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    double total_waiting = 0,total_turnaround=0;

    for (int i = 0; i < n; i++) {
        cout << "arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    for (auto& process : processes) {
        process.exit = 0;
        process.waiting = 0;
        process.turnaround = 0;
    }

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            processes[i].exit = processes[i].arrival + processes[i].burst;
        } else {
            processes[i].exit = max(processes[i].arrival, processes[i - 1].exit) + processes[i].burst;
        }
        processes[i].turnaround = processes[i].exit - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }

    double average_waiting = total_waiting / n;

    cout << "Process | Arrival | Burst | Exit | Turnaround | Waiting\n";
    for (const auto& process : processes) {
        cout << process.id << " | " << process.arrival << " | " << process.burst << " | " << process.exit
             << " | " << process.turnaround << " | " << process.waiting << "\n";
    }
    cout << "Average waiting time is: " << average_waiting << "\n";
    cout << "Average turn around time is: " << total_turnaround/n << "\n";

    return 0;
}
