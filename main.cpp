// Assignment 2: Topology recognition problem
// Michael Romero - CPSC 335 - March 16, 2017

// Given a network with n>3 nodes and a weight matrix W[0..n−1, 0..n−1] of
// positive integers, of a weighted, connected undirected graph modeling
// a network, decide whether the network is one of the topologies, if any:
// ring, star, fully connected mesh. Note: represent infinity by the value 100.
// INPUT: a positive integer n and a list of n^2 positive values
// OUTPUT: message "ring" or "star" or "complete" or "neither"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

using namespace std;

int main() {
    int n, i, j, count;
    int W[100][100];

    // display the header
    cout << endl << "CPSC 335-x - Programming Assignment #2" << endl;
    cout << "Topology recognition algorithm" << endl;
    cout << "Enter the number of nodes in the topology" << endl;
    // read the number of nodes
    cin >> n;
    // read the weight matrix
    cout << "Enter the positive weights, 100 for infinity" << endl;
    for(i=0; i < n; i++)
        for(j=0; j < n; j++)
            cin >> W[i][j];

    // Start the chronograph to time the execution of the algorithm
    auto start = chrono::high_resolution_clock::now();

    // check whether the topology is a ring, star, or fully-connected mesh
    bool condition[] = {true,true,true};    // 3
    unsigned center = 0, starVertex = 0;    // 2
    for (unsigned i=0; i < n; i++) {        // ((n-1 - 0)/1 - 1) == n, n*(1 + 8n + 7 + 7) = 8n^2 + 15n
        unsigned edgeCounter = 0;           // 1
        for (unsigned j = 0; j < n; j++) {  // ((n-1 - 0)/1 - 1) == n, n * max(7,8,8) = 8n
            if (j == i && W[i][j] != 0) {   // 3 -> (3) + (3 + 1) = 7
                condition[0] = condition[1] = condition[2] = false; // 3
                goto topologyReport; // 1
            } else if (W[i][j] != W[j][i]) {// 1 -> (3 + 1) + (3 + 1) = 8
                condition[0] = condition[1] = condition[2] = false; // 3
                goto topologyReport; // 1
            } else if (W[i][j] > 0 && W[i][j] < 100) { // 3 -> (3 + 1 + 3) + 1 = 8
                edgeCounter++; // 1
            }
        }
        if (edgeCounter == (n-1)) { // 2 -> 2 + (1 + 1) = 4   --> max(4,7) = 7
            condition[0] = false; // 1
            center++; // 1
        } else { // 2 + (1 + 2 + 2) = 7
            condition[2] = false; // 1
            if (edgeCounter != 2) { // 1 -> 1 + 1 = 2
                condition[0] = false; // 1
            }
            if (edgeCounter == 1) { // 1 -> 1 + 1 = 2
                starVertex++; // 1
            }
        }
        // runs only at the very end of our outer for loop to validate topology conditions{
        if (i == (n-1)) { // 2 + max(4,5) = 2 + 5 = 7
            if (center != 1) { // 1 -> 1 + (1 + 2) = 4
                condition[1] = false; // 1
                if (center != n) { // 1 -> 1 + 1 = 2
                    condition[2] = false; // 1
                }
            } else { // 2 + 3 = 5
                if (starVertex != (n-1)) { // 2 -> 2 + 1 = 3
                    condition[1] = false; // 1
                }
            }
        }
    }
    topologyReport: // 1
    cout <<"The topology is"<< endl; // 1
    if (condition[0]) { // 1 -> 1 + 1 = 2 -> max(2,3,4,4) = 4
        cout <<"ring" << endl; // 1
    } else if (condition[1]) { // 1 -> (1 + 1) + 1 = 3
        cout <<"star" << endl; // 1
    } else if (condition[2]) { // 1 -> (1 + 1 + 1) + 1 = 4
        cout <<"complete" << endl; // 1
    } else { // 0 -> (1 + 1 + 1 + 0) + 1 = 4
        cout <<"neither" << endl; // 1
    }
    // Total Count: 3 + 2 + 8n^2 + 15n + 1 + 1 + 4 = 8n^2 + 15n + 11
    // End the chronograph to time the loop
    auto end = chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "elapsed time: " << diff.count() << " seconds" << endl;
    return EXIT_SUCCESS;
}