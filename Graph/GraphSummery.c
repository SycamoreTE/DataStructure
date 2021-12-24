#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxVertexNum 100
#define MaxSize 50

typedef struct {
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

typedef struct EdgeNode{     //边表结点
    int adjvex;         //点的位置
    struct EdgeNode *next;
    ElemType weight;    //边的权值
}EdgeNode;

typedef struct VNode{   //顶点表结点
    ElemType data;
    EdgeNode *first;     //指向第一条依附于该点的弧
}VNode,AdjList[MaxVertexNum];

typedef struct{
    AdjList adjList;
    int vexnum,edgenum;
}Graph;              //以邻接表方式存储的图

void InitQueue(SqQueue *Q){
    Q->front = Q->rear = 0;
}

bool isEmpty(SqQueue Q){
    if(Q.rear == Q.front){
        return true;
    }else{
        return false;
    }
}

bool EnQueue(SqQueue *Q, ElemType x){
    if((Q->rear + 1)%MaxSize == Q->front){
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue *Q, ElemType *x){
    if(Q->rear == Q->front){
        return false;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1)%MaxSize;
    return true;
}

//初始化
void InitStack(SqStack* s){
    s->top = -1;
}

bool StackEmpty(SqStack* s){
    if(s->top == -1){
        return true;
    }else{
        return false;
    }
}

//进栈
bool Push(SqStack *s, ElemType x){
    if(s->top == MaxSize-1){
        return false;
    }else{
        s->data[++s->top] = x;
        return true;
    }
}

//出栈
ElemType Pop(SqStack *s){
    if(s->top == -1){
        return -1;
    }else{
        return s->data[s->top--];
    }
}

void CreateGraph(Graph *G){
    EdgeNode *p,*pe;
    printf("input vexnum : ");
    scanf("%d",&G->vexnum);
    printf("\ninput edgenum : ");
    scanf("%d",&G->edgenum);

    int i,j,k;
    for(i = 0; i< G->vexnum; i++){
        printf("\ninput vertex info: ");
        scanf("%d",&G->adjList[i].data);
        G->adjList[i].first = NULL;
    }
    for(k = 0; k < G->edgenum; k++){
        //输入下标位置
        printf("input vi and vj : ");
        scanf("%d %d",&i,&j);
        p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->adjvex = j;
        p->next = G->adjList[i].first;
        G->adjList[i].first = p;

        // 有向图, 无向图
        pe = (EdgeNode*)malloc(sizeof(EdgeNode));
        pe->adjvex = i;
        pe->next = G->adjList[j].first;
        G->adjList[j].first = pe;
    }
}

void PrintGraph(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        EdgeNode *p = G.adjList[i].first;
        while(p){
            printf("(%d-->%d) ",G.adjList[i].data,G.adjList[p->adjvex].data);
            p = p->next;
        }
        printf("\n");
    }
}

//v 表示从第几个顶点出发
ElemType FindFirstNeighbor(Graph G, int v){
    EdgeNode *p = G.adjList[v].first;
    if(p){
        return p->adjvex;
    }
    return -1;
}

//v 表示从第几个顶点出发，w 表示已被访问的顶点
ElemType NextNeighbor(Graph G, int v, int w){
    EdgeNode *p = G.adjList[v].first;
    while(p){
        if(p->adjvex != w){
            return p->adjvex;
        }
        p = p->next;
    }
    return -1;
}

void visit(Graph G, int v){
    printf("%d-->\t",G.adjList[v].data);
}

static int visited[MaxVertexNum];

void BFS(Graph G, int v){
    int w,u;
    visit(G,v);
    visited[v] = true;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, v);
    while(!isEmpty(Q)){
        DeQueue(&Q, &u);
        EdgeNode *p = G.adjList[u].first;
        while(p){
            if(!visited[p->adjvex]){
                visit(G,p->adjvex);
                visited[p->adjvex] = true;
                EnQueue(&Q, p->adjvex);
            }
            p = p->next;
        }
    }
}

void BFSTraverse(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            BFS(G, i);
        }
    }
}

//深度优先
void DFS(Graph G, int v){
    visit(G, v);
    visited[v] = true;
    EdgeNode *p = G.adjList[v].first;
    while(p){
        if(!visited[p->adjvex]){
            visited[p->adjvex] = true;
            DFS(G, p->adjvex);
        }
        p = p->next;
    }
}

void DFSTraverse(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            DFS(G,i);
        }
    }
}

//DFS 非递归，使用栈
void DFS_NonRecursion(Graph G, int v){
    int u;
    visited[v] = true;
    SqStack S;
    InitStack(&S);
    Push(&S, v);
    while(!StackEmpty(&S)){
        u = Pop(&S);
        visit(G, u);
        EdgeNode *p = G.adjList[u].first;
        while(p){
            if(!visited[p->adjvex]){
                visited[p->adjvex] = true;
                Push(&S,p->adjvex);
            }
            p = p->next;
        }
    }
}

void DFSTraverse1(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            DFS_NonRecursion(G, i);
        }
    }
}

//判断无向图G是否为一棵树，返回true或false
//使用深度优先搜索，若遍历一次无向图G就能访问到n个顶点和n-1条边，可断定图G是一棵树
void DFS_Tree(Graph G, int v, int *Vnum, int *Enum, int visited[]){
    visited[v] = true; 
    (*Vnum)++;
    visit(G, v);
    EdgeNode *p = G.adjList[v].first;
    while(p){
        if(!visited[p->adjvex]){
            (*Enum)++;
            visited[p->adjvex] = true;
            DFS_Tree(G, p->adjvex, Vnum, Enum, visited);
        }
        p = p->next;
    }
}

bool isTree(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    int Vnum = 0,Enum = 0;
    DFS_Tree(G, 0, &Vnum, &Enum, visited);
    printf("\n Enum, Vnum : %d, %d",Enum,Vnum);
    if(Vnum == G.vexnum && Enum == (G.vexnum - 1)){
        return true;
    }else{
        return false;
    }
}
//判别是否存在由顶点Vi到Vj的路径
void DFS_Vi_Vj(Graph G, int i, int j, int *can_reach){
    visited[i] = true;
    visit(G, i);
    if(i == j){
        *can_reach = true;
        return;
    }
    EdgeNode *p = G.adjList[i].first;
    while(p){
        if(!visited[p->adjvex] && !(*can_reach)){
            DFS_Vi_Vj(G, p->adjvex, j, can_reach);
        }
        p = p->next;
    }
}

//判别是否存在由顶点Vi到Vj的路径
int BFS_Vi_Vj(Graph G, int i, int j){
    int u;
    SqQueue Q;
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    InitQueue(&Q);
    EnQueue(&Q, i);
    if(i == j){
        return 1;
    }
    while(!isEmpty(Q)){
        DeQueue(&Q, &u);
        visit(G, u);
        visited[u] = true;
        EdgeNode *p = G.adjList[u].first;
        while(p){
            if(p->adjvex == j){
                return 1;
            }
            if(!visited[p->adjvex]){
                EnQueue(&Q, p->adjvex);
                visited[p->adjvex] = true;
            }
            p = p->next;
        }
    }
    return 0;
}

//输出从Vi 到 Vj 的所有简单路径
void FindPath_Vi_Vj(Graph G, int i, int j, int path[],int d){
    int w;
    d++;
    path[d] = i;
    visited[i] = true;
    if(i == j){
        for(int k = 0; k <= d; k++){
            if(path[k] != 0){
                printf("%d-->",path[k]);
            }
        }
        printf("\n");
    }
    EdgeNode *p = G.adjList[i].first;
    while(p){
        if(!visited[p->adjvex]){
            FindPath_Vi_Vj(G, p->adjvex, j, path, d);
        }     
        p = p->next;
    }
    //恢复访问路径，可返回重新找新的路径
    visited[i] = false;
}

static int indegree[MaxSize];
//拓扑排序
bool TopologicalSort(Graph G){
    int u;
    SqStack S;
    InitStack(&S);
    for(int i = 0; i < G.vexnum; i++){
        if(indegree[i] == 0){
            Push(&S,i);
        }
    }
    int count = 0;
    while(!StackEmpty(&S)){
        u = Pop(&S);
        visit(G, u);
        count++;
        EdgeNode *p = G.adjList[u].first;
        while(p){
            if(!(--indegree[p->adjvex])){
                Push(&S,p->adjvex);
            }
            p = p->next;
        }
    }
    if(count < G.vexnum){
        return false;
    }else{
        return true;
    }
}

int main(){
    Graph G;
    CreateGraph(&G);
    PrintGraph(G);
    BFSTraverse(G);
    // BFS(G,0);
    printf("\n");
    DFSTraverse(G);
    printf("\n");
    DFSTraverse1(G);
    printf("\n");
    if(isTree(G)){
        printf("\n Graph is a tree");
    }else{
        printf("\n Graph is not a tree");
    }
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    printf("\n");
    int can_reach = false;
    DFS_Vi_Vj(G, 1, 7, &can_reach);
    if(can_reach){
        printf("\n DFS Vi can reach Vj\n");
    }else{
        printf("\n DFS Vi can not reach Vj\n");
    }
    if(BFS_Vi_Vj(G, 1, 7)){
        printf("\n BFS Vi can reach Vj");
    }else{
        printf("\n BFS Vi can not reach Vj");
    }
    printf("\n");
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    int path[8] = {0};
    FindPath_Vi_Vj(G, 0, 7, path, 0);
    return 0;
}