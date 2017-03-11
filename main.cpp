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

    // loop to check whether the topology is a ring, star, or fully-connected mesh
    bool condition[] = {true,true,true}; // ring, star, fully-connected mesh are all true until proven otherwise
    unsigned center = 0;
    for (unsigned i=0; i < n; i++) {
        // my implementation
        unsigned edgeCounter = 0;
        for (unsigned j = 0; j < n; j++) {
            if (j == i && W[i][j] != 0) { // validates diagonal
                condition[0] = condition[1] = condition[2] = false;
                goto topologyReport;
            } else if (W[i][j] != W[j][i]) { // validate equality across diagonal
                condition[0] = condition[1] = condition[2] = false;
                goto topologyReport;
            } else if (W[i][j] > 0 && W[i][j] < 100) {
                edgeCounter++;
            }
        }

        // runs after each row has been processed
        if (edgeCounter == (n-1)) {
            condition[0] = false; // not a ring
            center++;
        } else {
            condition[2] = false; // not a fully-connected mesh
            if (edgeCounter != 2) {
                condition[0] = false; // not a ring
            }
        }

        // runs only at the very end of our outer for loop to validate topology conditions
        if (i == (n-1)) {
            if (center != 1) {
                condition[1] = false;
                if (center != n) {
                    condition[2] = false;
                }
            }
        }
    }
    topologyReport:

    cout <<"The topology is"<< endl;
    if (condition[0]) {
        cout <<"ring" << endl;
    } else if (condition[1]) {
        cout <<"star" << endl;
    } else if (condition[2]) {
        cout <<"fully-connected mesh" << endl;
    } else {
        cout <<"neither" << endl;
    }

    // End the chronograph to time the loop
    auto end = chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    cout << "elapsed time: " << diff.count() << " seconds" << endl;
    return EXIT_SUCCESS;
}