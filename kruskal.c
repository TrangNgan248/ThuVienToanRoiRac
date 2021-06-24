#include <stdio.h>

typedef struct Edge{
	int u, v, w;
}edge;

int n, m, D = 0;

edge add_edge(int u, int v, int w){
	edge temp;
	temp.u = u; //dinh dau 
	temp.v = v; //dinh cuoi
	temp.w = w; //trong so
	return temp;
}

void readFile(FILE *fin, edge edges[]){
	int i = 0;
	while(feof(fin)==0){
		fscanf(fin, "%d %d %d\n", &edges[i].u, &edges[i].v, &edges[i].w);
		i++;
	}
}

void kruskal(int parent[],edge edges[], edge T[])  
	{ 
	int v;
	int t = 0;
	for(v=0;v<n;v++){   //cho tat ca cha cua cac nut la chinh no
		parent[v] = v; 
	}
	int e;                 
	for(e=0;e<m;e++){   //trong khi e < tong cac canh (dang xet tung canh 1)
		if(parent[edges[e].u]!=parent[edges[e].v]){  //cha cua nut u  != cha cua nut v          --- edges[e]: canh thu e.   edges[e].u: la dinh dau.  parent[edges[e].u]
			D+=edges[e].w; //tim duoc la chac chan no luon
			T[t] = add_edge(edges[e].u, edges[e].v, edges[e].w);  //them vao cay
			t++; //tang thu tu
			int old_par = parent[edges[e].u];  
			int new_par = parent[edges[e].v]; 
			for(v=0;v<n;v++){   //chay het tap dinh
				if(parent[v]==old_par)  //neu cha cua 1 dinh bat ky == cha cu
				{
					parent[v]=new_par; //doi thanh cha moi
				}
			}
		}
	}

}


void swap(edge *a, edge *b){
    int u = a->u;
    a->u=b->u;
    b->u=u;
    u = a->v;
    a->v=b->v;
    b->v=u;
    u = a->w;
    a->w=b->w;
    b->w=u;
}
int partition(edge edges[], int hight, int low){
    int pivot = edges[hight].w;
    int left = low;
    int right = hight - 1;
    while(1){
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

int main(){
	FILE *fin = fopen("inputKruskal.txt", "r");
	fscanf(fin, "%d %d\n", &n, &m);  //m la so canh, n so dinh
	edge edges[m];//tap canh cua do thi
	edge T[m]; //luu cay
	int parent[n];
	int i;
	readFile(fin, edges); //ra duoc tap canh luon
	quickSort(edges, m-1, 0); //sap xep xong
	for(i=0;i<m;i++){
		printf("%d %d %d\n", edges[i].u, edges[i].v, edges[i].w); //in ra thu tu sau khi da sap xep
	}
	kruskal(parent, edges, T); 
	printf("Tong trong so la: %d\n", D);
	printf("Cac canh trong MST la:\n");
	for(i=0;i<n-1;i++){
		printf("%d-%d\n", T[i].u,T[i].v);
	}


}
