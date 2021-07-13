#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define availabletreenum 52

typedef struct _NODE {
    char data;
    struct _NODE* left_child;
    struct _NODE* right_sibling;
}NODE;
typedef struct _tree {
    NODE* root;
    int cnt;
}T;

void create(T* tree, char data);

NODE* search(NODE* pnode, char data);

void print(NODE* pnode, NODE* cnode);
void printbn(NODE* pnode, NODE* cnode);

void insertchild(T* tree, NODE* pnode, char cnode, int isbinarytree);
void insertsibling(T* tree, NODE* sibling, char data, int isbinarytree);

NODE* get_parent(NODE* pnode, char data);
NODE* get_parentbn(NODE* pnode, char data);

void get_sibling(T* tree, char data);
void get_siblingbn(T* tree, char crr);

void get_child(NODE* parent);
void get_childbn(NODE* parent);

void get_descendants(NODE* pnode, NODE* cnode);
void get_descendantsbn(NODE* pnode, NODE* cnode);

void get_ancestors(T* tree, NODE* cnode, int isbinarytree);

int cnodenum(NODE* parent);
int cnodenumbn(NODE* parent);

void count(T* tree,int crr);

void degreeofnode(NODE* parent);
void degreeofnodebn(NODE* parent);

T* copy(T* tree, NODE* root);
T* join(T* newtree, T* tree1, T* tree2);
T* joinbn(T* newtree, T* tree1, T* tree2);

int delete_node(T* tree, NODE* node);
int delete_nodebn(T* tree, NODE* node);

int clear(T* tree, NODE* pnode);
int clearbn(T* tree, NODE* pnode);

NODE* degreeoftree(NODE* p1, NODE* p2);
NODE* degreeoftreebn(NODE* p1, NODE* p2);

int levelofnode(T* tree, NODE* cnode, int isbinarytree);
NODE* leveloftree(T* tree, NODE* p1, NODE* p2, int isbinarytree);


void screen(int isbinarytree) {
    system("cls");
    printf("\n\n\t");
    printf("==================================================================");
    if (isbinarytree == TRUE) printf("\n\n                          BINARY TREE FUNCTION\n\t");
    else printf("\n\n                          TREE FUNCTION\n\t");
    printf("\n\t  ****CAPITALIZE all the COMMANDSs\t");
    printf("\n\t  ****Do not use space bar\n\t");
    printf("\n\t  ****p=parent  /  s=sibling  /  n=node  /  r=root");
    printf("\n\t------------------------------------------------------------------");
    printf("\n\t  +^n                        create root node");
    printf("\n\t  +p(n1 n2..)                insert pnode's child node(s)");
    printf("\n\t  =+s(n1 n2..)               insert snode's sibling node(s)");
    printf("\n\t  -n                         delete node if degree of n == 0");
    printf("\n\t  P(n)                       get parent node");
    printf("\n\t  C(n)                       get child node(s)");
    printf("\n\t  S(n)                       get sibling node(s)");
    printf("\n\t  A(n)                       get ancestors node(s)");
    printf("\n\t  D(n)                       get descendants node(s)");
    printf("\n\t  G(n)                       degree of node");
    printf("\n\t  G                          degree of tree");
    printf("\n\t  L(n)                       level of node(root=0)");
    printf("\n\t  L                          level of tree(start with 0)");
    printf("\n\t  #                          count all node of current tree");
    printf("\n\t  #r                         count all node of tree r");
    printf("\n\t  @                          count all tree");
    printf("\n\t  J(rab)                     join tree a + b (new root r)");
    printf("\n\t  K                          clear(delete tree and *go before tree)");
    printf("\n\t------------------------------------------------------------------");
    printf("\n\t  Q                          quit");
    printf("\n\t==================================================================");
}

int main() {
    T* roots[availabletreenum];
    for (int i = 0; i < availabletreenum; i++) {
        roots[i] = malloc(sizeof(T));
    }

    int len = 0;
    int crr = -1;
    //트리 종류 선택
    int isbinarytree;
    printf("\n\n\t일반 트리 (0) / 이진 트리 (1)\n\t>>> ");
    scanf_s("%d", &isbinarytree);
    rewind(stdin);
    if (isbinarytree == TRUE)
        printf("\n\tBINARY TREE를 선택하셨습니다.\n\n\t");
    else if (isbinarytree == FALSE)
        printf("\n\t일반 TREE를 선택하셨습니다.\n\n\t");
    else
        printf("\n\t잘못 입력하셨습니다.\n\t자동으로 일반 TREE가 선택됩니다.\n\n\t");

    //main screen print
    system("pause");
    screen(isbinarytree);



    int go = TRUE;
    while (go) {
        printf("\n\t");
        if (crr == -1) printf("This tree is empty.\n\tPlease create root node first");
        else if (isbinarytree == TRUE) printbn(roots[crr]->root, roots[crr]->root);//
        else print(roots[crr]->root, roots[crr]->root);//
        char order[30] = { 0 };
        printf("\n\t>>> ");
        gets(order);
        
        for (int i = 0; i < strlen(order); i++) {
            if (order[0] == 'K') {//
            if (crr == -1) {
                printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                break;
            }
            if (order[1] == '\0') {
                if (roots[crr]->cnt == 0) {
                    printf("\n\tThis tree is already empty\n");
                    break;
                }
                if (isbinarytree == TRUE) { int n = clearbn(roots[crr], roots[crr]->root); }
                else { int n = clear(roots[crr], roots[crr]->root); }
                len--;
                crr--;

            }
            else break;//이후에 다른 입력값 존재 시 clear작동x
            break;
        }switch (order[i]) {
            case '+'://
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '^') {
                    if (order[i + 2] == '\0')break;
                    //전에 정의한 root node인지 확인
                    int crnt = -1;
                    for (int j = 0; j < len; j++) {
                        if (roots[j]->root->data == order[i + 2]) crnt = j;
                    }
                    if (crnt != -1) {
                        crr = crnt;//이미 정의한 root node 면 현재 tree 바꾸기
                        printf("\n\t{%c}는 이미 정의한 tree의 root node 이므로\n\t해당 tree 입력창으로 이동합니다.\n", order[i + 2]);
                    }
                    else {// 새로 정의한 root node면 새 tree 생성
                        crr = len;
                        create(roots[crr], order[i + 2]);
                        len++;
                    }
                    i = i + 2;
                }
                if (order[i + 2] == '\0')break;
                if (order[i + 2] == '(') {
                    if (crr == -1)printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    NODE* find = search(roots[crr]->root, order[i + 1]);
                    if (find == NULL) {//해당 부모노드 미존재시
                        printf("\n\t%c is not in tree\n", order[i + 1]);
                        break;
                    }i += 3;
                    while (order[i] != ')') {//자식 노드 추가
                        insertchild(roots[crr], find, order[i], isbinarytree);
                        i++;
                    }
                    
                }
                break;
            case'='://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break;
                if (order[i + 1] == '+') {
                    if (order[i + 2] == '\0') break;
                    if (order[i + 3] == '\0') break;
                    if (order[i + 3] == '(') {
                        NODE* find = search(roots[crr]->root, order[i + 2]);
                        if (find == NULL) {//해당 부모노드 미존재시
                            printf("\n\t%c is not in tree\n", order[i + 2]);
                            break;
                        }i = i + 4;
                        while (order[i] != ')') {//형제 노드 추가
                            insertsibling(roots[crr], find, order[i], isbinarytree);
                            i++;
                        }
                    }
                }
                break;
            case'-'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; 
                NODE* find = search(roots[crr]->root, order[i + 1]);
                if (find == NULL) {//해당 노드 미존재시
                    printf("\n\t{%c} is not in tree\n", order[i + 1]);
                }
                else {
                    int k = 0;
                    if (isbinarytree == TRUE)
                        k = delete_nodebn(roots[crr], find);
                    else  k = delete_node(roots[crr], find);
                    if (k == FALSE) {
                        printf("\n\t해당 노드 {%c}는 지울 수 없습니다.\n", order[i + 1]);
                    }
                    if (k == -1) {
                        printf("\n\troot node가 지워졌으니 이전 트리로 돌아갑니다.\n\t이전 tree가 없는 경우 새 tree를 생성합니다.\n");
                        len--;
                        crr--;
                    }
                }i++;
                break;
            case 'P'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 3] == ')') {//부모노드 찾기
                        NODE* parent;
                        if (isbinarytree == TRUE)
                            parent = get_parentbn(roots[crr]->root, find->data);
                        else parent = get_parent(roots[crr]->root, find->data);//
                        printf("\n\t{%c}'s parent node : %c\n", find->data, parent->data);
                    }
                } i += 3;
                break;
            case 'S'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 3] == '\0') break; //자동 오타 수정 기능
                    if (order[i + 3] == ')') {//형제노드 찾기
                        if (isbinarytree == TRUE)
                            get_siblingbn(roots[crr], find->data);//
                        else get_sibling(roots[crr], find->data);//

                    }
                } i += 3;
                break;
            case 'G'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') {
                    if (isbinarytree == TRUE) {
                        NODE* new = degreeoftreebn(roots[crr]->root, roots[crr]->root);
                        printf("\n\tdegree of tree : %d\n", cnodenumbn(new));
                    }
                    else {
                        NODE* new = degreeoftree(roots[crr]->root, roots[crr]->root);
                        printf("\n\tdegree of tree : %d\n", cnodenum(new));
                    }
                    break;
                }
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 1] == '\0') break;
                    if (order[i + 3] == ')') {//형제노드 찾기
                        if (isbinarytree == TRUE)
                            degreeofnodebn(find);
                        else degreeofnode(find);
                        i = i + 3;
                    }
                }
                break;
            case 'C'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 3] == ')') {//자식노드 찾기
                        if (isbinarytree == TRUE)
                            get_childbn(find);
                        else get_child(find);//
                        i = i + 3;
                    }
                }
                break;
            case 'A'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 3] == ')') {//부모노드들 찾기
                        get_ancestors(roots[crr], find, isbinarytree);//
                        i = i + 3;
                    }
                }
                break;
            case 'D'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    NODE* find = search(roots[crr]->root, order[i + 2]);
                    if (find == NULL) {//해당 노드 미존재시
                        printf("\n\t{%c} is not in tree\n", order[i + 2]);
                        break;
                    }
                    if (order[i + 3] == ')') {//자식노드들 찾기
                        if (isbinarytree == TRUE)
                            get_descendantsbn(find, find);
                        else get_descendants(find, find);
                        i = i + 3;
                    }
                }
                break;
            case'L':
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') {
                    NODE* new = leveloftree(roots[crr], roots[crr]->root, roots[crr]->root, isbinarytree);
                    printf("\n\tlevel of tree : %d\n", levelofnode(roots[crr], new, isbinarytree));
                    break;
                }
                else {
                    if (order[i + 1] == '(') {
                        NODE* find = search(roots[crr]->root, order[i + 2]);
                        if (find == NULL) {//해당 노드 미존재시
                            printf("\n\t{%c} is not in tree\n", order[i + 2]);
                            break;
                        }else if (order[i + 3] == ')') {//level of node
                            int cnt = levelofnode(roots[crr], find, isbinarytree);
                            printf("\n\tlevel of node {%c} : %d\n", find->data, cnt);
                        }
                    }i = i + 3;
                }
                break;
            case'J':
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }
                if (order[i + 1] == '\0') break; //자동 오타 수정 기능
                if (order[i + 1] == '(') {
                    int crrr = -1, crnt = -1, p = -1;
                    for (int j = 0; j < len; j++) {
                        if (roots[j]->root->data == order[i + 3]) {
                            crrr = j;
                            if (order[i + 3] == order[i + 2]) p = j;
                        }
                        else if (roots[j]->root->data == order[i + 4]) {
                            crnt = j;
                            if (order[i + 4] == order[i + 2]) p = j;
                        }
                    }
                    if (crrr == -1 && crnt == -1)
                        printf("\n\t%c, %c가 root node인 tree가 존재하지 않습니다.\n", order[i + 3], order[i + 4]);
                    else if (crrr == -1)
                        printf("\n\t%c가 root node인 tree가 존재하지 않습니다.\n", order[i + 3]);
                    else if (crnt == -1)
                        printf("\n\t%c가 root node인 tree가 존재하지 않습니다.\n", order[i + 4]);
                    else if (p != -1)
                        printf("\n\t%c가 root node인 tree가 이미 정의되어있기에\n\tnew tree 생성 불가능합니다.\n", order[i + 2]);
                    else if (order[i + 5] == ')') {
                        crr = len;
                        create(roots[crr], order[i + 2]);//새 트리 생성
                        if (isbinarytree == TRUE)
                            roots[crr] = joinbn(roots[crr], roots[crrr], roots[crnt]);
                        else roots[crr] = join(roots[crr], roots[crrr], roots[crnt]);
                        roots[crr]->cnt = roots[crrr]->cnt + roots[crnt]->cnt + 1;

                        len++;
                    }
                    i += 5;
                }
                break;
            case '#'://
                if (crr == -1) {
                    printf("\n\ttree가 아직 생성되지 않았습니다.\n");
                    break;
                }if (order[i + 1] == '\0') {
                    count(roots[crr],crr+1);
                    break;
                }
                else {
                    int crrr = -1;
                    for (int j = 0; j < len; j++) {
                        if (roots[j]->root->data == order[i + 1]) crrr = j;
                    }
                    count(roots[crrr], crrr+1);
                    i++;
                }
                break;
            case'@':
                printf("\n\tcount all tree : %d\n",len);
                break;
            case 'T'://
                break;
            case'Q':
                printf("\n\ttree를 모두 지우고 프로그램을 종료합니다.\n");
                if (crr != -1) {
                    crr = len-1;
                    while (crr != -1) {
                        int n;
                        printf("\n\tdelete tree[%d] (root node {%c})",crr+1,roots[crr]->root->data);
                        if (isbinarytree == TRUE) n = clear(roots[crr], roots[crr]->root);
                        else n = clearbn(roots[crr], roots[crr]->root);
                        crr--;
                    }
                }
                printf("\n\n\t삭제할 tree가 존재하지 않으므로 프로그램을 종료합니다.\n\n\t\t\t\t\t\t\t\t-end-\n\n\n\n");
                go = FALSE;
                break;
            default:
                break;
            }//switch

        }//for

    }//while
    return 0;
}

void create(T* tree, char data) {
    NODE* new = (NODE*)malloc(sizeof(NODE));
    tree->root = new;
    tree->root->left_child = NULL;
    tree->root->right_sibling = NULL;
    tree->root->data = data;
    tree->cnt = 1;
}

NODE* search(NODE* pnode, char data) {
    if (pnode == NULL)return NULL;
    if (pnode->data == data) return pnode;
    NODE* new = search(pnode->left_child, data);
    if (new != NULL) return new;
    new = search(pnode->right_sibling, data);
    if (new != NULL) return new;
    return NULL;
}

void insertchild(T* tree, NODE* pnode, char cnode, int isbinarytree) {

    NODE* new = (NODE*)malloc(sizeof(NODE));
    NODE* tmp = pnode->left_child;

    if (isbinarytree == TRUE) {//이진트리인경우
        if (pnode->left_child == NULL) {//첫칸 빔
            pnode->left_child = new;
            //printf("inserting %c 's first child\n", pnode->data);//
        }
        else if (pnode->right_sibling == NULL) {//두번째칸 빔
            pnode->right_sibling = new;
            //printf("inserting %c 's second child \n", pnode->data);//
        }
        else {
            printf("\n\tbinarytree이기 때문에 더 이상 노드 %c를 추가할 수 없습니다\n", cnode);
            return;
        }
    }
    else {//일반 트리인 경우
        if (pnode->left_child == NULL) {//자식노드 x
            pnode->left_child = new;
            //printf("inserting %c 's first child\n", pnode->data);//
        }
        else if (tmp->right_sibling == NULL) {
            //printf("inserting %c 's second child\n", pnode->data);//
            tmp->right_sibling = new;
        }
        else {//자식노드 존재
            while (tmp->right_sibling != NULL) {//부모노드의 자식노드 끝 자리로
                tmp = tmp->right_sibling;
                //printf("inserting %c 's child %c 's sibling\n", pnode->data, tmp->data);//
            }
            tmp->right_sibling = new;
        }
        //printf("insert complete\n");//
    }
    new->right_sibling = NULL;
    new->left_child = NULL;
    new->data = cnode;
    tree->cnt++;
}

void print(NODE* pnode, NODE* cnode) {
    NODE* crr = cnode->left_child;
    if (pnode == cnode) printf("%c", pnode->data);
    if (pnode->left_child == NULL) return;

    printf("(");
    while (crr != NULL) {
        printf("%c", crr->data);
        if (crr->left_child != NULL) print(pnode, crr);
        if (crr->right_sibling != NULL) printf(",");
        crr = crr->right_sibling;
    }
    printf(")");
}
void printbn(NODE* pnode, NODE* cnode) {
    NODE* crr = cnode->left_child;
    if (pnode == cnode) printf("%c", pnode->data);//root 출력
    if (pnode->left_child == NULL) return;

    if (crr != NULL) {
        printf("(%c", crr->data);
        //printf("\n(%c 's left child %c", cnode->data,crr->data);
        printbn(cnode, crr);
        if (cnode->right_sibling != NULL) {
            printf(",%c", cnode->right_sibling->data);
            //printf("\n,%c 's right child %c", cnode->data, cnode->right_sibling->data);
            printbn(cnode, cnode->right_sibling);
        }
        printf(")");
    }
}

void count(T* tree,int crrr) {
    printf("\n\ttree[%d] (root node {%c}) all node count : %d\n",crrr, tree->root->data,tree->cnt);
}

NODE* get_parent(NODE* pnode, char data) {
    if (pnode == NULL)return NULL;
    if (pnode->left_child == NULL)return NULL;
    NODE* child = pnode->left_child;
    if (child == NULL) return NULL;
    if (child->data == data)return pnode;
    NODE* new = get_parent(child, data);
    if (new != NULL) return new;
    while (child->right_sibling != NULL) {
        if (child->right_sibling->data == data) return pnode;
        NODE* new2 = get_parent(child->right_sibling, data);
        if (new2 != NULL) return new2;
        child = child->right_sibling;
    }
    return NULL;
}
NODE* get_parentbn(NODE* pnode, char data) {
    if (pnode == NULL) return NULL;
    if (pnode->right_sibling != NULL)
        if (pnode->right_sibling->data == data)return pnode;
    if (pnode->left_child == NULL) return NULL;
    if (pnode->left_child->data == data) return pnode;

    NODE* new = get_parentbn(pnode->left_child, data);
    if (new != NULL) return new;
    new = get_parentbn(pnode->right_sibling, data);
    if (new != NULL) return new;
    return NULL;
}

void get_sibling(T* tree, char data) {
    NODE* parent = get_parent(tree->root, data);
    NODE* child = parent->left_child;
    int cnt = 0;
    while (child != NULL) {//sibling 개수 확인 
        cnt++;
        child = child->right_sibling;
    }
    if (cnt < 2) {//child 자기자신 하나일때
        printf("\n\t%c의 sibling 이 존재하지 않습니다.\n", data);
        return;
    }
    //sibling print
    child = parent->left_child;
    printf("\n\t{%c}'s sibling node(s) : {", data);
    while (child != NULL) {
        if (child->data != data) printf(" %c", child->data);
        child = child->right_sibling;
    }
    printf(" }\n");
}
void get_siblingbn(T* tree, char crr) {
    NODE* parent = get_parentbn(tree->root, crr);
    if (parent->left_child->data == crr) {
        if (parent->right_sibling != NULL)
            printf("\n\t{%c}'s sibling node : {%c}\n", crr, parent->right_sibling->data);
        else printf("\n\t%c의 sibling 이 존재하지 않습니다.\n", crr);
    }
    else if (parent->right_sibling->data == crr)
        printf("\n\t{%c}'s sibling node : {%c}\n", crr, parent->left_child->data);
    else return;


}

void get_child(NODE* parent) {
    if (cnodenum(parent) == 0) {
        printf("\n\t{%c}의 child가 존재하지 않습니다.\n", parent->data);
        return;
    }
    NODE* child = parent->left_child;

    //child print
    printf("\n\t{%c}'s child node(s) : {", parent->data);
    while (child != NULL) {
        printf(" %c", child->data);
        child = child->right_sibling;
    }
    printf(" }\n");
}
void get_childbn(NODE* parent) {
    int cnt = cnodenumbn(parent);
    if (cnt == 0)
        printf("\n\t{%c}의 child가 존재하지 않습니다.\n", parent->data);
    else if (parent->right_sibling == NULL)
        printf("\n\t{%c}'s child node : {%c}\n", parent->data, parent->left_child->data);
    else printf("\n\t{%c}'s child nodes : {%c,%c}\n", parent->data, parent->left_child->data, parent->right_sibling->data);
}

void insertsibling(T* tree, NODE* sibling, char data, int isbinarytree) {
    //입력된 node값이 root일 경우
    if (sibling->data == tree->root->data) {
        printf("\n\t{%c(root node)}에 sibling node {%c}을 추가할 수 없습니다. \n", tree->root->data, data);
        return;
    }

    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->data = data;


    if (isbinarytree == TRUE) {//이진트리인경우
        NODE* pnode = get_parentbn(tree->root, sibling->data);
        if (pnode->right_sibling == NULL) {//두번째칸 빔
            pnode->right_sibling = new;
        }
        else {
            printf("\n\tbinarytree이기 때문에 더 이상 노드 {%c}를 추가할 수 없습니다\n", data);
            return;
        }
    }
    else {//일반 트리인 경우
        NODE* pnode = get_parent(tree->root, sibling->data);
        NODE* tmp = pnode->left_child; //first child
        if (tmp->right_sibling != NULL) {//노드 두개 이상이면 
            while (tmp->right_sibling != NULL) {//자식노드 끝 자리로
                tmp = tmp->right_sibling;
            }
        }
        tmp->right_sibling = new;
    }
    new->right_sibling = NULL;
    new->left_child = NULL;
    tree->cnt++;
}

void get_descendants(NODE* pnode, NODE* cnode) {

    if (pnode->left_child == NULL) {
        printf("\n\t{%c}의 child node가 존재하지 않습니다.\n", pnode->data);
        return;//자식 노드 없으면 종료
    }
    //자식노드 있을때
    printf("\n\t{%c}'s descendants node : { ", pnode->data);
    NODE* crr = cnode->left_child;
    while (crr != NULL) {
        printf("%c ", crr->data);
        if (crr->left_child != NULL) print(pnode, crr);
        crr = crr->right_sibling;
    }
    printf("}\n");
}
void get_descendantsbn(NODE* pnode, NODE* cnode) {
    if (pnode->left_child == NULL) {
        printf("\n\t{%c}의 child node가 존재하지 않습니다.\n", pnode->data);
        return;//자식 노드 없으면 종료
    }
    //자식노드 있을때
    printf("\n\t{%c}'s descendants node : { ", pnode->data);
    NODE* crr = cnode->left_child;

    if (crr != NULL) {
        printf("%c ", crr->data);
        //printf("\n(%c 's left child %c", cnode->data,crr->data);
        printbn(cnode, crr);
        if (cnode->right_sibling != NULL) {
            printf("%c ", cnode->right_sibling->data);
            //printf("\n,%c 's right child %c", cnode->data, cnode->right_sibling->data);
            printbn(cnode, cnode->right_sibling);
        }
    }
    printf("}\n");
}

void get_ancestors(T* tree, NODE* cnode, int isbinarytree) {
    NODE* tmp = cnode;
    NODE* pnode;
    printf("\n\t{%c}'s ancestor node(s) : { ", cnode->data);
    while (tmp != NULL) {
        if (isbinarytree == TRUE) pnode = get_parentbn(tree->root, tmp->data);
        else  pnode = get_parent(tree->root, tmp->data);
        if (pnode != NULL) printf("%c ", pnode->data);
        else break;
        tmp = pnode;
    }
    printf("}\n");
}

int cnodenum(NODE* parent) {
    if (parent == NULL)return -1;//필요한가
    int cnt = 0;
    if (parent->left_child == NULL) return cnt;
    NODE* child = parent->left_child;
    //child print
    while (child != NULL) {
        cnt++;
        child = child->right_sibling;
    }
    return cnt;
}
int cnodenumbn(NODE* parent) {

    if (parent->left_child == NULL) return 0;
    else if (parent->right_sibling == NULL)
        return 1;
    else return 2;
}

void degreeofnode(NODE* parent) {
    printf("\n\tdegree of node {%c} : %d\n", parent->data, cnodenum(parent));
}
void degreeofnodebn(NODE* parent) {
    printf("\n\tdegree of node {%c} : %d\n", parent->data, cnodenumbn(parent));
}

NODE* degreeoftree(NODE* p1, NODE* p2) {
    if (p1 == NULL) return NULL;
    NODE* new = cnodenum(p1) > cnodenum(p2) ? p1 : p2;
    new = degreeoftree(p1->left_child, new) ? degreeoftree(p1->left_child, new) : new;
    new = degreeoftree(p1->right_sibling, new) ? degreeoftree(p1->right_sibling, new) : new;
    return new;
}
NODE* degreeoftreebn(NODE* p1, NODE* p2) {
    if (p1 == NULL) return NULL;
    NODE* new = cnodenumbn(p1) > cnodenumbn(p2) ? p1 : p2;
    new = degreeoftreebn(p1->left_child, new) ? degreeoftreebn(p1->left_child, new) : new;
    new = degreeoftreebn(p1->right_sibling, new) ? degreeoftreebn(p1->right_sibling, new) : new;
    return new;
}

int delete_node(T* tree, NODE* node) {
    int n = cnodenum(node);//해당 노드가 갖고 있는 자식노드 개수 
    if (n > 0) {
        return FALSE;
    }
    int childnum = cnodenum(get_parent(tree->root, node->data));//형제노드 개수 
    if (get_parent(tree->root, node->data) == NULL) {//root node 하나 남았을 때
        free(tree->root);
        return -1;
    }
    NODE* firstchild = get_parent(tree->root, node->data)->left_child;
    
    if (childnum == 1) {//자식노드가 자신 하나 뿐 
        NODE* rmv = firstchild;
        get_parent(tree->root, node->data)->left_child = NULL;
        free(rmv);
    }
    else if (node->data == firstchild->data) {//지울 노드가 첫번째 자식노드일 때 
        NODE* rmv = firstchild;
        get_parent(tree->root, node->data)->left_child = firstchild->right_sibling;//두번째 자식노드를 부모노드의 첫번째 자식노드로 연결줌
        free(rmv);
    }
    else if (childnum == 2) {
        NODE* rmv = firstchild->right_sibling;
        firstchild->right_sibling = NULL;
        free(rmv);
    }
    else {//나머지
        NODE* tmp = firstchild;
        NODE* tmpt = tmp;
        while (tmp->right_sibling != NULL) {
            tmpt = tmp;
            if (tmp->right_sibling->data == node->data) {
                NODE* rmv = tmp->right_sibling;
                tmpt->right_sibling = rmv->right_sibling;
                free(rmv);
                break;
            }
            tmp = tmp->right_sibling;
        }
        if (tmp->data == node->data) {//맨 끝 자식노드 지우기
            tmpt->right_sibling = NULL;
            free(tmp);
        }
    }
    tree->cnt--;
    return TRUE;
}
int delete_nodebn(T* tree, NODE* node) {
    //해당 자식노드 존재하면 못 지움
    int n = cnodenumbn(node);
    if (n > 0) {
        return FALSE;
    }

    NODE* parent = get_parentbn(tree->root, node->data);//부모노드
    if (parent == NULL && tree->cnt == 1) {//root node 하나 남았을 때 
        free(tree->root);
        return -1;
    }
    if (parent == NULL) {
        printf("\n\tparent cannot find : child node %c\n", node->data);//
        return FALSE;
    }

    if (parent->left_child->data == node->data) {//왼쪽 노드 지워야함
        NODE* rmv = parent->left_child;
        if (parent->right_sibling != NULL) {//오른쪽노드 차있을때
            parent->left_child = parent->right_sibling;
            parent->right_sibling = NULL;
        }
        else parent->left_child = NULL;//왼쪽노드 하나 있을때
        free(rmv);
    }
    else {//오른쪽 노드 지워야함
        NODE* rmv = parent->right_sibling;
        parent->right_sibling = NULL;
        free(rmv);
    }
    tree->cnt--;
    return TRUE;
}

int clear(T* tree, NODE* pnode) {
    NODE* crr = pnode->left_child;
    if (tree->cnt == 1) {
        free(tree->root);
        return -1;
    }
    //자식노드 없으면 반환
    if (pnode->left_child == NULL) return TRUE;
    //자식노드 있으면 
    while (pnode->left_child != NULL) {
        if (crr->right_sibling == NULL) break;
        while (crr->right_sibling != NULL) {//맨 끝부터 지움 
            crr = crr->right_sibling;

        }
        int k = clear(tree, crr);//crr자식노드 있ㄴ ㅏ?
        if (k == TRUE) { //crr자식노드 없으면 crr삭제
            int l = delete_node(tree, crr);
        }
        crr = pnode->left_child;//다시 돌아가서 자식노드 없어질때까지 지우기
    }
    if (tree->cnt == 1) {
        free(tree->root);
        return -1;
    }
}
int clearbn(T* tree, NODE* pnode) {
    if (tree->cnt == 1) {
        free(tree->root);
        return -1;
    }
    //printf("\n\npnode node : %c", pnode->data);
    NODE* crr = pnode->left_child;
    if (pnode->left_child == NULL) return TRUE;

    //자식노드 없으면 반환
    if (pnode->left_child == NULL) return TRUE;

    //자식노드 있으면 
    if (crr != NULL) {
        if (pnode->right_sibling != NULL) {//오른쪽에 값 존재하면 (degree값 2이면)
            int n = clearbn(tree, pnode->right_sibling);//오른쪽 노드에 자식노드 있나 확인
            if (n == TRUE) {
                //printf("\ndelete %c", pnode->right_sibling->data);
                int k = delete_nodebn(tree, pnode->right_sibling);//없으면 지우기
            }
        }
        if (pnode->left_child != NULL) {
            int n = clearbn(tree, pnode->left_child);//왼쪽 노드에 자식노드 있나 확인
            if (n == TRUE) {
                //printf("\ndelete %c", pnode->left_child->data);
                int k = delete_nodebn(tree, pnode->left_child);//없으면 지우기
            }
        }
    }

    if (tree->cnt == 1) {
        free(tree->root);
        return -1;
    }
    return TRUE;
}

int levelofnode(T* tree, NODE* cnode, int isbinarytree) {
    NODE* tmp = cnode;
    NODE* pnode;
    int cnt = 0;
    while (tmp != NULL) {
        if (isbinarytree == TRUE) pnode = get_parentbn(tree->root, tmp->data);
        else  pnode = get_parent(tree->root, tmp->data);
        if (pnode != NULL) cnt++;
        else break;
        tmp = pnode;
    }
    return cnt;
}
NODE* leveloftree(T* tree, NODE* p1, NODE* p2, int isbinarytree) {
    if (p1 == NULL) return NULL;
    NODE* new = levelofnode(tree, p1, isbinarytree) > levelofnode(tree, p2, isbinarytree) ? p1 : p2;
    new = leveloftree(tree, p1->left_child, new, isbinarytree) ? leveloftree(tree, p1->left_child, new, isbinarytree) : new;
    new = leveloftree(tree, p1->right_sibling, new, isbinarytree) ? leveloftree(tree, p1->right_sibling, new, isbinarytree) : new;
    return new;
}

T* copy(T* tree,NODE*root) {
    if (tree== NULL) return NULL;
    if (root != NULL) {
        T* new = (T*)malloc(sizeof(T));
        create(new, root->data);
        //root 왼쪽 
        if (root->left_child != NULL) {
            T* copyleft = copy(tree, root->left_child);
            new->root->left_child = copyleft->root;

        }
        else new->root->left_child = NULL;
        //root 오른쪽
        if (root->right_sibling != NULL) {
            T* copyright = copy(tree, root->right_sibling);
            new->root->right_sibling = copyright->root;
        }else new->root->right_sibling = NULL;

        return new;
    }
}

T* join(T* newtree, T* tree1, T* tree2) {
    
    T* copy1 = copy(tree1,tree1->root);
    T* copy2 = copy(tree2,tree2->root);
    newtree->root->left_child = copy1->root;
    newtree->root->right_sibling == NULL;
    copy1->root->right_sibling = copy2->root;
    copy2->root->right_sibling = NULL;
    return newtree;
}

T* joinbn(T* newtree, T* tree1, T* tree2) {
    T* copy1 = copy(tree1, tree1->root);
    T* copy2 = copy(tree2, tree2->root);
    newtree->root->left_child = copy1->root;
    newtree->root->right_sibling = copy2->root;
    return newtree;
}
