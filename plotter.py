import matplotlib.pyplot as plt
import csv

frames = []
faults_per_1000 = []

# Read the data saved by your C++ program
with open('results.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        frames.append(int(row[0]))        # First column is the number of frames
        faults_per_1000.append(float(row[1])) # Second column is the faults

# Plot the graph
plt.plot(frames, faults_per_1000, marker='o')
plt.title('Aging Algorithm Performance (C++ Output)')
plt.xlabel('Number of Page Frames')
plt.ylabel('Page Faults per 1000 References')
plt.grid(True)
plt.show()