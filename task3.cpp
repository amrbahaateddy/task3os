#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main() {
    // 1. Read the page references
    ifstream file("refs.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open refs.txt." << endl;
        return 1;
    }

    vector<int> pages;
    int page_num;
    while (file >> page_num) {
        pages.push_back(page_num);
    }
    file.close();

    int total_refs = pages.size();
    if (total_refs == 0) {
        cerr << "Error: The references file is empty." << endl;
        return 1;
    }

    // NEW: Open a CSV file to save our graph data
    ofstream csv_file("results.csv");

    cout << "Frames | Faults per 1000 References" << endl;
    cout << "-----------------------------------" << endl;

    // 2. Simulate the aging algorithm
    for (int num_frames = 1; num_frames <= 10; ++num_frames) {
        unordered_map<int, uint8_t> memory;
        int faults = 0;

        for (int page : pages) {
            // Step A: Age pages
            for (auto& pair : memory) {
                pair.second >>= 1;
            }

            // Step B: Page fault check
            if (memory.find(page) == memory.end()) {
                faults++;
                // Evict if full
                if (memory.size() >= num_frames) {
                    auto evict_it = memory.begin();
                    for (auto it = memory.begin(); it != memory.end(); ++it) {
                        if (it->second < evict_it->second) {
                            evict_it = it;
                        }
                    }
                    memory.erase(evict_it);
                }
                memory[page] = 0;
            }
            // Step C: Mark as used
            memory[page] |= 128;
        }

        // Calculate metric
        double faults_per_1000 = (static_cast<double>(faults) / total_refs) * 1000.0;

        // Print to terminal
        cout << setw(6) << num_frames << " | " << fixed << setprecision(2) << faults_per_1000 << endl;

        // NEW: Save the exact same numbers to the CSV file
        csv_file << num_frames << "," << faults_per_1000 << "\n";
    }

    csv_file.close(); // Close the CSV file
    return 0;
}