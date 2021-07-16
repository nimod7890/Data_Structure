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
NODE* get_parent(NODE* root, int data) {//�� ó�� ���� tree->root
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
}//isleftchild ���̸� �� ��ȯ
NODE* get_right_child(NODE* node) {
    if (node == NULL)return NULL;
    int n = is_right_child(node);
    if (n == TRUE) return node->right_child;
    else return NULL;
}//isrightchild ���̸� �� ��ȯ �����̸� NULL��ȯ
NODE* get_min(NODE* root) {
    if (root == NULL)return NULL;
    while (root->left_child != NULL) {
        root = root->left_child;
    }
    return root;
}//inorderù��° ��
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
    if (node == tree->root) {//����� �� �� root��� ��
        if (n == 0) {
            tree->root->data = '\0';
        }
        else if (n == 1) {
            tree->root = tree->root->left_child != NULL ? tree->root->left_child : tree->root->right_child;//����
            free(rmv);
        }
        else {//degree(node)==2
            NODE* max = get_max(tree->root->left_child);//���� �����Ʈ�� ���� ������ ���
            NODE* maxparent = get_parent(tree->root, max->data);
            if (maxparent == tree->root) {//���� �����Ʈ�� �ִ��� ���� �����Ʈ�� ��Ʈ��  
                max->right_child = tree->root->right_child;
                tree->root->left_child = NULL;
                tree->root->right_child = NULL;
                tree->root = max;//
                free(rmv);
            }
            else {//���� �����Ʈ�� �ִ��� ��Ʈ �ƴ� ���� �����̸�
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
                maxparent->right_child = NULL;//max���κ� ���� ����
                tree->root = max;
                free(rmv);
            }
        }
    }
    else {//root node �ƴϸ�
        NODE* parent = get_parent(tree->root, node->data);//parent���ϼ�
        if (n == 0) {
            if (node == get_left_child(parent)) parent->left_child = NULL;//�����ڽ��϶�
            else parent->right_child = NULL;//������ �ڽ��϶�
            free(rmv);
        }
        else if (n == 1) {
            if (node == get_left_child(parent)) {//���� ��尡 ���� �ڽ��̸�
                if (node->left_child != NULL) {//���� ����� �ڽ��� ���ʿ� ������
                    parent->left_child = node->left_child;
                }
                else {//���� ����� �ڽ��� �����ʿ� ������
                    parent->left_child = node->right_child;
                }
                free(rmv);
            }
            else {//���� ��尡 ������ �ڽ��̸�
                if (node->left_child != NULL) {//���� ����� �ڽ��� ���ʿ� ������
                    parent->right_child = node->left_child;
                }
                else {//���� ����� �ڽ��� �����ʿ� ������
                    parent->right_child = node->right_child;
                }
                free(rmv);
            }
        }
        else {//degree(node)==2
            NODE* max = get_max(node->left_child);//���� ����� ���� �����Ʈ�� ���� ������ ���
            //max->right_child = node->right_child;
            NODE* maxparent = get_parent(tree->root, max->data);
            if (maxparent == node) {//���� �����Ʈ�� �ִ��� ���� �����Ʈ�� ��Ʈ��  
                parent->left_child = node->left_child;//parent���� ��� ����
                max->right_child = node->right_child;
                node->left_child = NULL;
                node->right_child = NULL;
                free(rmv);
            }
            else {//���� �����Ʈ�� �ִ��� ��Ʈ �ƴ� ���� �����̸�
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

NODE* find_tree_node(NODE* node, int data) {//Ž�� ������ return null //���� �� ������ ��ġ ��ȯ

    if (node == NULL) return node;//�־���ϳ� ? ���߿� Ȯ�� �� �� 
    if (data == node->data) return NULL;
    //������

    NODE* leftchild = get_left_child(node);
    NODE* rightchild = get_right_child(node);
    //�ڽ� ������ �ش� ��� ��ȯ
    if (leftchild == NULL && rightchild == NULL) return node;

    if (data < node->data) {//��������
        
        if (leftchild != NULL) {//���ʰ��� ��������
            if (leftchild->data == data)  return NULL;//���� �� ������
            else if (data < leftchild->data) {//������ ���ʤ���
                if (leftchild->left_child != NULL) {//��������
                    NODE* baby = find_tree_node(leftchild->left_child, data);
                    return baby;
                }
                else return leftchild;//���������
            }
            else if (data > leftchild->data) {//������ ����������
                if (leftchild->right_child != NULL) {

                    NODE* baby = find_tree_node(leftchild->right_child, data);
                    return baby;
                }
                else return leftchild;
            }
            else return leftchild;
        }
        else return node;//���� ���������
    }//����
    else if (data > node->data) {//����������

        if (rightchild != NULL) {//������ �� ��������
            if (rightchild->data == data) return NULL;
            else if (data < rightchild->data) {//�������� ���� ������
                if (rightchild->left_child != NULL) {
                    NODE* baby = find_tree_node(rightchild->left_child, data);
                    return baby;
                }
                else return rightchild;
            }
            else if (data > rightchild->data) {//�������� ����������
                if (rightchild->right_child != NULL) {
                    NODE* baby = find_tree_node(rightchild->right_child, data);
                    return baby;
                }
                else return rightchild;
            }
            else return rightchild;
        }
        else return node;//������ ��
    }//������
    else return node;
}

void insert_heap_node(H* heap,NODE* data) {
    int i;
    i = ++(heap->heap_size);
    //printf("\n\tinserting : %d", data->data);//Ȯ�� �۾�
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
        printf("\n\tMAX HEAP changed to BST\n\t>>> %d", treeroot->data);//root ���
    }
    if (treechild->left_child != NULL) {//�ش� ����� ������ ���� �ʾ�����
        printf("(%d", crr->data);
        print_tree(treeroot, crr);//���ʳ���� �ڽ� ���� Ȯ��
        if (treechild->right_child != NULL) {//�����ʵ� �� ���������
            printf(",%d", treechild->right_child->data);
            print_tree(treeroot, treechild->right_child);//�����ʳ���� �ڽĳ���
            printf(")");
        }
        else {//������ ��
            printf(",)");
        }
    }
    else if (treechild->right_child != NULL) {//���� ��� ������ ��������
        printf("(,%d", treechild->right_child->data);
        print_tree(treeroot, treechild->right_child);//�������� �ڽĵ� Ȯ��
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
    
    //�ƽ��� �迭 ����
    H* heap=malloc(sizeof(H));
    create_max_heap(heap);

    //����Ž��Ʈ�� ���Ḯ��Ʈ ����
    T* tree = malloc(sizeof(T));
    create_bst_tree(tree);

    //�Լ� ���� �� �ʿ��� ������
    int go = TRUE;
    printf("\n\tinsert example : +1");
    printf("\n\tif you want to change max heap to binary search tree\n\tplease input only T");
    while (go) {
        
        printf("\n\n\t");
        //heap print
        if (heap->heap_size == 0) printf("This heap is empty.\n\tPlease create root node first");
        else print_heap(heap);//root���� ���
        
        char order[30] = { '0' };
        printf("\n\t>>> ");
        gets(order);

        //�� �Է� �� �ʿ��� ������
        int data = 0;
        int isinheap = 0;
        int num = 0;
        for (int i = 0; i < strlen(order); i++) {
            //�Է� ���� �߿��� data ���� ���� data�� ����
            if (num == 0 && (int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                while ((int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                    data = data * 10;
                    data += order[i] - 48;
                    i++;
                }
                i = -1;//for÷���� ���ư���
                num++;
            }
            //��ɾ� ����
            switch (order[i]) {
            case '+'://
                if (order[i + 1] == '\0') break; //�ڵ� ��Ÿ ���� ���
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
                printf("\n\t���α׷��� �����մϴ�.\n");
                go = FALSE;
                break;
            default:
                break;
            }//switch
        }//for
    }//while
    return 0;
}//main


