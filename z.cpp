#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class RingAlgorithm
{
private:
    vector<int> processes;
    int leader;

public:
    RingAlgorithm(const vector<int> &procList)
    {
        processes = procList;
        sort(processes.begin(), processes.end());
        leader = -1;
    }

    void startElection(int initiator)
    {
        cout << "Process " << initiator << " starts an election." << endl;
        vector<int> electionRing;

        auto it = find(processes.begin(), processes.end(), initiator);
        if (it == processes.end())
        {
            cout << "Error: Initiator process " << initiator << " not found." << endl;
            return;
        }

        int index = it - processes.begin();
        for (size_t i = 0; i < processes.size(); ++i)
        {
            int process = processes[(index + i) % processes.size()];
            electionRing.push_back(process);
            cout << "Process " << process << " passes the election message." << endl;
        }

        leader = *max_element(electionRing.begin(), electionRing.end());
        cout << "Process " << leader << " is elected as the leader." << endl;
    }
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes;
    cout << "Enter process IDs: " << endl;
    for (int i = 0; i < n; ++i)
    {
        int id;
        cin >> id;
        processes.push_back(id);
    }

    int initiator;
    cout << "Enter the initiator process ID: ";
    cin >> initiator;

    RingAlgorithm ring(processes);
    ring.startElection(initiator);
    
    return 0;
}
