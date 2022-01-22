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
    cout << "VERTEX: " << vertex << " COLOUR: " << nodes[vertex-1].colour << endl;
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
    for(auto iter: nodes[child-1].parents)  
        if(iter == parent)
            return true;
    return false;
}

void pre_processing(int u, int v){
    vector<int> aux1;
    vector<int> aux2;
    nodes[u-1].colour = 'r';
    aux1 = u_parents(aux1, u);
    aux2 = LCA(aux2, v);
    aux1.clear();
    for(auto parent: aux2)
        for(auto child: aux2)
            if(child!=parent && !is_parent(child, parent))
                aux1.push_back(parent);
            

    for(auto iter: aux1)
        cout << iter << ' ';
    cout << endl;
}


int dfs_visit(int vertex){ 
    
    nodes[vertex].colour = 'g';
    for (auto iter: nodes[vertex].parents){
        if(nodes[iter-1].colour == 'w'){
            if(dfs_visit(iter-1) == -1)
                return -1;
            }
        else if(nodes[iter-1].colour == 'g'){
            cout << "0" << endl;
            return -1;
        }
    }
    nodes[vertex].colour = 'b';
    
    return 0;
}

void dfs(int size){
    for (int i=0; i < size; i++){
        if(nodes[i].colour == 'w'){
            if (dfs_visit(i) == -1){
                break;
            }
        }
    }
}

int main()
{
    int u, v, vertices, edges, parent, child;
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
            printf("HERE 2");
            cout << "0" << endl;
            return 0;
        }
        nodes[child-1].parents.push_back(parent);
        i++;
    }
    if(nodes[u-1].parents.empty() && nodes[v-1].parents.empty()){
        cout << "-" << endl;
        return 0;
    }    
    dfs(vertices);
    pre_processing(u, v);
    return 0;
}
