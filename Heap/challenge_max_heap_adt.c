#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAXNUMOFHEAP 100

typedef struct _NODE {
    int data;
    struct _NODE* left_child;
    struct _NODE* right_child;
}NODE;

typedef struct {
    NODE* root;
    int tree_size;
}T;
typedef struct {
    NODE* heap[MAXNUMOFHEAP];
    int heap_size;
} H;

void create_max_heap(H* heap) {
    heap->heap_size = 0;
}
void create_bst_tree(T* tree) {
    NODE* root = malloc(sizeof(NODE));
    tree->root = root;
    tree->root->left_child = NULL;
    tree->root->right_child = NULL;
    tree->root->data = '\0';
    tree->tree_size = 0;
}


int is_left_child(NODE* node) {
    if (node == NULL) return FALSE;
    if (node->left_child != NULL)return TRUE;
    else return FALSE;
}
int is_right_child(NODE* node) {
    if (node == NULL) return FALSE;
    if (node->right_child != NULL)return TRUE;
    else return FALSE;
}
int degree_of_node(NODE* parent) {

    if (is_left_child(parent) == FALSE && is_right_child(parent) == FALSE) return 0;
    else if (is_left_child(parent) == FALSE || is_right_child(parent) == FALSE)return 1;
    else return 2;
}
NODE* get_parent(NODE* root, int data) {//맨 처음 시작 tree->root
    NODE* cur = root;
    NODE* parent = NULL;
    while (cur != NULL) {
        if (cur->data == data) {
            return parent;
        }
        else if (cur->data > data) {
            parent = cur;
            cur = cur->left_child;
        }
        else {
            parent = cur;
            cur = cur->right_child;
        }
    }
    return NULL;
}
NODE* get_left_child(NODE* node) {
    if (node == NULL) return NULL;
    int n = is_left_child(node);
    if (n == TRUE) return node->left_child;
    /* if (n == TRUE) {
        NODE* leftchild = node->left_child;
        leftchild->data = node->left_child->data;
        return leftchild;
    }*/
    else return NULL;
}//isleftchild 참이면 값 반환
NODE* get_right_child(NODE* node) {
    if (node == NULL)return NULL;
    int n = is_right_child(node);
    if (n == TRUE) return node->right_child;
    else return NULL;
}//isrightchild 참이면 값 반환 거짓이면 NULL반환
NODE* get_min(NODE* root) {
    if (root == NULL)return NULL;
    while (root->left_child != NULL) {
        root = root->left_child;
    }
    return root;
}//inorder첫번째 값
NODE* get_max(NODE* root) {
    if (root == NULL)return NULL;
    while (root->right_child != NULL) {
        root = root->right_child;
    }
    return root;
}

void delete_node(T* tree, NODE* node) {
    if (node == NULL)return;
    int n = degree_of_node(node);
    NODE* rmv = node;
    if (node == tree->root) {//지우려 한 게 root노드 면
        if (n == 0) {
            tree->root->data = '\0';
        }
        else if (n == 1) {
            tree->root = tree->root->left_child != NULL ? tree->root->left_child : tree->root->right_child;//연결
            free(rmv);
        }
        else {//degree(node)==2
            NODE* max = get_max(tree->root->left_child);//왼쪽 서브노트의 가장 오른쪽 노드
            NODE* maxparent = get_parent(tree->root, max->data);
            if (maxparent == tree->root) {//왼쪽 서브노트의 최댓값이 왼쪽 서브노트의 루트면  
                max->right_child = tree->root->right_child;
                tree->root->left_child = NULL;
                tree->root->right_child = NULL;
                tree->root = max;//
                free(rmv);
            }
            else {//왼쪽 서브노트의 최댓값이 루트 아닌 다음 값들이면
                max->right_child = tree->root->right_child;
                if (max->left_child != NULL) {
                    NODE* tmp = max;
                    while (tmp->left_child != NULL) {
                        tmp = tmp->left_child;
                    }
                    tmp->left_child = tree->root->left_child;
                }
                else max->left_child = tree->root->left_child;
                tree->root->left_child = NULL;
                tree->root->right_child = NULL;
                maxparent->right_child = NULL;//max윗부분 연결 끊기
                tree->root = max;
                free(rmv);
            }
        }
    }
    else {//root node 아니면
        NODE* parent = get_parent(tree->root, node->data);//parent구하셈
        if (n == 0) {
            if (node == get_left_child(parent)) parent->left_child = NULL;//왼쪽자식일때
            else parent->right_child = NULL;//오른쪽 자식일때
            free(rmv);
        }
        else if (n == 1) {
            if (node == get_left_child(parent)) {//지울 노드가 왼쪽 자식이면
                if (node->left_child != NULL) {//지울 노드의 자식이 왼쪽에 있으면
                    parent->left_child = node->left_child;
                }
                else {//지울 노드의 자식이 오른쪽에 있으면
                    parent->left_child = node->right_child;
                }
                free(rmv);
            }
            else {//지울 노드가 오른쪽 자식이면
                if (node->left_child != NULL) {//지울 노드의 자식이 왼쪽에 있으면
                    parent->right_child = node->left_child;
                }
                else {//지울 노드의 자식이 오른쪽에 있으면
                    parent->right_child = node->right_child;
                }
                free(rmv);
            }
        }
        else {//degree(node)==2
            NODE* max = get_max(node->left_child);//지울 노드의 왼쪽 서브노트의 가장 오른쪽 노드
            //max->right_child = node->right_child;
            NODE* maxparent = get_parent(tree->root, max->data);
            if (maxparent == node) {//왼쪽 서브노트의 최댓값이 왼쪽 서브노트의 루트면  
                parent->left_child = node->left_child;//parent다음 노드 연결
                max->right_child = node->right_child;
                node->left_child = NULL;
                node->right_child = NULL;
                free(rmv);
            }
            else {//왼쪽 서브노트의 최댓값이 루트 아닌 다음 값들이면
                parent->left_child = max;
                node->right_child->left_child = node->right_child;
                node->left_child = NULL;
                if (max->left_child != NULL) {
                    NODE* tmp = max;
                    while (tmp->left_child != NULL) {
                        tmp = tmp->left_child;
                    }
                    tmp->left_child = node->right_child;
                }
                else max->left_child = node->right_child;
                maxparent->right_child = NULL;
                free(rmv);
            }
        }
    }
    tree->tree_size--;
}//
void clear(T* tree) {
    while (tree->tree_size != 0) delete_node(tree, tree->root);
}

NODE* find_tree_node(NODE* node, int data) {//탐색 성공시 return null //실패 시 실패한 위치 반환

    if (node == NULL) return node;//있어야하나 ? 나중에 확인 ㄱ ㄱ 
    if (data == node->data) return NULL;
    //같으면

    NODE* leftchild = get_left_child(node);
    NODE* rightchild = get_right_child(node);
    //자식 없으면 해당 노드 반환
    if (leftchild == NULL && rightchild == NULL) return node;

    if (data < node->data) {//왼쪽으로
        
        if (leftchild != NULL) {//왼쪽값이 차있으면
            if (leftchild->data == data)  return NULL;//왼쪽 값 같으면
            else if (data < leftchild->data) {//왼쪽의 왼쪽ㄱㄱ
                if (leftchild->left_child != NULL) {//차있으면
                    NODE* baby = find_tree_node(leftchild->left_child, data);
                    return baby;
                }
                else return leftchild;//비어있으면
            }
            else if (data > leftchild->data) {//왼쪽의 오른쪽으로
                if (leftchild->right_child != NULL) {

                    NODE* baby = find_tree_node(leftchild->right_child, data);
                    return baby;
                }
                else return leftchild;
            }
            else return leftchild;
        }
        else return node;//왼쪽 비어있으면
    }//왼쪽
    else if (data > node->data) {//오른쪽으로

        if (rightchild != NULL) {//오른쪽 값 차있으면
            if (rightchild->data == data) return NULL;
            else if (data < rightchild->data) {//오른쪽의 왼쪽 값으로
                if (rightchild->left_child != NULL) {
                    NODE* baby = find_tree_node(rightchild->left_child, data);
                    return baby;
                }
                else return rightchild;
            }
            else if (data > rightchild->data) {//오른쪽의 오른쪽으로
                if (rightchild->right_child != NULL) {
                    NODE* baby = find_tree_node(rightchild->right_child, data);
                    return baby;
                }
                else return rightchild;
            }
            else return rightchild;
        }
        else return node;//오른쪽 빔
    }//오른쪽
    else return node;
}

void insert_heap_node(H* heap,NODE* data) {
    int i;
    i = ++(heap->heap_size);
    //printf("\n\tinserting : %d", data->data);//확인 작업
    //printf("\ni == %d\theapsize %d", i, heap->heap_size);
    if (i == 1) {
        heap->heap[i] = data;
        return;
    }
    while (i!=1){
        if (data->data > heap->heap[i / 2]->data) {
            heap->heap[i] = heap->heap[i / 2];
            i /= 2;
        }
        else break;
    }
    heap->heap[i] = data;
}
void insert_tree_node(T* tree, NODE* putposition, int data) {

    NODE* newnode = malloc(sizeof(NODE));
    if (data < putposition->data)
        putposition->left_child = newnode;
    else if (data > putposition->data)
        putposition->right_child = newnode;
    newnode->left_child = NULL;
    newnode->right_child = NULL;
    newnode->data = data;
    tree->tree_size++;
}

void print_heap( H* heap) {
    int i = 1;
    while (i != heap->heap_size+1) {
        printf("%d ", heap->heap[i]->data);
        i++;
    }
}
void print_tree(NODE* treeroot, NODE* treechild)
{
    NODE* crr = treechild->left_child;
    if (treeroot == treechild) {
        printf("\n\tMAX HEAP changed to BST\n\t>>> %d", treeroot->data);//root 출력
    }
    if (treechild->left_child != NULL) {//해당 노드의 왼쪽이 비지 않았으면
        printf("(%d", crr->data);
        print_tree(treeroot, crr);//왼쪽노드의 자식 노드들 확인
        if (treechild->right_child != NULL) {//오른쪽도 안 비어있으면
            printf(",%d", treechild->right_child->data);
            print_tree(treeroot, treechild->right_child);//오른쪽노드의 자식노드들
            printf(")");
        }
        else {//오른쪽 빔
            printf(",)");
        }
    }
    else if (treechild->right_child != NULL) {//왼쪽 비고 오른쪽 차있으면
        printf("(,%d", treechild->right_child->data);
        print_tree(treeroot, treechild->right_child);//오른쪽의 자식들 확인
        printf(")");
    }
}

void heap_to_BST(H* heap, T* tree) {
    int crr = 2;
    printf("\n\n\t[START]\n");
    tree->root->data = heap->heap[1]->data;
    printf("\n\t[INPUT ROOT SUCCESS] %d", heap->heap[1]->data);

    tree->tree_size++;
    while (crr != heap->heap_size + 1) {
        NODE* putposition = find_tree_node(tree->root, heap->heap[crr]->data);
        if (putposition == NULL) {
            printf("\n\t[INPUT NODE  FAILED] %d (same data in tree)",heap->heap[crr]->data);
        }
        else {
            printf("\n\t[INPUT NODE SUCCESS] %d", heap->heap[crr]->data);
            insert_tree_node(tree, putposition, heap->heap[crr]->data);
        }crr++;
    }
}


int main() {
    
    //맥스힙 배열 생성
    H* heap=malloc(sizeof(H));
    create_max_heap(heap);

    //이진탐색트리 연결리스트 생성
    T* tree = malloc(sizeof(T));
    create_bst_tree(tree);

    //함수 실행 전 필요한 지정값
    int go = TRUE;
    printf("\n\tinsert example : +1");
    printf("\n\tif you want to change max heap to binary search tree\n\tplease input only T");
    while (go) {
        
        printf("\n\n\t");
        //heap print
        if (heap->heap_size == 0) printf("This heap is empty.\n\tPlease create root node first");
        else print_heap(heap);//root부터 출력
        
        char order[30] = { '0' };
        printf("\n\t>>> ");
        gets(order);

        //값 입력 전 필요한 지정값
        int data = 0;
        int isinheap = 0;
        int num = 0;
        for (int i = 0; i < strlen(order); i++) {
            //입력 값들 중에서 data 추출 변수 data에 저장
            if (num == 0 && (int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                while ((int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                    data = data * 10;
                    data += order[i] - 48;
                    i++;
                }
                i = -1;//for첨으로 돌아가기
                num++;
            }
            //명령어 실행
            switch (order[i]) {
            case '+'://
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (data != 0) {
                    NODE* node = malloc(sizeof(NODE));
                    node->data = data;
                    insert_heap_node(heap, node);
                }
                break;
            case'T':
                if (heap->heap_size != 0) {
                    heap_to_BST(heap, tree);
                    printf("\n\t");
                    print_tree(tree->root, tree->root);
                    printf("\n\n\t[FINISHED] Automatically return to HEAP\n");
                    clear(tree);
                }
                break;
            case'Q':
                printf("\n\t프로그램을 종료합니다.\n");
                go = FALSE;
                break;
            default:
                break;
            }//switch
        }//for
    }//while
    return 0;
}//main


