#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _NODE {
    int data;
    struct _NODE* left_child;
    struct _NODE* right_child;
}NODE;
typedef struct _tree {
    NODE* root;
    int cnt;
}T;



//functions 선언
void screen() {
    printf("\n\n\t");//get_parents 다시 만들기 
    printf("==============================================================");
    printf("\n\n                         AVL TREE FUNCTION\n\t");
    printf("\n\t  ****CAPITALIZE all the COMMANDSs\t");
    printf("\n\t  ****Do not use space bar\n\t");
    printf("\n\t  ****n=node data (input available only one integer type data");
    printf("\n\t--------------------------------------------------------------");
    printf("\n\t  first +n                   create tree, and insert root node");//
    printf("\n\t  +n                         insert node");//
    printf("\n\t  -n                         delete node ");//
    printf("\n\t  Fn                         search node ");//
    printf("\n\t  Gn                         get right child node");//
    printf("\n\t  Ln                         get left child node");//
    printf("\n\t  I                          sort (start min)");//
    printf("\n\t  R                          sort (start max)");//
    printf("\n\t  N                          get minimum");//
    printf("\n\t  X                          get maximum");//
    printf("\n\t  P                          print tree(default)");//
    printf("\n\t  A                          hide node data");//기능
    printf("\n\t  V                          reveal node data");//기능
    printf("\n\t  D                          degree of tree");//기능
    printf("\n\t  Dn                         degree of node");//기능
    printf("\n\t  T                          height of root");//
    printf("\n\t  Hn                         level of node (leaf is 0)");//
    printf("\n\t  Bn                         balancing factor");//
    printf("\n\t  #                          count all node");//
    printf("\n\t  C                          clear (delete all node)");//
    printf("\n\t--------------------------------------------------------------");
    printf("\n\t  Q                          quit (clear tree first)");//기능
    printf("\n\t==============================================================");
}

void create(T* tree) {

    NODE* new = (NODE*)malloc(sizeof(NODE));
    tree->root = new;
    tree->root->left_child = NULL;
    tree->root->right_child = NULL;
    tree->root->data = '\0';
    tree->cnt = 0;
}

void print(NODE* pnode, NODE* cnode);
void hide(NODE* pnode, NODE* cnode);

void insert(T* tree, NODE* putposition, int data);
void delete_node(T* tree, NODE* node);
void clear(T* tree);

int is_left_child(NODE* node);
int is_right_child(NODE* node);
NODE* get_left_child(NODE* node);
NODE* get_right_child(NODE* node);
NODE* get_parent(NODE* pnode, int data);

NODE* find(NODE* node, int data, char path[], int index);
NODE* search(NODE* pnode, char data);

void inorder(NODE* node);
void rightmost_inorder(NODE* node);

NODE* get_min(NODE* root);
NODE* get_max(NODE* root);

void count(T* tree);

int degree_of_node(NODE* parent);
NODE* degree_of_tree(NODE* p1, NODE* p2);



void rotate(T* tree);
NODE* rotateL(T* tree,NODE* new);
NODE* rotateR(T* tree,NODE* new);
NODE* rotateLR(T* tree,NODE* new);
NODE* rotateRL(T* tree,NODE* new);
int height(T* tree, NODE* node);
int balancing_factor(T* tree, NODE* node);

NODE* balancing(T* tree, NODE* p1, NODE* p2);


//main
int main() {
    //tree 생성
    T* tree = malloc(sizeof(T));

    screen();
    create(tree);
    int reveal = TRUE;
    int go = TRUE;
    while (go) {
        printf("\n\n\t");
        if (tree->cnt == 0) printf("This tree is empty.\n\tPlease create root node first");
        else if (reveal == TRUE) print(tree->root, tree->root);
        else hide(tree->root, tree->root);

        char order[30] = { '0' };
        printf("\n\t>>> ");
        gets(order);
        //
        int num = 0;
        int data = 0;
        char path[100] = { '\0' };
        int index = 0;
        NODE* new = malloc(sizeof(NODE));
        NODE* found = tree->root;
        for (int i = 0; i < strlen(order); i++) {
            //입력 값들 중에서 data 추출 변수 data에 저장
            if (num == 0 && (int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                while ((int)order[i] - 48 >= 0 && (int)order[i] - 48 <= 9) {
                    data = data * 10;
                    data += order[i] - 48;
                    i++;
                }
                i = -1;
                num++;
            }
            //명령어 실행
            switch (order[i]) {
            case '+'://
                if (data != 0) {
                    if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                    if (tree->cnt == 0) {
                        tree->root->data = data;
                        tree->cnt++;
                        break;
                    }
                    else {
                        new = find(tree->root, data, path, index);
                        if (new != NULL) {
                            insert(tree, new, data);
                            rotate(tree);
                        }
                        else {
                            printf("\n\t중복 값은 입력할 수 없습니다.");
                            //중복 값 루트 출력
                            printf("\n\tsearch path of same data %d : root ", data);
                            int j = 0;
                            while (path[j] != '\0') {
                                printf("-> %c ", path[j]);
                                j++;
                            }
                        }
                        break;
                    }
                    i++;
                }
                break;
            case '-'://
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                else if (data != 0) {
                    if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                    new = find(tree->root, data, path, index);
                    if (new == NULL) {//값 존재하면
                        found = search(tree->root, data);//해당 값 반환//값 존재하기 때문에 NULL 반환하는 일 없음 
                        delete_node(tree, found);//지우기
                        rotate(tree);
                    }
                    else {
                        printf("\n\tNot Found");//값 없음
                        printf("\n\tfailed search path of %d: root ", data);
                        int j = 0;
                        while (path[j] != '\0') {
                            printf("-> %c ", path[j]);
                            j++;
                        }
                        //값 없으면 탐색 실패한 루트라고 출력
                        printf("-> 탐색 실패 ");
                    }
                    break;
                }
                break;
            case'A':
                reveal = FALSE;
                break;
            case'V':
                reveal = TRUE;
                break;
            case'P'://print 자동임
                break;
            case'I':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                printf("\n\tsort (start min) : ");
                inorder(tree->root);
                break;
            case'R':
                if (tree->cnt == 0)
                    break;
                printf("\n\tsort (start max) : ");
                rightmost_inorder(tree->root);
                break;
            case'N':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                new = get_min(tree->root);
                printf("\n\tminimum data : %d", new->data);
                if (tree->cnt == 1) printf("(root node)");
                break;
            case'X':
                if (tree->cnt == 0)
                    break;
                new = get_max(tree->root);
                printf("\n\tmaximum data : %d", new->data);
                if (tree->cnt == 1) printf("(root node)");
                break;
            case'F':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (data != 0) {
                    new = find(tree->root, data, path, index);
                    //값 성공하면 탐색 성공한 루트라고 출력
                    if (new == NULL) printf("\n\tsuccess ");
                    //값 없으면 탐색 실패한 루트라고 출력
                    else printf("\n\tfail ");
                    printf("search path of %d : root ", data);
                    int j = 0;
                    while (path[j] != '\0') {
                        printf("-> %c ", path[j]);
                        j++;
                    }
                }
                break;
            case'C':
                clear(tree);
                break;
            case'T':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                printf("\n\theight of tree (root : %d) : %d", tree->root->data, height(tree, tree->root));
                break;
            case'H'://
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (order[i + 1] == NULL) {
                    break;
                }
                else if (data != 0) {
                    new = find(tree->root, data, path, index);
                    if (new == NULL) {//값 존재하면
                        found = search(tree->root, data);//해당 값 반환//값 존재하기 때문에 NULL 반환하는 일 없음 
                        printf("\n\theight of node %d : %d", found->data, height(tree, found));
                    }
                    else printf("\n\tNot Found");//값 없으면
                }
                break;
            case'B'://
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (order[i + 1] == NULL) {
                    break;
                }
                else if (data != 0) {
                    new = find(tree->root, data, path, index);
                    if (new == NULL) {//값 존재하면
                        found = search(tree->root, data);//해당 값 반환//값 존재하기 때문에 NULL 반환하는 일 없음 
                        printf("\n\tbalance factor of node %d : %d", found->data, balancing_factor(tree, found));
                    }
                    else printf("\n\tNot Found");//값 없으면
                }
                break;
            case'D'://
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (order[i + 1] == NULL) {
                    new = degree_of_tree(tree->root, tree->root);
                    printf("\n\tdegree of tree : %d", degree_of_node(new));
                }
                else if (data != 0) {
                    new = find(tree->root, data, path, index);
                    if (new == NULL) {//값 존재하면
                        found = search(tree->root, data);//해당 값 반환//값 존재하기 때문에 NULL 반환하는 일 없음 
                        printf("\n\tdegree of node %d : %d", found->data, degree_of_node(found));
                    }
                    else printf("\n\tNot Found");//값 없으면
                }
                break;
            case 'G':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (data != 0) {
                    new = find(tree->root, data, path, index);
                    //값 없으면
                    if (new != NULL) {
                        printf("\n\tNot Found");
                        break;
                    }
                    else {//값 있으면
                        found = search(tree->root, data);
                        NODE* right = get_right_child(found);
                        if (right != NULL) printf("\n\tright child data : %d", right->data);
                        else printf("\n\tNot Found");
                    }
                }
                break;
            case 'L':
                if (tree->cnt == 0) {
                    printf("\n\tTree is empty");
                    break;
                }
                if (data != 0) {
                    new = find(tree->root, data, path, index);
                    //값 없으면
                    if (new != NULL) {
                        printf("\n\tNot Found");
                        break;
                    }
                    //값 있으면
                    else {
                        found = search(tree->root, data);
                        NODE* left = get_left_child(found);
                        if (left != NULL) printf("\n\tright child data : %d", left->data);
                        else printf("\n\tNot Found");
                    }
                }
                break;
            case'#':
                count(tree);
                break;
            case'Q':
                printf("\n\ttree를 지우고 프로그램을 종료합니다.\n");
                clear(tree);
                printf("\n\n\t삭제할 tree가 존재하지 않으므로 프로그램을 종료합니다.\n\n\t\t\t\t\t\t\t\t-end-\n\n\n\n");
                go = FALSE;
            default:
                break;
            }//switch
        }//for
    }//while
    return 0;
}//main



//function 구현
void print(NODE* pnode, NODE* cnode)
{
    NODE* crr = cnode->left_child;
    if (pnode == cnode) printf("%d", pnode->data);//root 출력

    if (cnode->left_child != NULL) {//해당 노드의 왼쪽이 비지 않았으면
        printf("(%d", crr->data);
        print(pnode, crr);//왼쪽노드의 자식 노드들 확인
        if (cnode->right_child != NULL) {//오른쪽도 안 비어있으면
            printf(",%d", cnode->right_child->data);
            print(pnode, cnode->right_child);//오른쪽노드의 자식노드들
            printf(")");
        }
        else {//오른쪽 빔
            printf(",)");
        }
    }
    else if (cnode->right_child != NULL) {//왼쪽 비고 오른쪽 차있으면
        printf("(,%d", cnode->right_child->data);
        print(pnode, cnode->right_child);//오른쪽의 자식들 확인
        printf(")");
    }

}
void hide(NODE* pnode, NODE* cnode) {
    NODE* crr = cnode->left_child;
    if (pnode == cnode) printf("O");//root 출력

    if (cnode->left_child != NULL) {//해당 노드의 왼쪽이 비지 않았으면
        printf("(O,");
        //printf("\n(%d 's left child %d , ", cnode->data, cnode->left_child->data);
        hide(pnode, crr);//왼쪽노드의 자식 노드들 확인
        if (cnode->right_child != NULL) {//오른쪽도 안 비어있으면
            printf("O");
            //printf("\n %d 's right child %d", cnode->data, cnode->right_child->data);
            hide(pnode, cnode->right_child);//오른쪽노드의 자식노드들
            printf(")");
        }
        else {//오른쪽 빔
            printf(")");
        }
    }
    else if (cnode->right_child != NULL) {//왼쪽 비고 오른쪽 차있으면
        printf("(O");
        //printf("\n( ,%d 's right child %d", cnode->data, cnode->right_child->data);
        hide(pnode, cnode->right_child);//오른쪽의 자식들 확인
        printf(")");
    }
}

void count(T* tree) {
    printf("\n\tall node count : %d", tree->cnt);
}//

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

NODE* find(NODE* node, int data, char path[], int index) {//탐색 성공시 return null //실패 시 실패한 위치 반환

    if (node == NULL) return node;//있어야하나 ? 나중에 확인 ㄱ ㄱ 

    if (data == node->data) return NULL;
    //같으면

    NODE* leftchild = get_left_child(node);
    NODE* rightchild = get_right_child(node);
    //자식 없으면 해당 노드 반환
    if (leftchild == NULL && rightchild == NULL) return node;


    if (data < node->data) {//왼쪽으로
        path[index] = 'L';
        path[index + 1] = '\0';
        index++;
        if (leftchild != NULL) {//왼쪽값이 차있으면
            if (leftchild->data == data)  return NULL;//왼쪽 값 같으면
            else if (data < leftchild->data) {//왼쪽의 왼쪽ㄱㄱ
                if (leftchild->left_child != NULL) {//차있으면
                    path[index] = 'L';
                    path[index + 1] = '\0';
                    index++;
                    NODE* baby = find(leftchild->left_child, data, path, index);
                    return baby;
                }
                else return leftchild;//비어있으면
            }
            else if (data > leftchild->data) {//왼쪽의 오른쪽으로
                if (leftchild->right_child != NULL) {
                    path[index] = 'R';
                    path[index + 1] = '\0';
                    index++;
                    NODE* baby = find(leftchild->right_child, data, path, index);
                    return baby;
                }
                else return leftchild;
            }
            else return leftchild;
        }
        else return node;//왼쪽 비어있으면
    }//왼쪽
    else if (data > node->data) {//오른쪽으로
        path[index] = 'R';
        path[index + 1] = '\0';
        index++;
        if (rightchild != NULL) {//오른쪽 값 차있으면
            if (rightchild->data == data) return NULL;
            else if (data < rightchild->data) {//오른쪽의 왼쪽 값으로
                if (rightchild->left_child != NULL) {
                    path[index] = 'L';
                    path[index + 1] = '\0';
                    index++;
                    NODE* baby = find(rightchild->left_child, data, path, index);
                    return baby;
                }
                else return rightchild;
            }
            else if (data > rightchild->data) {//오른쪽의 오른쪽으로
                if (rightchild->right_child != NULL) {
                    path[index] = 'R';
                    path[index + 1] = '\0';
                    index++;
                    NODE* baby = find(rightchild->right_child, data, path, index);
                    return baby;
                }
                else return rightchild;
            }
            else return rightchild;
        }
        else return node;//오른쪽 빔
    }//오른쪽
    else return node;
} //child 둘 다 비교해서 같으면 반환 //작으면 배열에 L넣고 왼쪽 재귀함수 호출 //크면 배열에 R넣고 오른쪽 재귀함수 호출//실패하면 실패한 위치도 프린트 할 까 ? 나중에 수정 ㄱ ㄱ
NODE* search(NODE* pnode, char data) {
    if (pnode == NULL)return NULL;
    if (pnode->data == data) return pnode;
    NODE* new = search(pnode->left_child, data);
    if (new != NULL) return new;
    new = search(pnode->right_child, data);
    if (new != NULL) return new;
    return NULL;
}//find함수 사용한 후 pnode값 존재하는 경우에만 적용// NULL 반환하는 일 x //노드 뮤조건 반환함

void inorder(NODE* node) {
    NODE* leftchild = get_left_child(node);
    if (leftchild != NULL) {
        inorder(leftchild);
    }
    printf("%d ", node->data);

    NODE* rightchild = get_right_child(node);
    if (rightchild != NULL) {
        inorder(rightchild);
    }
}//left차있으면 재귀함수 호출 //left 비면 루트 쓰고 //right 차있으면 재귀함수 호출//
void rightmost_inorder(NODE* node) {
    NODE* rightchild = get_right_child(node);
    if (rightchild != NULL) {
        rightmost_inorder(rightchild);
    }

    printf("%d ", node->data);

    NODE* leftchild = get_left_child(node);
    if (leftchild != NULL) {
        rightmost_inorder(leftchild);
    }
}//inorder반대로

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

int degree_of_node(NODE* parent) {

    if (is_left_child(parent) == FALSE && is_right_child(parent) == FALSE) return 0;
    else if (is_left_child(parent) == FALSE || is_right_child(parent) == FALSE)return 1;
    else return 2;
}
NODE* degree_of_tree(NODE* p1, NODE* p2) {

    if (p1 == NULL) return NULL;

    NODE* deeper = degree_of_node(p1) > degree_of_node(p2) ? p1 : p2;
    //p1, p2 레벨 비교해 더 높은 자식노드 개수를 가진 노드를 deeper에 저장 

    deeper = degree_of_tree(p1->left_child, deeper) ? degree_of_tree(p1->left_child, deeper) : deeper;
    //p1의 leftchild와 new에 대해 degreeoftree함수 적용
        //p1의 왼쪽이 NULL이면 deepter는 그대로 유지
        //p1의 왼쪽 값이 존재하면 levelofnode 계산해서 상위 레벨가진 노드 반환

    deeper = degree_of_tree(p1->right_child, deeper) ? degree_of_tree(p1->right_child, deeper) : deeper;
    //p1의 오른쪽에 대해서도 똑같이 적용

    return deeper;//degree값 가장 큰 node반환

}

void insert(T* tree, NODE* putposition, int data) {

    NODE* newnode = malloc(sizeof(NODE));
    if (data < putposition->data)
        putposition->left_child = newnode;
    else if (data > putposition->data)
        putposition->right_child = newnode;
    else { printf("값 같아서 못 들어감"); return; }
    newnode->left_child = NULL;
    newnode->right_child = NULL;
    newnode->data = data;
    tree->cnt++;
}

void delete_node(T* tree, NODE* node) {
    if (node == NULL)return;
    int n = degree_of_node(node);
    NODE* rmv = node;
    if (node == tree->root) {//지우려 한 게 root노드 면
        if (n == 0) tree->root->data = '\0';

        else if (n == 1) {
            tree->root = tree->root->left_child != NULL ? tree->root->left_child : tree->root->right_child;//연결
            free(rmv);
        }
        else {//degree(node)==2
            NODE* max = get_max(tree->root->left_child);//왼쪽 서브노트의 가장 오른쪽 노드
            NODE* maxparent = get_parent(tree->root, max->data);
            if (max == tree->root->left_child) {//왼쪽 서브노트의 최댓값이 왼쪽 서브노트의 루트면  
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
            if (max == node->left_child) {//왼쪽 서브노트의 최댓값이 왼쪽 서브노트의 루트면  
                if (node == get_left_child(parent)) parent->left_child = node->left_child;//왼쪽자식일때
                else parent->right_child = node->left_child;//오른쪽 자식일때
                max->right_child = node->right_child;
                node->left_child = NULL;
                node->right_child = NULL;
                free(rmv);
            }
            else {//왼쪽 서브노트의 최댓값이 루트 아닌 다음 값들이면
                if (max->left_child != NULL) {
                    NODE* tmp = max;
                    while (tmp->left_child != NULL) {
                        tmp = tmp->left_child;
                    }
                    tmp->left_child = node->left_child;
                }
                else max->left_child = node->left_child;
                max->right_child = node->right_child;
                if (node == get_left_child(parent)) parent->left_child = max;
                else parent->right_child = max;;
                maxparent->right_child = NULL;
                free(rmv);
            }
        }
    }
    tree->cnt--;
}//
void clear(T* tree) {
    while (tree->cnt != 0) {
        delete_node(tree, tree->root);
    }

}//root 부터 tree->cnt 개수만큼 반복 삭제

void rotate(T* tree) {//rotate하는지 확인

    NODE* balancing_node = balancing(tree, tree->root, tree->root);//balacing 해야하는 최하단 노드 반환
    //printf("\n\tbalancing node : %d", balancing_node->data);
    int nbalancing_factor = balancing_factor(tree, balancing_node);
    //printf("\n\tbalancing factor : %d", nbalancing_factor);

    switch (nbalancing_factor)
    {
    case 0:
    case 1:
    case -1:
        printf("\n\tNot Rotated");
        break;
    //필요 없으면 끝
    case 2://right 
        printf("\n\n\t");
        print(tree->root, tree->root);
        if (balancing_node->left_child != NULL && balancing_factor(tree, balancing_node->left_child) > 0) {
            NODE* new = rotateL(tree, balancing_node);
            printf("\n\n\tLL Rotated(%d)", balancing_node->data);
        }
        else {
            NODE* new = rotateLR(tree,balancing_node);
            printf("\n\n\tLR Rotated(%d)", balancing_node->data);
        }
        break;
    case -2://left rotate
        printf("\n\n\t");
        print(tree->root, tree->root);
        if (balancing_node->right_child != NULL && balancing_factor(tree, balancing_node->right_child) < 0) {
            NODE* new = rotateR(tree,balancing_node);
            printf("\n\n\tRR Rotated(%d)",balancing_node->data);
        }
        else {
            NODE* new = rotateRL(tree,balancing_node);
            printf("\n\n\tRL Rotated(%d)", balancing_node->data);
        }
        break;
    default:
        break;
    }
}
NODE* rotateL(T* tree, NODE* new)
{
    NODE* parent = get_parent(tree->root, new->data);
    //printf("\nrotate L(%d)", new->data);
    if (parent == NULL) {
        tree->root = new->left_child;
        tree->root->left_child = new->left_child->left_child;
        NODE* temp = NULL;
        if (new->left_child->right_child != NULL) {
            temp = new->left_child->right_child;
        }
        tree->root->right_child = new;
        new->left_child = temp;
        return tree->root;
    }
    if (new == get_left_child(parent)) {
        parent->left_child = new->left_child;
        NODE* temp = NULL;
        if (new->left_child->right_child != NULL) {
            temp = new->left_child->right_child;
        }
        new->left_child->right_child = new;
        new->left_child = temp;
        return parent;
    }
    else if (new == get_right_child(parent)) {
        parent->right_child = new->left_child;
        NODE* temp = NULL;
        if (new->left_child->right_child != NULL) {
            temp = new->left_child->right_child;
        }
        new->left_child->right_child = new;
        new->left_child = temp;
        return parent;
    }
}
NODE* rotateR(T* tree, NODE* new)
{
    NODE* parent = get_parent(tree->root, new->data);
    //printf("\nrotate R(%d)", new->data);
    if (parent == NULL) {
        tree->root = new->right_child;
        NODE* temp = NULL;
        if (new->right_child->left_child != NULL) {
            temp = new->right_child->left_child;
        }
        tree->root->left_child = new;
        new->right_child = temp;
        return tree->root;
    }
    else if (new == get_left_child(parent)) {
        parent->left_child = new->right_child;
        NODE* temp = NULL;
        if (new->right_child->left_child != NULL) {
            temp = new->right_child->left_child;
        }
        new->right_child->left_child = new;
        new->right_child = temp;
        return parent;
    }
    else if (new == get_right_child(parent)) {
        parent->right_child = new->right_child;
        NODE* temp = NULL;
        if (new->right_child->left_child != NULL) {
            temp = new->right_child->left_child;
        }
        new->right_child->left_child = new;
        new->right_child = temp;
        return parent;
    }
    
}
NODE* rotateLR(T* tree, NODE* new)
{   
    new = rotateR(tree, new->left_child);
    //printf("\nrotate LR(%d)", new->data);
    return rotateL(tree, new);
}
NODE* rotateRL(T* tree, NODE* new)
{
    new = rotateL(tree, new->right_child);
    
    //printf("\nrotate RL(%d)", parent->data);
    return rotateR(tree, new);
}
/*
int height(T* tree, NODE* node) {//avl tree 에서의 height 계산
    if (tree->cnt == 0)return -1;//빈 tree면 return -1
    if (node == NULL) return 0;//빈 자리면 return -1
    int height_of_tree = level_of_node(tree, level_of_tree(tree, tree->root, tree->root));//tree level
    int level_of_tree = level_of_node(tree, node);//node level
    return abs(height_of_tree - level_of_tree);
}*/

int height(T* tree, NODE* root) {
    if (root == NULL)
        return -1;
    int left = height(tree, root->left_child);
    int right = height(tree, root->right_child);
    if (left > right)
        return left+1;
    else
        return right+1;
}
int balancing_factor(T*tree, NODE* node) {//balacing factor 반환
    /*if (node == NULL) {
        printf("node==null"); return ;
    }*/
    int left_height = height(tree, node->left_child);
    int right_height = height(tree, node->right_child);
    //printf("\nbalancing factor of %d >> (%d) - (%d) = %d", node->data, left_height, right_height, left_height - right_height);
    return left_height - right_height;
}

NODE* balancing(T* tree, NODE* p1, NODE* p2) { // balacing 해야하는 노드 반환

    if (p1== NULL) return NULL;
    NODE* deeper;
    if (abs(balancing_factor(tree, p1)) > abs(balancing_factor(tree, p2))) {
        deeper = p1;
    }
    else if (abs(balancing_factor(tree, p1)) < abs(balancing_factor(tree, p2))) {
        deeper = p2;
    }else {
        if (height(tree, p1) > height(tree, p2)) {
            deeper = p2;
        }
        else deeper = p1;
    }
 
    deeper = balancing(tree, p1->left_child, deeper) ? balancing(tree, p1->left_child, deeper) : deeper;
    //p1의 leftchild와 new에 대해 balancing함수 적용
    //p1의 왼쪽이 NULL이면 deepter는 그대로 유지
    //p1의 왼쪽 값이 존재하면 balacing factor 계산해서 노드 반환
    deeper = balancing(tree, p1->right_child, deeper) ? balancing(tree, p1->right_child, deeper) : deeper;
    //p1의 오른쪽에 대해서도 똑같이 적용
    return deeper;//balacing factor 가장 큰 node반환
}

