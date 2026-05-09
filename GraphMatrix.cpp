#include "GraphMatrix.hpp"

GraphMatrix::GraphMatrix(int numV, GType type) {
    // TODO
    v = numV;                           // save how many vertices the graph has
    e = 0;                              // we start with zero edges
    graphType = type;                   // save if its directed or undirected

    adjMatrix = new bool*[v];           // make an array with one slot per vertex (these will be the rows)

    for (int i = 0; i < v; i++){
        adjMatrix[i] = new bool[v];     // give each row v columns
        for (int j = 0; j < v; j++){
            adjMatrix[i][j] = false;    // set every spot to false meaning no edges exist yet
        }
    }
}

GraphMatrix::~GraphMatrix() {
    // TODO
    for (int i = 0; i < v; i++){
        delete[] adjMatrix[i];  // delete each row we created
    }
    delete[] adjMatrix;         // then delete the outer array that held all the rows
}

bool GraphMatrix::isEdge(int i, int j) const {
    // TODO
     if (i < 0 || i >= v || j < 0 || j >= v){
        return false;           // if the vertices dont exist in the graph, there cant be an edge
    }
    return adjMatrix[i][j];     // look up that spot in the matrix, true means edge exists false means it doesnt
}

ostream& GraphMatrix::print(ostream& os) const {
    os << "    ";
    for (int i = 0; i < v; i++) {
        os << i << ' ';
    }
    os << endl;

    os << "---";
    for (int i = 0; i < v; i++) {
        os << "--";
    }
    os << endl;

    for (int i = 0; i < v; i++) {
        os << i << " | ";
        for (int j = 0; j < v; j++) {
            os << adjMatrix[i][j] << ' ';
        }
        os << endl;
    }

    return os;
}

void GraphMatrix::toggleEdge(int i, int j) {
    // TODO
    if (i < 0 || i >= v || j < 0 || j >= v){
        return;                             // if either vertex doesnt exist, do nothing
    }
    adjMatrix[i][j] = !adjMatrix[i][j];     // flip it, if it was false make it true, if true make it false

    if (adjMatrix[i][j]) e++;               // we just turned it on so edge count goes up
    else                 e--;               // we just turned it off so edge count goes down

    if (graphType == UNDIRECTED && i != j){
        adjMatrix[j][i] = adjMatrix[i][j];  // undirected means the edge goes both ways so mirror it on the other side
    }
}
