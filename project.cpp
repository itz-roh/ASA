#include <cstdio>
#include <iostream>
#include <vector>

typedef struct node{
    int n;
    int children[2];
    vector<int> parents;
};

int main()
{
    int u, v, vertices, edges, parent, child, last_node = 0;
    scanf("%d %d", u, v);
    scanf("%d %d", vertices, edges);
    node nodes[edges];
    int i = 0;
    while(i<edges){
        scanf("%d %d", parent, child);
        
    }
    if(u > last_node || v > last_node){
        cout << "0" << endl;
        return 0
    }


    return 0;
}
