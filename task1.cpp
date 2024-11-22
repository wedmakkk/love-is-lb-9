#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <queue>
using namespace std;


typedef struct Node {
    int dest; // ����� �������� �������
    struct Node* next; // ��������� �� ��������� ������� � ������
} Node;

// ������� �������� ����� �������
Node* create_node(int dest) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}


void generate_matrix(int n, float p, int** adjacency_matrix) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = 0;
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((float)rand() / RAND_MAX < p) {
                adjacency_matrix[i][j] = 1;
                adjacency_matrix[j][i] = 1;
            }
        }
    }

}

void print_matrix(int n, int** adjacency_matrix)
{
    printf("Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_to_adj_list(int num_vertices, int** matrix, Node** adj_list) {
    // ������������� ������ ���������
    for (int i = 0; i < num_vertices; i++) {
        adj_list[i] = NULL;
    }

    // �������������� ������� � ������ ���������
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == 1) {
                // ���������� ����� �� i � j
                Node* new_node = create_node(j);
                new_node->next = adj_list[i];
                adj_list[i] = new_node;
            }
        }
    }
}

void** BFS(int** G, int s, int size, int* vis)
{
    queue <int> q;
    q.push(s);

    vis[s] = 0;

    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] == 1 && vis[i] == -1) {
                q.push(i);
                vis[i] = vis[s]+1;
            }
        }
    }
    return 0;
}


int main()
{
    int n;
    float p;


    srand(time(NULL));


    printf("Input count of peaks  : ");
    scanf("%d", &n);

    Node** adj_list = (Node**)malloc(n * sizeof(Node*));

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0;i < n;i++)
    {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    printf("Enter the probability of having an edge (0.0 to 1.0):");
    scanf("%f", &p);
    if (p < 0.0 || p > 1.0) {
        printf("The probability should be in the range from 0.0 to 1.0.\n");

        return 1;
    }
    int* vis = (int*)malloc(n * sizeof(int*));
    for (int i = 0;i < n;i++)
    {
        vis[i] = -1;
    }
    generate_matrix(n, p, matrix);
    print_matrix(n, matrix);
    matrix_to_adj_list(n, matrix, adj_list);
    int s = 0;
	printf("\n");
	printf("input start peek: ");
	scanf_s("%i",&s);
	printf("\n");
    
    BFS(matrix, s, n, vis);
    printf("obhod matrix:");
	printf("\n");
	for(int i = 0;i<n;i++)
	{
		printf("peak #%d: %d",i,vis[i]);
		printf("\n");

	}
    getchar();
    getchar();
    getchar();
    return 0;
}