#include <iostream>
#include <vector>

using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

vector<vector<int>> Max = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

vector<vector<int>> Allocation = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

vector<int> Available = {3, 3, 2};

void calculateNeed(vector<vector<int>>& Need) {
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

bool isSafeState(vector<int>& Work, vector<vector<int>>& Allocation, vector<vector<int>>& Need, vector<int>& SafeSequence) {
    vector<bool> Finish(NUM_PROCESSES, false);
    int count = 0;

    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!Finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        Work[j] += Allocation[i][j];
                    }
                    SafeSequence.push_back(i);
                    Finish[i] = true;
                    found = true;
                    ++count;
                }
            }
        }
        if (!found) {
            break; // Unsafe state
        }
    }

    return count == NUM_PROCESSES;
}

int main() {
    vector<vector<int>> Need(NUM_PROCESSES, vector<int>(NUM_RESOURCES, 0));
    calculateNeed(Need);

    cout << "Content of the Need matrix:" << endl;
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            cout << Need[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << "Is the system currently in a safe state?" << endl;
    vector<int> Work = Available;
    vector<int> SafeSequence;
    if (isSafeState(Work, Allocation, Need, SafeSequence)) {
        cout << "Yes, the system is in a safe state." << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            cout << "P" << SafeSequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "No, the system is not in a safe state." << endl;
    }

    cout << endl;

    cout << "If process P1 requests one additional instance of resource type A and two instances of resource type C:" << endl;
    int additionalA = 1;
    int additionalC = 2;

    if (additionalA <= Need[1][0] && additionalC <= Need[1][2]) {
        if (additionalA <= Available[0] && additionalC <= Available[2]) {
            // Grant the request
            Available[0] -= additionalA;
            Available[2] -= additionalC;
            Allocation[1][0] += additionalA;
            Allocation[1][2] += additionalC;
            Need[1][0] -= additionalA;
            Need[1][2] -= additionalC;

            cout << "Request granted.\nUpdated Allocation matrix:" << endl;
            for (int i = 0; i < NUM_PROCESSES; ++i) {
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    cout << Allocation[i][j] << " ";
                }
                cout << endl;
            }
            cout << "Safe Sequence after granting request: ";
            for (int i = 0; i < SafeSequence.size(); ++i) {
                cout << "P" << SafeSequence[i] << " ";
            }
            cout << endl;
        } else {
            cout << "Request denied due to insufficient resources." << endl;
        }
    } else {
        cout << "Request denied as it exceeds maximum claim." << endl;
    }

    return 0;
}
