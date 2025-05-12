#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure to store process information
struct Process {
    int pid, arrivalTime, burstTime, priority, remainingTime, completionTime, waitingTime, turnaroundTime, startTime;
};

// Function to display results
void displayResults(vector<Process> &processes) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t" << p.turnaroundTime << "\t" << p.waitingTime << endl;
    }
}

// First Come First Serve (FCFS) Scheduling
void fcfs(vector<Process> &processes) {
    int n = processes.size(), currentTime = 0;
    
    sort(processes.begin(), processes.end(), [](Process a, Process b) { return a.arrivalTime < b.arrivalTime; });

    for (auto &p : processes) {
        if (currentTime < p.arrivalTime) currentTime = p.arrivalTime;
        p.startTime = currentTime;
        p.completionTime = currentTime + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        currentTime = p.completionTime;
    }
    
    displayResults(processes);
}

// Shortest Job First (SJF) - Non-Preemptive
void sjf_non_preemptive(vector<Process> &processes) {
    int n = processes.size(), currentTime = 0, completed = 0;

    vector<bool> isCompleted(n, false);

    while (completed < n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurst) {
                minBurst = processes[i].burstTime;
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        processes[idx].startTime = currentTime;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        isCompleted[idx] = true;
        currentTime = processes[idx].completionTime;
        completed++;
    }

    displayResults(processes);
}

// Priority Scheduling - Non-Preemptive
void priority_scheduling(vector<Process> &processes) {
    int n = processes.size(), currentTime = 0, completed = 0;
    vector<bool> isCompleted(n, false);

    while (completed < n) {
        int idx = -1, highestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++;
            continue;
        }
        processes[idx].startTime = currentTime;
        processes[idx].completionTime = currentTime + processes[idx].burstTime;
        processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        isCompleted[idx] = true;
        currentTime = processes[idx].completionTime;
        completed++;
    }

    displayResults(processes);
}

// Round Robin Scheduling
void round_robin(vector<Process> &processes, int timeQuantum) {
    int n = processes.size(), currentTime = 0, completed = 0;
    vector<int> remainingTime(n);
    
    for (int i = 0; i < n; i++) remainingTime[i] = processes[i].burstTime;

    while (completed < n) {
        bool executed = false;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0 && processes[i].arrivalTime <= currentTime) {
                executed = true;
                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }
        if (!executed) currentTime++;
    }

    displayResults(processes);
}

// Function to get process details
vector<Process> getProcesses() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time, Burst Time, and Priority for Process " << i + 1 << ": ";
        processes[i].pid = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }
    return processes;
}

// Main Menu
int main() {
    while (true) {
        cout << "\nCPU Scheduling Algorithms\n";
        cout << "1. FCFS (First Come First Serve)\n";
        cout << "2. SJF (Shortest Job First) - Non-Preemptive\n";
        cout << "3. Priority Scheduling (Non-Preemptive)\n";
        cout << "4. Round Robin Scheduling\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        if (choice == 5) break;

        vector<Process> processes = getProcesses();
        if (choice == 1) fcfs(processes);
        else if (choice == 2) sjf_non_preemptive(processes);
        else if (choice == 3) priority_scheduling(processes);
        else if (choice == 4) {
            int timeQuantum;
            cout << "Enter Time Quantum: ";
            cin >> timeQuantum;
            round_robin(processes, timeQuantum);
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}