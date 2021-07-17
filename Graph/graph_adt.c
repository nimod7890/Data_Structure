#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_NUM 100

typedef struct _NODE {
    char data;
    struct _NODE* edge_to;
    int edge_cnt;
    int visited;
}NODE;
typedef struct _graph {
    NODE* vertex[MAX_VERTEX_NUM];
    int vertex_cnt;
    int crr;
}G;

void create(G* graph) {
    graph->crr = 0;
    graph->vertex_cnt = 0;
}

void insert(G* graph, char data) {
    NODE* vertex = malloc(sizeof(NODE));
    graph->vertex[graph->crr] = vertex;
    graph->vertex[graph->crr]->data = data;
    graph->vertex[graph->crr]->edge_cnt = 0;
    graph->vertex[graph->crr]->edge_to = NULL;
    graph->crr++;
    graph->vertex_cnt++;
}

void reset_visited(G* graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertex[i]->visited = FALSE;
        if (i == graph->vertex_cnt - 1) break;
    }
}

int is_upper(char data) {
    if (data >= 'A' && data <= 'Z') return TRUE;
    else if (data >= 'a' && data <= 'b') return FALSE;
}

NODE* search(G* graph, char data) {
    char upper_data = data - 32;
    char lower_data = data + 32;
    if (graph->vertex_cnt == 0) return NULL;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (is_upper(graph->vertex[i]->data) == TRUE) {
            if (is_upper(data) == TRUE) {
                if (graph->vertex[i]->data == data) {
                    return graph->vertex[i];
                }
            }
            else {
                if (graph->vertex[i]->data == upper_data) {
                    return graph->vertex[i];
                }
            }
        }
        else {
            if (is_upper(data) == TRUE) {
                if (graph->vertex[i]->data == lower_data) {
                    return graph->vertex[i];
                }
            }
            else {
                if (graph->vertex[i]->data == data) {
                    return graph->vertex[i];
                }
            }
        }

        if (i == graph->vertex_cnt - 1) break;
    }
    return NULL;
}


void visited(G* graph, NODE* node) {
    if (node->visited == TRUE) return;
    node->visited = TRUE;
    NODE* edge = node->edge_to;
    while (edge != NULL) {
        visited(graph, search(graph, edge->data));
        edge = edge->edge_to;
    }
}


void print(G* graph) {
    int cnt = 0;
    printf("(");
    while (cnt != graph->vertex_cnt) {
        printf("%c", graph->vertex[cnt]->data);
        if (graph->vertex[cnt]->edge_cnt != 0) {
            NODE* edge = graph->vertex[cnt]->edge_to;
            printf("(");
            while (edge != NULL) {
                printf("%c", edge->data);
                if (edge->edge_to != NULL) {
                    printf(",");
                }
                edge = edge->edge_to;
            }
            printf(")");
        }
        if (cnt != graph->vertex_cnt - 1) {
            printf(",");
        }
        cnt++;
    }
    printf(")");
}
void print_vertex(G* graph) {
    int cnt = 0;
    printf("\n\n\tvertex : {");
    while (cnt != graph->vertex_cnt) {
        printf("%c", graph->vertex[cnt]->data);

        if (cnt != graph->vertex_cnt - 1) {
            printf(",");
        }
        cnt++;
    }
    printf("}\n");
}

void num_of_vertex(G* graph) {
    printf("\n\n\tnumber of vertex : %d\n", graph->vertex_cnt);
}
void degree_of_vertex(NODE* vertex) {
    printf("\n\n\tdegree of vertex {%c} : %d\n", vertex->data, vertex->edge_cnt);
}

void is_empty(G* graph) {
    if (graph->vertex_cnt == 0) printf("\n\n\tThis graph is empty\n");
    else printf("\n\n\tThis graph is not empty\n");
}

void adjacent(NODE* vertex) {
    if (vertex->edge_cnt == 0) printf("\n\n\t{%c} does not have adjacent vertex\n", vertex->data);
    else {
        NODE* edge = vertex->edge_to;
        printf("\n\n\t{%c}'s adjacent vertex : {", vertex->data);
        while (edge != NULL) {
            printf("%c", edge->data);
            if (edge->edge_to != NULL) {
                printf(",");
            }
            edge = edge->edge_to;
        }
        printf("}\n");
    }
}

void path_existed(G* graph, NODE* start,NODE* end) {
    reset_visited(graph);
    visited(graph,start);
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->data == end->data) {
            if (graph->vertex[i]->visited == FALSE) {
                printf("\n\n\t{%c} and {%c} is not connected\n", start->data, end->data);
                return;
            }
            else {
                printf("\n\n\t{%c} and {%c} is connected\n", start->data, end->data);
                return;
            }
        }
        if (i == graph->vertex_cnt - 1) break;
    }
}

void is_connected(G* graph) {
    reset_visited(graph);
    visited(graph, graph->vertex[0]);
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->visited == FALSE) {
            printf("\n\n\tThis graph is not connected\n");
            return;
        }
        if (i == graph->vertex_cnt - 1) break;
    }
    printf("\n\n\tThis graph is connected\n");
}

void num_of_edge(G* graph) {
    int edge = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        edge += graph->vertex[i]->edge_cnt;
        if (i == graph->vertex_cnt - 1) break;
    }
    printf("\n\n\tnumber of edge : %d\n", edge / 2);
}
int edge_exist(NODE* vertex, NODE* vertex2) {
    if (vertex->edge_cnt == 0)
        return FALSE;
    else {
        NODE* edge = vertex->edge_to;
        while (edge != NULL) {
            if (edge->data == vertex2->data) return TRUE;
            edge = edge->edge_to;
        }
    }
    return FALSE;
}

void add_edge(NODE* vertex, NODE* vertex2) {

    NODE* data_of_vertex2 = malloc(sizeof(NODE));
    data_of_vertex2->data = vertex2->data;
    if (vertex->edge_cnt == 0) {
        vertex->edge_to = data_of_vertex2;
    }
    else {
        NODE* edge = vertex->edge_to;
        while (edge->edge_to != NULL) {
            edge = edge->edge_to;
        }
        edge->edge_to = data_of_vertex2;
    }


    NODE* data_of_vertex = malloc(sizeof(NODE));
    data_of_vertex->data = vertex->data;
    if (vertex2->edge_cnt == 0) {
        vertex2->edge_to = data_of_vertex;
    }
    else {
        NODE* edge = vertex2->edge_to;
        while (edge->edge_to != NULL) {
            edge = edge->edge_to;
        }
        edge->edge_to = data_of_vertex;
    }
    data_of_vertex->edge_to = NULL;
    data_of_vertex2->edge_to = NULL;
    vertex->edge_cnt++;
    vertex2->edge_cnt++;
}

void delete_edge(NODE* vertex, NODE* vertex2) {
    if (vertex->edge_cnt == 1) {
        vertex->edge_to = NULL;
    }
    else if (vertex->edge_to->data == vertex2->data) {
        NODE* edge = vertex->edge_to;
        vertex->edge_to = edge->edge_to;
        free(edge);
    }
    else {
        NODE* edge = vertex->edge_to;
        while (edge != NULL) {
            if (edge->edge_to->data = vertex2->data) {//�������� �ش� vertex��
                if (edge->edge_to == NULL) {//�ǳ�
                    NODE* edge_to = edge->edge_to;
                    free(edge_to);
                    edge->edge_to = NULL;
                }
                else {//�� �� �ƴϸ�
                    NODE* edge_to = edge->edge_to;
                    edge->edge_to = edge_to->edge_to;
                    free(edge_to);
                }
            }
            edge = edge->edge_to;
        }
    }

    if (vertex2->edge_cnt == 1) {
        vertex2->edge_to = NULL;
    }
    else if (vertex2->edge_to->data == vertex->data) {
        NODE* edge = vertex2->edge_to;
        vertex2->edge_to = edge->edge_to;
        free(edge);
    }
    else {
        NODE* edge = vertex2->edge_to;
        while (edge != NULL) {
            if (edge->edge_to->data = vertex->data) {//�������� �ش� vertex��
                if (edge->edge_to == NULL) {//�ǳ�
                    NODE* edge_to = edge->edge_to;
                    free(edge_to);
                    edge->edge_to = NULL;
                }
                else {//�� �� �ƴϸ�
                    NODE* edge_to = edge->edge_to;
                    edge->edge_to = edge_to->edge_to;
                    free(edge_to);
                }
            }
            edge = edge->edge_to;
        }
    }
    vertex->edge_cnt--;
    vertex2->edge_cnt--;

}

void delete(G* graph, NODE* vertex) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (edge_exist(vertex, graph->vertex[i]) == TRUE)
            delete_edge(vertex, graph->vertex[i]);
        if (i == graph->vertex_cnt - 1) break;
    }
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->data == vertex->data) {
            NODE* tmp = graph->vertex[i];
            for (int j = i; j < graph->vertex_cnt; j++)
                graph->vertex[j] = graph->vertex[j + 1];
            free(tmp);
            break;
        }
        if (i == graph->vertex_cnt - 1) break;
    }
    graph->vertex_cnt--;
    graph->crr--;
}

void rename_vertex(G* graph, NODE* vertex, char data) {
    if (vertex->edge_cnt != 0) {//edge ������
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {
            NODE* edge = graph->vertex[i]->edge_to;
            while (edge != NULL) {
                if (edge->data == vertex->data) {
                    edge->data = data;
                }
                edge = edge->edge_to;
            }
            if (i == graph->vertex_cnt - 1) break;
        }
    }
    vertex->data = data;
}

void swap(G* graph, NODE* vertex, NODE* vertex2) {
    char tmp = vertex->data;
    char tmp2 = vertex2->data;
    rename_vertex(graph, vertex, '*');
    rename_vertex(graph, vertex2, tmp);
    rename_vertex(graph, vertex, tmp2);
}

void upper_to_lower(G* graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->data >= 'A' && graph->vertex[i]->data <= 'Z') {
            rename_vertex(graph, graph->vertex[i], graph->vertex[i]->data + 32);
        }
        if (i == graph->vertex_cnt - 1) break;
    }
}
void lower_to_upper(G* graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->data >= 'a' && graph->vertex[i]->data <= 'z') {
            rename_vertex(graph, graph->vertex[i], graph->vertex[i]->data - 32);
        }
        if (i == graph->vertex_cnt - 1) break;
    }
}

void trade(G* graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (graph->vertex[i]->data >= 'a' && graph->vertex[i]->data <= 'z') {
            rename_vertex(graph, graph->vertex[i], graph->vertex[i]->data - 32);
        }
        else if (graph->vertex[i]->data >= 'A' && graph->vertex[i]->data <= 'Z') {
            rename_vertex(graph, graph->vertex[i], graph->vertex[i]->data + 32);
        }
        if (i == graph->vertex_cnt - 1) break;
    }
}

void clear(G* graph) {
    while (graph->vertex_cnt != 0) {
        delete(graph, graph->vertex[0]);
    }
}

void screen() {
    printf("\n\n\t");
    printf("===================================================================");
    printf("\n\n\t                          GRAPH FUNCTION\n\t");
    printf("\n\t  ****CAPITALIZE all the COMMANDSs\t");
    printf("\n\t  ****You can enter both upper and lower, but they are the same");
    printf("\n\t  ****Do not use space bar\n\t");
    printf("\n\t-------------------------------------------------------------------");
    printf("\n\t  G                         create graph");//
    printf("\n\t  +n                        insert node");//
    printf("\n\t  -n                        delete node");//
    printf("\n\t  En1n2                     add edge between n1 and n2");//
    printf("\n\t  Dn1n2                     delete edge between n1 and n2");//
    printf("\n\t  X                         number of vertex");//
    printf("\n\t  H                         number of edge");//
    printf("\n\t  Vn                        degree of vertex");//
    printf("\n\t  An                        adjacent vertex");//
    printf("\n\t  N                         check if graph is empty");//
    printf("\n\t  C                         check if graph is connected");//
    printf("\n\t  Pn1n2                     check if they are connected");//
    printf("\n\t  Rn1n2                     rename n1 to n2");//
    printf("\n\t  Sn1n2                     swap n1 and n2");//���
    printf("\n\t  U                         uppercase letters as lowercase letters");//���
    printf("\n\t  W                         lowercase letters as uppercase letters");//���
    printf("\n\t  Z                         upper to lower and lower to upper");//���
    printf("\n\t  L                         print graph");//
    printf("\n\t  T                         print vertex");//���
    printf("\n\t  K                         clear");
    printf("\n\t-------------------------------------------------------------------");
    printf("\n\t  Q                         quit");
    printf("\n\t===================================================================");
}

int main() {
    G* graph = malloc(sizeof(G));

    screen();
    int creategraph = FALSE;
    int go = TRUE;
    while (go) {
        NODE* vertex = malloc(sizeof(NODE));
        NODE* vertex2 = malloc(sizeof(NODE));
        printf("\n\t");
        if (creategraph == FALSE) printf("This graph is not created yet\n\tPlease create graph first");
        else print(graph);
        char order[30] = { 0 };
        printf("\n\t>>> ");
        gets(order);
        for (int i = 0; i < strlen(order); i++) {
            switch (order[i]) {
            case'G':
                if (creategraph == FALSE) {
                    create(graph);
                    creategraph = TRUE;
                }
                else {
                    printf("\n\n\tGraph is already created\n");
                }
                break;
            case'L':
                break;
            case '+':
                if (creategraph == FALSE || order[i + 1] == '\0') break;
                vertex = search(graph, order[i + 1]);
                if (vertex != NULL) printf("\n\n\t{%c} is already in graph\n", order[i + 1]);
                else insert(graph, order[i + 1]);
                i += 6;
                break;
            case'-':
                if (creategraph == FALSE || order[i + 1] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                if (vertex == NULL) printf("\n\n\tthis vertex is not in graph\n");
                else delete(graph, vertex);
                i += 6;
                break;
            case'V':
                if (creategraph == FALSE || order[i + 1] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                if (vertex == NULL) printf("\n\n\tthis vertex is not in graph\n");
                else degree_of_vertex(vertex);
                i += 6;
                break;
            case'A':
                if (creategraph == FALSE || order[i + 1] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                if (vertex == NULL) printf("\n\n\tthis vertex is not in graph\n");
                else adjacent(vertex);
                i += 6;
                break;
            case'R':
                if (creategraph == FALSE || order[i + 1] == '\0' || order[i + 2] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                vertex2 = search(graph, order[i + 2]);
                if (vertex == NULL) printf("\n\n\t{%c} is not in graph\n", order[i + 1]);
                else if (vertex2 != NULL) printf("\n\n\t{%c} is already in graph\n", order[i + 2]);
                else rename_vertex(graph, vertex, order[i + 2]);
                i += 6;
                break;
            case'S':
                if (creategraph == FALSE || order[i + 1] == '\0' || order[i + 2] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                vertex2 = search(graph, order[i + 2]);
                if (vertex == NULL && vertex2 == NULL) printf("\n\n\t{%c} and {%c} are not in graph\n", vertex->data, vertex2->data);
                else if (vertex == NULL) printf("\n\n\t{%c} is not in graph\n", order[i + 1]);
                else if (vertex2 == NULL)printf("\n\n\t{%c} is not in graph\n", order[i + 2]);
                else swap(graph, vertex, vertex2);
                i += 6;
                break;
            case'P':
                if (creategraph == FALSE || order[i + 1] == '\0' || order[i + 2] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                vertex2 = search(graph, order[i + 2]);
                if (vertex == NULL && vertex2 == NULL) printf("\n\n\t{%c} and {%c} are not in graph\n", vertex->data, vertex2->data);
                else if (vertex == NULL) printf("\n\n\t{%c} is not in graph\n", order[i + 1]);
                else if (vertex2 == NULL)printf("\n\n\t{%c} is not in graph\n", order[i + 2]);
                else path_existed(graph, vertex, vertex2);
                i += 6;
                break;
            case'E':
                if (creategraph == FALSE || order[i + 1] == '\0' || order[i + 2] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                vertex2 = search(graph, order[i + 2]);
                if (vertex == NULL && vertex2 == NULL) printf("\n\n\t{%c} and {%c} are not in graph\n", vertex->data, vertex2->data);
                else if (vertex == NULL) printf("\n\n\t{%c} is not in graph\n", order[i + 1]);
                else if (vertex2 == NULL)printf("\n\n\t{%c} is not in graph\n", order[i + 2]);
                else {
                    if (edge_exist(vertex, vertex2) == TRUE)
                        printf("\n\n\t{%c} and {%c} are already connected\n", vertex->data, vertex2->data);
                    else add_edge(vertex, vertex2);
                }i += 6;
                break;
            case'D':
                if (creategraph == FALSE || order[i + 1] == '\0' || order[i + 2] == '\0') break;
                else if (graph->vertex_cnt == 0) break;
                vertex = search(graph, order[i + 1]);
                vertex2 = search(graph, order[i + 2]);
                if (vertex == NULL && vertex2 == NULL) printf("\n\n\t{%c} and {%c} are not in graph\n", vertex->data, vertex2->data);
                else if (vertex == NULL) printf("\n\n\t{%c} is not in graph\n", order[i + 1]);
                else if (vertex2 == NULL)printf("\n\n\t{%c} is not in graph\n", order[i + 2]);
                else {
                    if (edge_exist(vertex, vertex2) == FALSE)
                        printf("\n\n\t{%c} and {%c} are already not connected\n", vertex->data, vertex2->data);
                    else delete_edge(vertex, vertex2);
                }i += 6;
                break;
            case'T':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') print_vertex(graph);
                i++;
                break;
            case'U':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') upper_to_lower(graph);
                i++;
                break;
            case'W':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') lower_to_upper(graph);
                i++;
                break;
            case'Z':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') trade(graph);
                i++;
                break;
            case'X':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') num_of_vertex(graph);
                i++;
                break;
            case'N':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') is_empty(graph);
                i++;
                break;
            case'C':
                if (creategraph == FALSE)break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') is_connected(graph);
                i++;
                break;
            case'H':
                if (creategraph == FALSE) break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') num_of_edge(graph);
                break;
            case'K':
                if (creategraph == FALSE) break;
                else if (graph->vertex_cnt == 0) break;
                if (order[i + 1] == '\0') clear(graph);
                i++;
                break;
            case'Q':
                if (creategraph == FALSE) break;
                if (order[i + 1] == '\0') {
                    clear(graph);
                    printf("\n\n\t\t\t\t\t\t\t\t-end-\n\n\n\n");
                    go = FALSE;
                }break;
            default:
                break;
            }//switch
        }//for

    }//while
    return 0;
}