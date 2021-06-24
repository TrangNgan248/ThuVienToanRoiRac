#include "graph.h"

Graph createGraph()
{
    Graph G;
    G.edges = make_jrb(); //truong canh
    G.vertices = make_jrb(); //truong dinh
    return G;
}
void addVertex(Graph G, int id, char* name)
{
    if (!jrb_find_int(G.vertices, id))
        jrb_insert_int(G.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph G, int id)
{
    JRB node = jrb_find_int(G.vertices, id);
    if (!node)
        return "";
    return jval_s(node->val);
}

double getEdgeValue(Graph G, int v1, int v2)
{
    JRB node = jrb_find_int(G.edges, v1); 
    if (!node)
        return INFINITIVE_VALUE;
    node = jrb_find_int((JRB) jval_v(node->val), v2); 
    if (node)
        return jval_d(node->val); 
    else
        return INFINITIVE_VALUE;
}

void addEdge(Graph G, int v1, int v2, double weight)
{
    JRB node, tree;
    if (getEdgeValue(G, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(G.edges, v1);
        if(!node)
        {
            tree = make_jrb();
            jrb_insert_int(G.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

int outdegree(Graph G, int v, int* output)
{
    JRB node, tree;
    node = jrb_find_int(G.edges, v);
    if (!node)
        return 0;
    
    int total = 0;
    tree = (JRB) jval_v(node->val);
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

int indegree(Graph G, int v, int* output)
{
    JRB node, tree, iter;
    int total = 0;
    jrb_traverse(iter, G.vertices)
    {
        node = jrb_find_int(G.edges, jval_i(iter->key));
        if (node)
        {
            tree = (JRB) jval_v(node->val);
            if (jrb_find_int(tree, v)) 
            {
                output[total] = jval_i(node->key);
                total++;
            }
        }
    }
    return total;
}

void dropGraph(Graph G)
{
    JRB iter;
    if (G.vertices != NULL)
        jrb_free_tree(G.vertices);

    if (G.edges != NULL)
    {
        jrb_traverse(iter, G.edges)
            jrb_free_tree((JRB) jval_v(iter->val));
        jrb_free_tree(G.edges);
    }
}

double shortestPath(Graph G, int s, int t, int* path, int* length)
{
    int previous[MAX_ID]; 
    double distance[MAX_ID]; 
    int add[MAX_ID]; 
    Dllist queue = new_dllist();
    Dllist iter;
    Dllist node;
    int u;

    for (int i = 0; i < MAX_ID; ++i)
        distance[i] = INFINITIVE_VALUE;
    distance[s] = 0;
    memset(add, 0, sizeof(int)*MAX_ID);
    dll_append(queue, new_jval_i(s));
    add[s] = 1;

    while (!dll_empty(queue))
    {
        double min = INFINITIVE_VALUE;
        dll_traverse(iter, queue)
        {
            u = jval_i(iter->val);
            if (min > distance[u])
            {
                min = distance[u];
                node = iter;
            }
        }
        u = jval_i(node->val);
        dll_delete_node(node);

        if (u == t)
            break;	
        int n, v, w, output[MAX_PATH_LENGTH];
        n = outdegree(G, u, output);
        for (int i = 0; i < n; ++i)
        {
            v = output[i];
            w = getEdgeValue(G, u, v);
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }

            if (!add[v])
            {
                add[v] = 1;
                dll_append(queue, new_jval_i(v));
            }    
        }
    }
    int n, tmp[MAX_PATH_LENGTH];
    if(distance[t] != INFINITIVE_VALUE)
    {
        tmp[0] = t;
        n = 1;
        u = t;
        while(u != s)
        {
            u = previous[u];
            tmp[n] = u;
            n++;
        }
        
        *length = n;
        for(int i = n-1 ; i >= 0 ; --i)
            path[n-i-1] = tmp[i];
    }

    free_dllist(queue);
    return distance[t];
}
