# -*- coding: utf-8 -*-
"""dij_2b.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/16XcW16cIYLgyrrwiqgMNlXKlx4JV9z_A
"""

import heapq

def dijkstra(graph, start):
    # Initialize distances and predecessors
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]
    visited = set()

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_node in visited:
            continue

        visited.add(current_node)

        for neighbor in graph[current_node]:
            distance = current_distance + 1  # Assuming all edge weights are 1

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))

    return distances

# Define the graph
graph = {
    0: [5, 7],
    5: [0, 7, 3, 1],
    7: [0, 5, 3, 8, 1, 4],
    1: [5, 7],
    3: [5, 6, 2, 7],
    4: [7, 8],
    2: [3],
    6: [3],
    8: [4, 7]
}

# Get distances from node 0 to all other nodes
distances = dijkstra(graph, 0)

# Sort nodes by distance and then by their label in the event of a tie
sorted_nodes = sorted(distances, key=lambda x: (distances[x], x))

# Filter the sorted list to only include nodes from N0
N0 = {1, 3, 4, 5, 7}
L0 = [node for node in sorted_nodes if node in N0]

print(L0)