#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StackQueue.h"

#define MaxVertexNum 100

typedef struct ArcNode{    //边表结点
    int adjvex;   //当前结点的位置
    struct ArcNode *next;    //链接下一个邻接点
}ArcNode;

typedef struct VNode{     //顶点表结点
    ElemType data;        //顶点的值
    ArcNode *first;       //顶点指向的第一条边
}VNode,AdjList[MaxVertexNum];

typedef struct Graph{
    AdjList adjList;      //邻接表
    int vexnum, arcnum;   //图的顶点数量和边数
}Graph;

void CreateGraph(Graph *G){
    ArcNode *p, *q;
    printf("please input vexnum : ");
    scanf("%d",&G->vexnum);
    printf("please input edgenum : ");
    scanf("%d",&G->arcnum);

    int i,j,k;
    for(i = 0; i < G->vexnum; i++){
        printf("please input vertex info : ");
        scanf("%d",&(G->adjList[i].data));
        G->adjList[i].first = NULL;
    }
    for(k = 0; k < G->arcnum; k++){
        printf("input edge vi vj : ");
        scanf("%d %d",&i,&j);
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->next = G->adjList[i].first;
        G->adjList[i].first = p;

        q = (ArcNode*)malloc(sizeof(ArcNode));
        q->adjvex = i;
        q->next = G->adjList[j].first;
        G->adjList[j].first = q;
    }
}

void printGraph(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        ArcNode *p = G.adjList[i].first;
        while(p){
            printf("(%d-->%d)",G.adjList[i].data, G.adjList[p->adjvex].data);
            p = p->next;
        }
        printf("\n");
    }
}

ElemType FindFirstNeighbor(Graph G, int v){
    ArcNode *p = G.adjList[v].first;
    if(p){
        return p->adjvex;
    }
    return -1;
}

ElemType NextNeighbor(Graph G, int v, int w){
    ArcNode *p = G.adjList[v].first;
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
    int w;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q,v);
    visit(G, v);
    visited[v] = true;
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &w);
        ArcNode *p = G.adjList[w].first;
        while(p){
            if(!visited[p->adjvex]){
                visit(G, p->adjvex);
                visited[p->adjvex] = true;
                EnQueue(&Q,p->adjvex);
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

void DFS(Graph G, int v){
    visit(G, v);
    visited[v] = true;
    ArcNode *p = G.adjList[v].first;
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

void DFS_NonRecursion(Graph G, int v){
    int u;
    SqStack S;
    InitStack(&S);
    Push(&S,v);
    visited[v] = true;
    while(!StackEmpty(S)){
        Pop(&S, &u);
        visit(G, u);
        ArcNode *p = G.adjList[u].first;
        while(p){
            if(!visited[p->adjvex]){
                visited[p->adjvex] = true;
                Push(&S, p->adjvex);
            }
            p = p->next;
        }
    }
}

void DFSTraverseNonRecursion(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(!visited[i]){
            DFS_NonRecursion(G,i);
        }
    }
}

void DFS_Tree(Graph G, int v, int *vNum, int *eNum, int visited[]){
    visited[v] = true;
    (*vNum)++;
    visit(G, v);
    ArcNode *p = G.adjList[v].first;
    while(p){
        if(!visited[p->adjvex]){
            visited[p->adjvex] = true;
            (*eNum)++;
            DFS_Tree(G, p->adjvex, vNum, eNum, visited);
        }
        p = p->next;
    }
}

//判断图是否为树，遍历一遍，能得到n个顶点及n-1条边
bool isTree(Graph G){
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    int vNum = 0, eNum = 0;
    DFS_Tree(G,0,&vNum,&eNum,visited);
    if(vNum == G.vexnum && eNum == (G.vexnum - 1)){
        return true;
    }else{
        return false;
    }
}

//DFS遍历判断是否存在Vi Vj的路径
void DFS_Vi_Vj(Graph G, int i, int j, int *can_reach){
    visited[i] = true;
    visit(G, i);
    if(i == j){
        *can_reach = 1;
        return;
    }else{
        ArcNode *p = G.adjList[i].first;
        while(p){
            if(!visited[p->adjvex] && !(*can_reach)){
                DFS_Vi_Vj(G, p->adjvex, j, can_reach);
            }
            p = p->next;
        }
    }
}

bool BFS_Vi_Vj(Graph G, int i, int j){
    for(int k = 0; k < G.vexnum; k++){
        visited[k] = false;
    }
    if(i == j){
        return true;
    }
    int u;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, i);
    visited[i] = true;
    while(!QueueEmpty(Q)){
        DeQueue(&Q,&u);
        ArcNode *p = G.adjList[u].first;
        while(p){
            if(p->adjvex == j){
                return true;
            }
            if(!visited[p->adjvex]){
                visited[p->adjvex] = true;
                EnQueue(&Q,p->adjvex);
            }
            p = p->next;
        }
    }
    return false;
}

static ElemType path[MaxVertexNum] = {0};
static int pathnum = 0;
void FindPath_Vi_Vj(Graph G, int u, int v, int d){
    int i;
    ArcNode *p;
    visited[u] = true;
    path[d] = u;
    if(u == v){
        pathnum++;
        printf("%d  ",pathnum);
        for(i = 0; i <= d; i++){
            printf("%d\t", path[i]);
        }
        printf("\n");
    }else{
        p = G.adjList[u].first;
        while(p){
            if(!visited[p->adjvex]){
                FindPath_Vi_Vj(G, p->adjvex, v, d+1);
            }
            p = p->next;
        }
    }
    visited[u] = false;
    path[d] = 0;
}

static int bfs_path[MaxVertexNum];
static int distance[MaxVertexNum];
//BFS求单源最短路径
void BFS_Min_Distance(Graph G, int u){
    for(int i = 0; i < G.vexnum; i++){
        distance[i] = MaxSize;
        bfs_path[i] = -1;
    }
    bfs_path[u] = 0;
    visited[u] = true;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, u);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &u);
        ArcNode *p = G.adjList[u].first;
        while(p){
            if(!visited[p->adjvex]){
                distance[p->adjvex] = distance[u]+1;
                bfs_path[p->adjvex] = u;
                visited[p->adjvex] = true;
                EnQueue(&Q, p->adjvex);
            }
            p = p->next;
        }
    }
}

static int indegree[MaxVertexNum];
bool TopologicalSort(Graph G){
    SqStack S;
    InitStack(&S);
    for(int i = 0; i < G.vexnum; i++){
        if(indegree[i] == 0){
            Push(&S, i);
        }
    }
    int u;
    int count = 0;
    while(!StackEmpty(S)){
        Pop(&S,&u);
        count++;
        for(ArcNode *p = G.adjList[u].first; p; p = p->next){
            if(!(--indegree[p->adjvex])){
                Push(&S, p->adjvex);
            }
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
    printGraph(G);
    BFSTraverse(G);
    printf("\n");
    DFSTraverse(G);
    printf("\n");
    if(isTree(G)){
        printf("\nGraph G is a tree\n");
    }else{
        printf("\nGraph G is not a tree\n");
    }
    DFSTraverseNonRecursion(G);
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    int can_reach = 0;
    printf("\n");
    DFS_Vi_Vj(G, 0, 3, &can_reach);
    printf("\ncan_reach is %d\n",can_reach);
    if(BFS_Vi_Vj(G, 0, 3)){
        printf("\ncan reach\n");
    }else{
        printf("\ncan not reach\n");
    }
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    FindPath_Vi_Vj(G, 0, 3, 0);
    for(int i = 0; i < G.vexnum; i++){
        visited[i] = false;
    }
    BFS_Min_Distance(G, 0);
    for(int i = 0; i < G.vexnum; i++){
        printf("%d\t",bfs_path[i]);
    }
    for(int i = 0; i < G.vexnum; i++){
        printf("%d\t",distance[i]);
    }
    return 0;
}