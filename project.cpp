#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node{
    vector<int> parents;
    char colour = 'w';
};

vector<node> nodes;

vector<int> LCA(vector<int> vertices, int vertex){
    if(nodes[vertex-1].parents.empty()){
        if(nodes[vertex-1].colour == 'r'){
            nodes[vertex-1].colour = 'y';
            vertices.push_back(vertex);
            }
        return vertices;
        }
    for(auto iter: nodes[vertex-1].parents){
        if(nodes[iter-1].colour == 'r'){
            nodes[iter-1].colour = 'y';
            vertices.push_back(iter);
            }
        vertices = LCA(vertices, iter);
    }
    return vertices;
}

vector<int> u_parents(vector<int> vertices, int vertex){
    if(nodes[vertex-1].parents.empty()){
        return vertices;
        }
    for(auto iter: nodes[vertex-1].parents){
        nodes[iter-1].colour = 'r';
        vertices.push_back(iter);
        vertices = u_parents(vertices, iter);
    }
    return vertices;
}



bool is_parent(int child, int parent){
    cout << "CHILD: " << child << " PARENT: " << parent;
    if(nodes[child-1].parents.empty())
        return false;
    for(auto iter: nodes[child-1].parents){  
        if(iter != parent){
            cout << "FALSE" << endl;
            if(is_parent(parent, iter) == false)
                return false;
            }
        if( iter == parent)
        {cout << "TRUE" << endl;
        return true;}
    }
    return false;
}

vector<int> pre_processing(int u, int v){
    vector<int> aux1;
    vector<int> aux2;
    nodes[u-1].colour = 'r';
    aux1 = u_parents(aux1, u);
    aux2 = LCA(aux2, v);
    aux1.clear();
    aux1.push_back(aux2[0]);
    for (int i = 1; i < (int)aux2.size(); i++)
        if (!is_parent(aux2[i-1], aux2[i]))
            aux1.push_back(aux2[i]);
    sort(aux1.begin(), aux1.end());
    return aux1;
}


int dfs_visit(int vertex){ 
    
    nodes[vertex].colour = 'g';
    for (auto iter: nodes[vertex].parents){
        if(nodes[iter-1].colour == 'w'){
            if(dfs_visit(iter-1) == -1)
                return -1;
            }
        else if(nodes[iter-1].colour == 'g'){
            return -1;
        }
    }
    nodes[vertex].colour = 'b';
    
    return 0;
}

int dfs(int size){
    for (int i=0; i < size; i++){
        if(nodes[i].colour == 'w'){
            if (dfs_visit(i) == -1){
                return -1;
            }
        }
    }
    return 0;
}

int main()
{
    int u, v, vertices, edges, parent, child;
    vector<int> res;
    if(scanf("%d %d", &u, &v)!=2)
        return -1;
    if(scanf("%d %d", &vertices, &edges)!=2)
        return -1;
    node vertex;
    for(int i = 0; i < vertices; i++)
        nodes.push_back(vertex);
    int i = 0;
    while(i<edges){
        if(scanf("%d %d", &parent, &child)!=2)
            return -1;
        
        if(nodes[child-1].parents.size() == 2){
            cout << "0" << endl;
            return 0;
        }
        nodes[child-1].parents.push_back(parent);
        i++;
    }
    if(dfs(vertices) == -1){
        cout << "0" << endl;
        return 0;}

    if(nodes[u-1].parents.empty() && nodes[v-1].parents.empty()){
        cout << "-" << endl;
        return 0;
    }
    
    if(is_parent(u, v)){
        cout << "HERE";
        cout << v;
        return 0;}
        
     if(is_parent(v, u)){
        cout << u;
        return 0; }   
    
    res = pre_processing(u, v);
    
    if(res.empty())
        cout << "-";
    else
        for(auto iter: res)
            cout << iter << ' ';

    return 0;
}
