#include <iostream>
#include <vector>

using namespace std;

struct node{
    bool tree = false;
    vector<int> parents;
    vector<int> children;
};

int main()
{
    int u, v, vertices, edges, parent, child;
    scanf("%d %d", &u, &v);
    scanf("%d %d", &vertices, &edges);
    node nodes[vertices];
    int i = 0;
    while(i<edges){
        scanf("%d %d", &parent, &child);

        node c_vertex = nodes[child-1];

        if(c_vertex.tree == false){
            c_vertex.tree = true;
            if(c_vertex.parents.size() == 2){
                cout << "0" << endl;
                return 0;
            }
            c_vertex.parents.push_back(parent);
        } else {
            if(c_vertex.parents.size() == 2){
                cout << "0" << endl;
                return 0;
            }
            c_vertex.parents.push_back(parent);
        }
        printf("%d %ld\n", child, c_vertex.parents.size());
        
        node p_vertex = nodes[parent-1];

        if(p_vertex.tree == false){
            p_vertex.tree = true;
            p_vertex.children.push_back(child);
        } else {
            p_vertex.children.push_back(child);
        }
    i++;
    }
    if(nodes[u-1].tree == false || nodes[v-1].tree == false )
        cout << "-" << endl;
    

    return 0;
}
