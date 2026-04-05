# 🚀 CSS121: Data Structures & Algorithms Lab Assignments

This repository contains a collection of programming assignments for the **CSS121 (Data Structures & Algorithm)** course at King Mongkut's University of Technology Thonburi (KMUTT). The focus of these labs is on implementing fundamental data structures and efficient algorithms using C and C++.

## 📂 Project Overview

### 1. MBTI Neighbor Search (Quick Select Algorithm)
- **File:** `mbti_with_qs.c`,`CSS121_MBTI_2026_68.txt`(dataset which are classmates)
- **Description:** A tool to find the $K$-Nearest Neighbors of a classmate's MBTI cognitive functions using Euclidean Distance.
- **Key Implementation:** - Implemented the **Quick Select** algorithm for efficient selection of the $K$-th smallest element without fully sorting the dataset ($O(n)$ average time complexity).
    - Uses custom `struct` to manage student profiles and cognitive function scores.

### 2. Top-K Score Board (Doubly Linked List)
- **File:** `score_board.cpp`
- **Description:** A dynamic high-score management system that maintains the top scores in real-time.
- **Key Implementation:** - Utilized a **Doubly Linked List** with dummy head and tail nodes to allow efficient insertion and removal of nodes.
    - Implemented logic to automatically remove the lowest score when the board exceeds its maximum size.

### 3. Polynomial Arithmetic (Singly Linked List)
- **File:** `polynomial.cpp`
- **Description:** A mathematical engine designed to handle polynomial operations such as addition and multiplication.
- **Key Implementation:** - **Singly Linked List:** Each node represents a term (Coefficient and Power).
    - **Polynomial Addition:** Merges two polynomials by comparing powers in $O(N+M)$ time.
    - **Polynomial Multiplication:** Implements nested distribution logic to multiply terms and combines like-terms to ensure the result is in simplified form.

## 🛠️ Technical Skills Demonstrated
- **Data Structures:** Singly Linked List, Doubly Linked List, Arrays, Structs.
- **Algorithms:** Quick Select, Euclidean Distance, Polynomial Arithmetic.
- **Languages:** C, C++.
- **Concepts:** Memory Management (Dynamic Allocation), Complexity Analysis (Big O).
