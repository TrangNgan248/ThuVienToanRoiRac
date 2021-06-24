#include <stdio.h>
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 10000
#define INFI 10000000
int n,m,phanloai,n1,m1,n2,s2,f2;
int** a=NULL;

int nodelv[MAX];
int node[MAX];
int time, D;
int A[MAX][MAX];
int checkLT[MAX],luuLT[MAX];
void ReadFile(FILE*f,Graph G, Graph Gr);
void hoanvi(int *a,int *b)
	{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
	}
int BFS(Graph graph, int start, int stop, void (*func)(int), int *danhdau);
int DFS(Graph graph, int start, int stop, void (*func)(int), int *danhdau);
void PrintList(Graph G);
void vedothi(Graph G);
void vedothicohuong(Graph G);
void Softing();
void Coloring();
int CheckCl(int clused[],int somau,int cl);
int PickCl(int g[],int l);
void printVertex(int v)
{
     printf("%4d", v);
}

void danhdaudothi(Graph G, int* danhdau, int soluong);
void danhdaudothicohuong(Graph G, int* danhdau, int soluong);
void prepost(Graph G, int start, int* visited, int* pre, int* post);
void TOPO(int* post, int* posts);
//case 6:
int DAG(Graph graph);
//case 9:
int DFS_timduong(Graph graph, int start);
//case 10:
struct ShortPath{
	int data;
	struct ShortPath *prev;
};
typedef struct ShortPath *shortPath;
shortPath create(int data);
void readFileDijkstra(FILE *fin);
void print();
int findCostmin(int *current_node, int passed_node[], int cost[]);
void dijkstra(int *current_node, int passed_node[], int cost[]);

//case 11:
typedef struct Edge
{
	int u, v, w;
}edge;
edge add_edge(int u, int v, int w);
void kruskal(int parent[],edge edges[], edge T[]);
void swap(edge *a1, edge *b1)
{
    int u = a1->u;
    a1->u=b1->u;
    b1->u=u;
    u = a1->v;
    a1->v=b1->v;
    b1->v=u;
    u = a1->w;
    a1->w=b1->w;
    b1->w=u;
}
int partition(edge edges[], int hight, int low)
{
    int pivot = edges[hight].w;
    int left = low;
    int right = hight - 1;
    while(1)
    {
        while(edges[left].w<pivot&&left<=right){
        left ++;
    }
        while(edges[right].w>pivot&&right>=left){
        right --;
    }
        if(left>=right) break;
        else swap(&edges[left], &edges[right]);
        left++;
        right--;
}
    swap(&edges[left], &edges[hight]);
    return left;
}
void quickSort(edge edges[], int hight, int low){
    if(low<hight){
        int key = partition(edges, hight, low);
        quickSort(edges, key -1, low);
        quickSort(edges, hight, key+1);
    }	
}
void readFile(FILE *fin, edge edges[]); 

//


int main()
{
    Graph G = createGraph();
    Graph Gr = createGraph();
    		
	    int choice=0,c,soluong,tmp,i,j,k,h,e,v,demlt;
	    int danhdau[MAX],visited[MAX],pre[MAX],post[MAX],posts[MAX];
	   
    
    FILE *fin = fopen("inputKruskal.txt", "r");
    FILE *fin2 = fopen("inputDijkstra1.txt", "r");
    FILE* f = fopen("dothicohuong1.txt", "r");
    ReadFile(f,G,Gr);
    fscanf(fin, "%d %d\n", &n1, &m1);  //m la so canh, n so dinh
    readFileDijkstra(fin2);
    edge edges[m1];//tap canh cua do thi
    edge T[m1]; //luu cay
    int parent[n1];
    int current_node = s2;
    int passed_node[MAX];
    int cost[MAX];
    while (choice!=12)    
    {
        
        printf("\n	|====MENU====|\n");
        printf("1. Print List\n");
        printf("2. Ve Do Thi\n");
        printf("3. BFS\n");
        printf("4. DFS\n");
        printf("5. ToMau\n");
        printf("6. DAG\n");
        printf("7. Pre And Post\n");
        printf("8. Sap xep TOPO\n");
        printf("9. Tim thanh phan lien thong manh\n");
        printf("10. Dijkstra\n");
        printf("11. Cay bao trum nho nhat\n");
        printf("12. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        	case 1:
          		PrintList(G);
            		break;
        	case 2:
        		if (phanloai==1)
            		vedothicohuong(G);
            		else vedothi(G);
            		break;
        	case 3:
        		memset(danhdau,0,MAX);
            		soluong= BFS(G,0,-1,printVertex,danhdau);
            		if (phanloai==1)
            		danhdaudothicohuong(G,danhdau,soluong);
            		else danhdaudothi(G,danhdau,soluong);
            		break;
        	case 4:
        		memset(danhdau,0,MAX);
            		soluong= DFS(G,0,-1,printVertex,danhdau);
            		if (phanloai==1)
            		danhdaudothicohuong(G,danhdau,soluong);
            		else danhdaudothi(G,danhdau,soluong);
            		break;
        	
        	case 5:
			c=0;
			for(int i=0;i<n;i++)  //cho node[0]->node[n-1] = 0,1,2,3,4,5,6... n-1
			node[i]=c++;
			int i,j;
			for(i=0;i<n;i++)
				{
				nodelv[i]=0;
				for(j=0;j<n;j++)                 //tinh bac cua node
				nodelv[i]=nodelv[i]+a[i][j];
				}			
			Softing();
			Coloring();
        		break;	
            	case 6:
            		if (DAG(G)==0) printf("Do thi co chu trinh\n"); else printf("Do thi khong co chu trinh\n");
            		break;        	
        	case 7:
        		time =1;
    			memset(visited,0,MAX);
			for (i=0;i<n;i++)
				if (visited[i]!=1)
					{
					prepost(G, i, visited, pre, post);
					printf("\n\n --- xet xong dinh --- %d\n\n",i);           	
					}
				printf("Dinh	pre	post cua G\n");	
				for (i=0;i<n;i++)
					printf("%d	%d	%d	\n",i,pre[i],post[i]);
			
        		break;
        	case 8:
            		TOPO(post,posts);    			           		
            		break;
            	case 9:
            		time =1;
    			memset(visited,0,n);
    			memset(checkLT,0,n);
        		memset(luuLT,0,n);
			for (i=0;i<n;i++)
				if (visited[i]!=1)
					{
					prepost(Gr, i, visited, pre, post);
					printf("\n\n --- xet xong dinh --- %d\n\n",i);           	
					}
				printf("Dinh	pre	post cua Gr\n");	
				for (i=0;i<n;i++)
					printf("%d	%d	%d	\n",i,pre[i],post[i]);
			TOPO(post,posts);
			for (i=0;i<n;i++)
				if (checkLT[posts[i]]==0)
					{
					demlt++;
					
					printf("\nCac node trong TPLTM thu %d la: ",demlt);
					DFS_timduong(G,posts[i]);
					//printf("\nXet xong tpltm cua nut %d\n",posts[i]);
					checkLT[posts[i]]=1;
					
					}
			printf("\n");
            		break;
            	case 10:
			current_node = s2;
			print();
			
			for(i = 0;i<n2;i++){
			passed_node[i]=-1;
			}
			for(i = 0;i<n2;i++){
			cost[i]=INFI;
			}
			cost[current_node] = 0;
			dijkstra(&current_node, passed_node, cost);
            		break;
            	case 11:
            		D=0;
        		readFile(fin, edges); //ra duoc tap canh luon
			quickSort(edges, m1-1, 0); //sap xep xong
			for(i=0;i<m1;i++){
				printf("%d %d %d\n", edges[i].u, edges[i].v, edges[i].w); //in ra thu tu sau khi da sap xep
				}
			kruskal(parent, edges, T); 	
			printf("Tong trong so la: %d\n", D);
			printf("Cac canh trong MST la:\n");
			for(i=0;i<n1-1;i++){
					printf("%d-%d\n", T[i].u,T[i].v);
					}
            		break;
        	case 12:
            		dropGraph(G);
            		return 0;

        	default:
        		printf("\nYour selection is invalid.\n");
            		break;
        }
    }
}
int DFS_timduong(Graph graph, int start)
{ 
   int visited[10000] = {};
   int n, output[1000], i, u, v,a=0;
   Dllist node, stack;
   
   stack = new_dllist();
   dll_append(stack, new_jval_i(start));

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);        
      u = jval_i(node->val);
      //printf("Dang xet nut %d\n",u);  
      dll_delete_node(node);
      //printf("check[u] = %d\n",checkLT[u]);
      if ((checkLT[u]==0))   //(!visited[u])&&
      {
          checkLT[u] = 1;
          printf("%d ",u);
          //luuLT[u]= start;
          //printf("them %d vao trong luuLT cua %d\n",u,start);
          //checkver++;
          n = outdegree(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              //printf("Dang xet nut con cua %d la %d\n",u,v);
              if ((checkLT[v]==0))
              	{
              	 //printf("Chua tham %d, bo %d vao hang cho\n",v,v);
                 dll_append(stack, new_jval_i(v));
                }
               //else printf("Da tham nut %d nay\n",v);
          }
      }
   }                            
}

int DAG(Graph graph)
{
   int visited[1000];
   int nD, output[100], i, u, v, start;
   Dllist node, stack;
   JRB vertex;
   
   jrb_traverse(vertex, graph.vertices)
   {
       memset(visited, 0, sizeof(visited));   //set tat ca cac dinh deu chua co visited

       start = jval_i(vertex->key);              //cho start bang canh dau tien
       stack = new_dllist();			//dung stack
       dll_append(stack, new_jval_i(start));  //them start vao
    
       while ( !dll_empty(stack) )      //khi ma stack chua rong
       {
          node = dll_last(stack);     //node se lay gia tri cuoi cung cua stack
          u = jval_i(node->val);      //u nhan gia tri node
          dll_delete_node(node);
          if (!visited[u])		//neu chua tham u
          {
              visited[u] = 1;		//da tham u
              nD = outdegree(graph, u, output);	//nhan danh sach ke u
              for (i=0; i<nD; i++)
              {
                  v = output[i];		//di lan luot tung nut cua u
                  if ( v == start ) // cycle detected 
                     return 0;
                  if (!visited[v])    //neu chua visit v
                     dll_append(stack, new_jval_i(v)); //them v vao hang doi
              }
          }           
       }
   }
   return 1; // no cycle    
}
shortPath create(int data){
	shortPath temp = (shortPath)malloc(sizeof(shortPath));
	temp->data = data;
	temp->prev = NULL;
	return temp;
}

void readFileDijkstra(FILE *fin){
	fscanf(fin, "%d %d %d\n", &n2, &s2, &f2);
	int i, j;
	for(i=0;i<n2;i++){
		for(j=0;j<n2;j++){
			fscanf(fin, "%d", &A[i][j]);
		}
	}
}

void print(){
	int i, j;
	for(i=0;i<n2;i++){
		for(j=0;j<n2;j++){
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

int findCostmin(int *current_node, int passed_node[], int cost[]){
	int minCost = INFI;
	int imin = *current_node;
	int i;
	for(i = 0;i<n2;i++){
		if(passed_node[i]!=1&&cost[i]<minCost){
			minCost=cost[i];
			imin = i;
		}
	}
	if(imin==*current_node) return -1;
	return imin;
}

void dijkstra(int *current_node, int passed_node[], int cost[]){
	int i;

	shortPath list[n2-1];
	for(i=0;i<n2;i++){
		list[i]=create(i);
	}

	while(1){
		for(i=0;i<n2;i++){
			if(A[*current_node][i]!=0){
				if(cost[i]>cost[*current_node]+A[*current_node][i]){
					cost[i]=cost[*current_node]+A[*current_node][i];
					list[i]->prev=list[*current_node];
				}
			}
		}
		passed_node[*current_node] = 1;
		*current_node = findCostmin(current_node, passed_node, cost);
		if(*current_node==-1) break;
	}
	printf("Duong di tu %d den %d la:\n", f2, s2);
	while(list[f2]->prev!=NULL){
		printf("%d->", list[f2]->data);
		list[f2]=list[f2]->prev;
	}
	printf("%d", list[f2]->data);
	printf("\n");
}
void readFile(FILE *fin, edge edges[]){
	int i = 0;
	while(feof(fin)==0){
		fscanf(fin, "%d %d %d\n", &edges[i].u, &edges[i].v, &edges[i].w);
		i++;
	}
}

edge add_edge(int u, int v, int w){
	edge temp;
	temp.u = u; //dinh dau 
	temp.v = v; //dinh cuoi
	temp.w = w; //trong so
	return temp;
}
void kruskal(int parent[],edge edges[], edge T[])  
	{ 
	int v;
	int t = 0;
	for(v=0;v<n1;v++){   //cho tat ca cha cua cac nut la chinh no
		parent[v] = v; 
	}
	int e;                 
	for(e=0;e<m1;e++){   //trong khi e < tong cac canh (dang xet tung canh 1)
		if(parent[edges[e].u]!=parent[edges[e].v]){  //cha cua nut u  != cha cua nut v          --- edges[e]: canh thu e.   edges[e].u: la dinh dau.  parent[edges[e].u]
			D+=edges[e].w; //tim duoc la chac chan no luon
			T[t] = add_edge(edges[e].u, edges[e].v, edges[e].w);  //them vao cay
			t++; //tang thu tu
			int old_par = parent[edges[e].u];  
			int new_par = parent[edges[e].v]; 
			for(v=0;v<n1;v++){   //chay het tap dinh
				if(parent[v]==old_par)  //neu cha cua 1 dinh bat ky == cha cu
				{
					parent[v]=new_par; //doi thanh cha moi
				}
			}
		}
	}

}
void TOPO(int* post, int* posts)
{
int i,j,tmp;
for (i=0;i<n;i++) posts[i]=i;
        for (i=0;i<n;i++) 
        	for (j=0;j<n;j++)
        		if (post[j]<post[i]) 
        			{
        			tmp=post[j];
        			post[j]=post[i];
        			post[i]=tmp;
        			tmp=posts[j];
       			posts[j]=posts[i];
        			posts[i]=tmp;
        			}
for (i=0;i<n;i++) printf("%d ",posts[i]);	
}
void prepost(Graph G, int start, int* visited, int* pre, int* post)
{      int n=0, output[300],i,tmp;
	visited[start] = 1;
	pre[start] = time;
	printf("Dinh %d duoc them pre la %d \n",start,time);
	time++;
	n=outdegree(G, start, output);
	printf("Dinh %d hien tai co %d dinh co the di toi\nGom cac dinh: ",start,n);
	for (i=0; i<n; i++) printf("%d ",output[i]);
	
	 for (i=0; i<n; i++)
	 	{
	
	 	printf("\nDang xet dinh %d\n",output[i]);
	 	if ((visited[output[i]]!=1))
	 		prepost(G,output[i],visited,pre,post);
	 	}
	 	printf("Xong tap con cua dinh %d\n",start);
	 post[start] = time;
	 printf("Dinh %d duoc them post la %d \n",start,time);
	 time++;
}

int BFS(Graph graph, int start, int stop, void (*func)(int), int* danhdau)
{
   int visited[10000] = {};
   int n, output[100], i, u, v,sd=0,soluong=0;
   Dllist node, queue;
   
   queue = new_dllist();
   dll_append(queue, new_jval_i(start));

   while ( !dll_empty(queue) )
   {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          danhdau[sd++]=u;
          soluong++;
          visited[u] = 1;
          if ( u == stop ) return soluong;           
          n = outdegree(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(queue, new_jval_i(v));
          }
      }
   }
   free_dllist(queue);
   return soluong;                            
}

int DFS(Graph graph, int start, int stop, void (*func)(int), int* danhdau)
{
   int visited[10000] = {};
   int n, output[100], i, u, v,sd=0,soluong=0;
   Dllist node, stack;
   
   stack = new_dllist();
   dll_append(stack, new_jval_i(start));

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          danhdau[sd++]=u;
          soluong++;
          if ( u == stop ) return soluong;           
          n = outdegree(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(stack, new_jval_i(v));
          }
      }
   }
   free_dllist(stack);                            
   return soluong;
}
void ReadFile(FILE* f, Graph G, Graph Gr){
    if (f==NULL) printf("Failed to read file\n"); else printf("Read file succesful!\n");
    int id1, id2,i;
    char name[100];
    double d;
    fscanf(f,"%d\n",&phanloai);
    if (phanloai==1)
    {
    fscanf(f, "%d %d\n", &n, &m);
    a = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		a[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i){
        fscanf(f, "%d\n", &id1);
        addVertex(G, id1, name);
    }
    for (int i = 0; i < m; ++i){
        fscanf(f, "%d %d %lf\n", &id1, &id2, &d);
        addEdge(G,id1,id2,d);
        addEdge(Gr,id2,id1,d);
        //addEdge(G, id2, id1, d);
        a[id1][id2]=1;
      	
        //a[id2][id1]=1;
    }
    return;
    }
    if (phanloai==0)
    {
    fscanf(f, "%d %d\n", &n, &m);
    a = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		a[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i){
        fscanf(f, "%d\n", &id1);
        addVertex(G, id1, name);
    }
    for (int i = 0; i < m; ++i){
        fscanf(f, "%d %d %lf\n", &id1, &id2, &d);
        addEdge(G, id1, id2, d);
        addEdge(G, id2, id1, d);
        a[id1][id2]=1;
        a[id2][id1]=1;
    }
    return;
    }
    if ((phanloai!=0)&&(phanloai!=1)) printf("Wrong type of File\n");
   return;	
}
void PrintList(Graph G)
{	
	int i,j;
    printf("	==LIST==\n");
    JRB iter;
    jrb_traverse(iter, G.vertices)
        printf("%d\n", jval_i(iter->key));
    printf("\n	==MaTranMang==	\n");
    for (i=0;i<n;i++)
    	{
    	for (j=0;j<n;j++)
    		printf("%d ",a[i][j]);
    	printf("\n");
    	}
}
void vedothi(Graph G)
{
	FILE *f;
	int **checked = NULL;
	int tongnut,i,j;
	int output[MAX];
	f = fopen("test.dot","w+");
	checked = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		checked[i] = (int *)malloc(n * sizeof(int));
	for (i=0;i<n;i++) for (j=0;j<n;j++) checked[i][j]=0;
	if(f == NULL)
   		{
   		printf("Error!");   
		exit(1);             
   		}
   	fprintf(f,"graph dothi\n{");
   	JRB iter;
    	jrb_traverse(iter, G.vertices)
    		{
    		//printf("xet toi nut %d\n",jval_i(iter->key));

        	tongnut=outdegree(G,jval_i(iter->key),output);
        	if (tongnut==0) fprintf(f,"%d\n",jval_i(iter->key));
        	for (i=0;i<tongnut;i++)
        		if (checked[jval_i(iter->key)][output[i]]==0)
        		{
        		checked[jval_i(iter->key)][output[i]]=1;
        		checked[output[i]][jval_i(iter->key)]=1;
        		fprintf(f,"%d -- %d\n",jval_i(iter->key),output[i]);
        		printf("%d -- %d\n",jval_i(iter->key),output[i]);
        		}
        	}
   	
   	fprintf(f,"}"); 
   	fclose(f);
	for (i = 0; i < n; i++)
	{
	    	free(checked[i]);
	}
	free(checked);
}
void vedothicohuong(Graph G)
{
	FILE *f;
	int **checked = NULL;
	int tongnut,i,j;
	int output[MAX];
	f = fopen("test.dot","w+");
	checked = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		checked[i] = (int *)malloc(n * sizeof(int));
	for (i=0;i<n;i++) for (j=0;j<n;j++) checked[i][j]=0;
	if(f == NULL)
   		{
   		printf("Error!");   
		exit(1);             
   		}
   	fprintf(f,"digraph dothi\n{");
   	JRB iter;
    	jrb_traverse(iter, G.vertices)
    		{
    		//printf("xet toi nut %d\n",jval_i(iter->key));

        	tongnut=outdegree(G,jval_i(iter->key),output);
        	if (tongnut==0) fprintf(f,"%d\n",jval_i(iter->key));
        	for (i=0;i<tongnut;i++)
        		if (checked[jval_i(iter->key)][output[i]]==0)
        		{
        		checked[jval_i(iter->key)][output[i]]=1;
        		checked[output[i]][jval_i(iter->key)]=1;
        		fprintf(f,"%d -> %d\n",jval_i(iter->key),output[i]);
        		printf("%d -> %d\n",jval_i(iter->key),output[i]);
        		}
        	}
   	
   	fprintf(f,"}"); 
   	fclose(f);
	for (i = 0; i < n; i++)
	{
	    	free(checked[i]);
	}
	free(checked);
}
void danhdaudothi(Graph G, int* danhdau, int soluong)
{
	FILE *f;
	int **checked = NULL;
	int tongnut,i,j;
	int output[MAX];
	f = fopen("test.dot","w+");
	checked = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		checked[i] = (int *)malloc(n * sizeof(int));
	for (i=0;i<n;i++) for (j=0;j<n;j++) checked[i][j]=0;	
		
	if(f == NULL)
   		{
   		printf("Error!");   
		exit(1);             
   		}
   	printf("\n");
   	fprintf(f,"graph dothi\n{");
   	for (i=0;i<soluong;i++)
   		{
   		fprintf(f,"%d [fillcolor=red, style=filled];\n",danhdau[i]);
   		printf("%d [fillcolor=red, style=filled];\n",danhdau[i]);
   		}
   	JRB iter;
    	jrb_traverse(iter, G.vertices)
    		{
    		//printf("xet toi nut %d\n",jval_i(iter->key));

        	tongnut=outdegree(G,jval_i(iter->key),output);
        	if (tongnut==0) fprintf(f,"%d\n",jval_i(iter->key));
        	for (i=0;i<tongnut;i++)
        		if (checked[jval_i(iter->key)][output[i]]==0)
        		{
        		checked[jval_i(iter->key)][output[i]]=1;
        		checked[output[i]][jval_i(iter->key)]=1;
        		fprintf(f,"%d -- %d\n",jval_i(iter->key),output[i]);
        		printf("%d -- %d\n",jval_i(iter->key),output[i]);
        		}
        	}
   	
   	fprintf(f,"}"); 
	for (i = 0; i < n; i++)
	{
	    	free(checked[i]);
	}
	free(checked);
}
void danhdaudothicohuong(Graph G, int* danhdau, int soluong)
{
	FILE *f;
	int **checked = NULL;
	int tongnut,i,j;
	int output[MAX];
	f = fopen("test.dot","w+");
	checked = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		checked[i] = (int *)malloc(n * sizeof(int));
	for (i=0;i<n;i++) for (j=0;j<n;j++) checked[i][j]=0;	
		
	if(f == NULL)
   		{
   		printf("Error!");   
		exit(1);             
   		}
   	printf("\n");
   	fprintf(f,"digraph dothi\n{");
   	for (i=0;i<soluong;i++)
   		{
   		fprintf(f,"%d [fillcolor=red, style=filled];\n",danhdau[i]);
   		printf("%d [fillcolor=red, style=filled];\n",danhdau[i]);
   		}
   	JRB iter;
    	jrb_traverse(iter, G.vertices)
    		{
    		//printf("xet toi nut %d\n",jval_i(iter->key));

        	tongnut=outdegree(G,jval_i(iter->key),output);
        	if (tongnut==0) fprintf(f,"%d\n",jval_i(iter->key));
        	for (i=0;i<tongnut;i++)
        		if (checked[jval_i(iter->key)][output[i]]==0)
        		{
        		checked[jval_i(iter->key)][output[i]]=1;
        		checked[output[i]][jval_i(iter->key)]=1;
        		fprintf(f,"%d -> %d\n",jval_i(iter->key),output[i]);
        		printf("%d -> %d\n",jval_i(iter->key),output[i]);
        		}
        	}
   	
   	fprintf(f,"}"); 
	for (i = 0; i < n; i++)
	{
	    	free(checked[i]);
	}
	free(checked);
}
void Softing()
	{
	int i,j;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
			if(nodelv[i]<nodelv[j])
				{
				hoanvi(&nodelv[i],&nodelv[j]);
				hoanvi(&node[i],&node[j]);
				}
	}
int CheckCl(int clused[],int somau,int cl)
	{
	int i;
	for(i=0;i<somau;i++)
		{
		printf("So sanh voi mau %d\n", clused[i]);
		if(cl==clused[i])
			{
			printf("Da co mau nay\n");
			return 1;
			}
		}
	return 0;
	}
int PickCl(int g[],int l)
	{
	int mau=0;
	do
	{	
		if(CheckCl(g,l,mau)==0)
			{
			return mau;
			break;	
			}
		else
			mau++;
	}while(1);
	}
void Coloring()
	{
	int i,j,t,z;
	int cl=0;  //mau dau tien = 0
	int nodecl[MAX], clused[MAX],nodeused[MAX]; //nodecl: mau cua node, clused: mau da su dung, nodeused: node da danh
	int k, l, tongsomau;
	i=t=l=0;
	
	j=1;
	nodecl[node[0]]=cl;
	printf("Not dau tien la %d co mau la %d\n",node[0],nodecl[node[0]]);
	nodeused[0]=node[i];
	printf("Not duoc danh dau la not %d co mau la %d\n",node[0],nodecl[node[0]]);
	do
	{
	printf("Dang xet nut %d\n",node[j]);
	for(int z=0;z<=l;z++)         // (z se chay tu 0 -> l, voi l la so node da check)
		{
		printf("Dang xet nut %d voi cac nut con, hien la nut %d\n",node[j],nodeused[z]);
		if(a[node[j]][nodeused[z]]==1)   //neu phat hien giua node da check va node j dang xet co noi voi nhau
		{
		
		printf("Phat hien ket noi voi nhau\n");	
		clused[t++]=nodecl[nodeused[z]];  //thi mau hien tai can dung se phai = mau cua cai not bi trung do +1 (phai khac)
		printf("Mau cua nut %d bi danh dau them mau %d\n",node[j],nodecl[nodeused[z]]); 
		}
		else printf("Khong trung\n");
		}
		nodecl[node[j]]=PickCl(clused,t);   //bay gio se to mau cho node j bang ham PickCl
		printf("Nut %d duoc to mau %d\n",node[j],nodecl[node[j]]);
		l++; //l tang len
		nodeused[l]=node[j];  //node j bi danh dau
		printf("Not %d bi danh dau da dung\n",node[j]);
		j++;  //j tang len
		t=0;  //mau lai ve ban dau
	}while(j<n);   //thuc hien cho den khi nut dang can xet = gia tri n
	for (i=0;i<n;i++)
		{
		printf("%d ",nodelv[i]);
		}
		printf("\n");
	for (i=0;i<n;i++)
		{
		printf("%d ",node[i]);
		}
		printf("\n");
	for (i=0;i<n;i++)
		{
		printf("%d ",nodecl[i]);
		}
		printf("\n");
	for (i=0;i<n;i++)
		{
		printf("%d ",clused[i]);
		}
		printf("\n");
	for (i=0;i<n;i++)
		{
		printf("%d ",nodeused[i]);
		}
		printf("\n");
	FILE *fptr;
	fptr = fopen("test.dot","w+");
	if(fptr == NULL)
   		{
   		printf("Error!");   
		exit(1);             
   		}
   	tongsomau=nodecl[0];
   	for (i=1;i<n;i++) 
   		if (tongsomau<nodecl[i]) tongsomau=nodecl[i];
   	printf("So mau da su dung la: %d\n",tongsomau+1);
        
        fprintf(fptr,"graph dothi\n{\n");
	int color;
	int distance=10000/(tongsomau+1);
	printf("distance la: %d\n",distance);
	char tmp[10];
	char p[100];
	for (i=n-1;i>=0;i--)
		{
		strcpy(p,"");
		fprintf(fptr,"%d ",i);
		fprintf(fptr,"[fillcolor=");
		
		color=10000-(nodecl[i]*distance);
		sprintf(tmp, "%d", color);
		
		printf("Mau cua %d: %d %d %d\n",i,color, nodecl[i],distance);
		strcat(p,"\"0.");
		strcat(p,tmp);
		strcat(p,",0.5,0.5\", style=filled];\n");
		fprintf(fptr,"%s",p);
		}
	for(i=0;i<n;i++)
		for (j=i; j<n; j++) 
		 	if (a[i][j]==1) 
				fprintf(fptr,"%d -- %d;\n",i,j);
	fprintf(fptr,"}\n");       
        fclose(fptr);
	}

