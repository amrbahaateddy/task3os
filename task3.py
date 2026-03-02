import matplotlib.pyplot as plt

# 1. Read the page references from a file
with open('refs.txt', 'r') as f:
    pages = [int(x) for x in f.read().split()]

total_refs = len(pages)
frames_range = range(1, 11) # Testing from 1 to 10 page frames
faults_per_1000 = []

# 2. Simulate the aging algorithm
for num_frames in frames_range:
    memory = {} # Keeps track of pages and their 'age' counters
    faults = 0
    
    for page in pages:
        # Step A: Age all pages currently in memory by shifting bits right
        for p in memory:
            memory[p] >>= 1
            
        # Step B: Check for a page fault
        if page not in memory:
            faults += 1
            # If memory is full, find the smallest counter and kick that page out
            if len(memory) >= num_frames:
                evict = min(memory, key=memory.get)
                del memory[evict]
            # Bring the new page in
            memory[page] = 0
            
        # Step C: Mark the current page as recently used (set top bit to 1)
        memory[page] |= 128
        
    # Calculate the required metric
    faults_per_1000.append((faults / total_refs) * 1000)

# 3. Plot the results
plt.plot(frames_range, faults_per_1000, marker='o')
plt.title('Aging Algorithm Performance')
plt.xlabel('Number of Page Frames')
plt.ylabel('Page Faults per 1000 References')
plt.show()