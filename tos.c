#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 10

typedef struct {
    int N;
    int* final_path;
    bool* visited;
    int final_res;
} Main;

void copyToFinal(Main* main, int curr_path[]) {
    for (int i = 0; i < main->N; i++)
        main->final_path[i] = curr_path[i];
    if (main->N - 1 == 0)
        main->final_path[main->N - 1] = curr_path[0];
}

int firstMin(int** adj, int i, int N) {
    int min_val = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min_val && i != k)
            min_val = adj[i][k];
    return min_val;
}

int secondMin(int** adj, int i, int N) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

void TSPRec(int** adj, Main* main, int curr_bound, int curr_weight,
            int level, int curr_path[]) {

    if (level == main->N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];

            if (curr_res < main->final_res) {
                copyToFinal(main, curr_path);
                main->final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < main->N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !main->visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1], main->N) +
                               firstMin(adj, i, main->N)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1], main->N) +
                                firstMin(adj, i, main->N)) / 2);

            if (curr_bound + curr_weight < main->final_res) {
                curr_path[level] = i;
                main->visited[i] = true;

                TSPRec(adj, main, curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            memset(main->visited, false, main->N * sizeof(bool));
            for (int j = 0; j <= level - 1; j++)
                main->visited[curr_path[j]] = true;
        }
    }
}

void TSP(int** adj, Main* main) {
    int* curr_path = (int*)malloc((main->N + 1) * sizeof(int));

    int curr_bound = 0;
    memset(curr_path, -1, (main->N + 1) * sizeof(int));
    memset(main->visited, false, main->N * sizeof(bool));

    for (int i = 0; i < main->N; i++)
        curr_bound += (firstMin(adj, i, main->N) + secondMin(adj, i, main->N));

    curr_bound = (curr_bound == 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    main->visited[0] = true;
    curr_path[0] = 0;

    TSPRec(adj, main, curr_bound, 0, 1, curr_path);
}

int main() {
    int n;
    printf("Enter the number of cities visited: ");
    scanf("%d", &n);

    int** adj = (int**)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
    }

    Main main;
    main.N = n;
    main.final_path = (int*)malloc((n + 1) * sizeof(int));
    main.visited = (bool*)malloc(n * sizeof(bool));
    main.final_res = INT_MAX;

    TSP(adj, &main);

    printf("Minimum cost: %d\n", main.final_res);
    printf("Path Taken: ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", main.final_path[i] + 1); // Adju i   
         }
    printf("\n");

    // Clean up dynamically allocated memory
    for (int i = 0; i < n; i++)
        free(adj[i]);
    free(adj);

    free(main.final_path);
    free(main.visited);

    return 0;
}