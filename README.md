
# Gamers Database Manager

**Course**: Data Structures (CS218) - Fall 2024  
**Assignment**: #03  
**Author**: Muhammad Moiz Khalid  
**Roll Number**: 23i-2552

## Project Overview

The Gamers Database Manager is a console-based application designed to manage a dataset of players and the games they play. This project implements a custom database management system (DBMS) using a Binary Search Tree (BST) to efficiently store, retrieve, edit, and display player and game data. The system was developed to fulfill specific company queries and adheres to dynamic coding principles to ensure future scalability and modification.

### Objective

The primary goal was to:
1. Dynamically store player and game data in memory using a BST.
2. Implement essential DBMS functionalities, including insertion, search, deletion, data saving, layer display, path traversal, entry editing, and top players retrieval.
3. Optimize each operation's time complexity for efficient performance.

### Seed Generation

The system starts by generating a unique seed based on the user's roll number to determine which data entries to skip during dataset loading. This approach ensures unique data selection for each user.

## Key Features and Functionalities

### 1. **Store the Dataset in Memory**

   - **Description**: The player and game data are read from CSV files and stored in memory using a BST. Nodes are added based on a seed-based selection process.
   - **Time Complexity**: O(log n) for each insertion, given a balanced tree.

### 2. **Insertion**

   - **Description**: The system allows insertion of new players and games. Primary key conflicts are checked before insertion.
   - **Time Complexity**: O(log n) for BST insertion.

### 3. **Search and Retrieval**

   - **Description**: Users can search for players or games based on primary keys. The system returns the relevant node for viewing or modification.
   - **Time Complexity**: O(log n).

### 4. **Deletion**

   - **Description**: Enables deletion of a player or game entry. The BST is restructured to ensure no memory leaks.
   - **Time Complexity**: O(log n) for deletion in a balanced BST.

### 5. **Save Data**

   - **Description**: Saves the BST data to a CSV file in preorder traversal, ensuring the same tree structure on program restart.
   - **Time Complexity**: O(n), where `n` is the number of nodes in the tree.

### 6. **Show N Layers**

   - **Description**: Displays all entries up to the Nth layer in the BST. If N exceeds the tree's height, a warning is shown.
   - **Time Complexity**: O(n) for traversing up to n layers.

### 7. **Show Layer Number**

   - **Description**: Given a primary key, the system returns the layer number of the node.
   - **Time Complexity**: O(log n).

### 8. **Show Path**

   - **Description**: Prints the preorder traversal path taken to locate an entry.
   - **Time Complexity**: O(log n), with the traversal path generated in preorder.

### 9. **Edit Entry**

   - **Description**: Allows editing of any entry, including primary keys. If the key is modified, the node is repositioned in the BST.
   - **Time Complexity**: O(log n) for search, O(log n) for repositioning if needed.

### 10. **Top N Players**

   - **Description**: Finds the top N players based on the number of games played.
   - **Time Complexity**: O(n log n) for sorting players by the number of games.

### 11. **Show Details**

   - **Description**: Searches for a player and displays details of all games they have played.
   - **Time Complexity**: O(log n) for player search, O(n) for displaying `n` games.

### 12. **Has Played**

   - **Description**: Determines if a player has played a specific game using Player ID and Game ID. Achieves a time complexity of at most 2 * log(n).
   - **Time Complexity**: 2 * O(log n).

## Setup and Usage

1. Clone the repository from GitHub.
2. Compile the code with a C++ compiler:
   ```bash
   g++  main.cpp
   ```
3. Run the executable:
   ```bash
   ./a.out
   ```
4. Ensure that the `players.csv` and `games.csv` files are in the same directory for dataset loading.

## Thought Process and Design Decisions

The BST was chosen for its efficiency in dynamic insertion, search, and deletion operations, all of which are central to the DBMS. The choice of recursive and non-recursive traversal methods for various operations reflects an emphasis on optimizing memory usage and ensuring time efficiency. Dynamic solutions were prioritized to support future code modifications and functionality additions.

## Time Complexity Summary

| Operation              | Time Complexity |
|------------------------|-----------------|
| Insertion              | O(log n)        |
| Search                 | O(log n)        |
| Deletion               | O(log n)        |
| Preorder Save to File  | O(n)            |
| Show N Layers          | O(N)            |
| Top N Players          | O(n log n)      |
| Has Played             | 2 O(log n)      |
