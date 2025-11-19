/**
 * LeetCode 1791 - Find Center of Star Graph.
 *
 * A star graph is an undirected graph where there is exactly one center node
 * connected to every other node. If there are n nodes total, then the center
 * has degree n - 1, and all other nodes have degree 1.
 *
 * You are given a 2D array of edges where each edge has the form [u, v],
 * meaning there is an undirected connection between nodes u and v.
 * The task is to return the center of the star graph.
 *
 * <p>Example 1:</p>
 * Input: edges = [[1,2], [2,3], [4,2]]
 * Output: 2
 *
 * <p>Example 2:</p>
 * Input: edges = [[1,2], [5,1], [1,3], [1,4]]
 * Output: 1
 */

 int findCenter(int** edges, int edgesSize, int* edgesColSize) {

    int a1 = edges[0][0];
    int a2 = edges[0][1];
    int b1 = edges[1][0];
    int b2 = edges[1][1];

    if (a1 == b1 || a1 == b2) return a1;
    return a2;
}
