#include <iostream>
#include <cmath>

using namespace std;

class Graph {
private:
      bool** adjacencyMatrix;
      int vertexCount;
public:
      Graph(int vertexCount) {
            this->vertexCount = vertexCount;
            adjacencyMatrix = new bool*[vertexCount];
            for (int i = 0; i < vertexCount; i++) {
                  adjacencyMatrix[i] = new bool[vertexCount];
                  for (int j = 0; j < vertexCount; j++)
                        adjacencyMatrix[i][j] = false;
            }
      }
 
      void addEdge(int i, int j) {
            if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
                  adjacencyMatrix[i][j] = true;
                  adjacencyMatrix[j][i] = true;
            }
      }
 
      void removeEdge(int i, int j) {
            if (i >= 0 && i < vertexCount && j >= 0 && j < vertexCount) {
                  adjacencyMatrix[i][j] = false;
                  adjacencyMatrix[j][i] = false;
            }
      }
 
     double findavgdegree()
     {
            //might have to replace vertexCount with something smaller if I am trying to limit stuff
            //if that is the case then make sure that findavgdegree gets an input/parameter
            int node_counter = 0;
            int degree_counter = 0;
            //cout << vertexCount << endl;
            for(int i = 0; i < vertexCount; i++)
            {
                  bool checker = false;
                  for(int j = 0; j < vertexCount; j++)
                  {
                        if(adjacencyMatrix[i][j] == true)
                        {
                              degree_counter++;
                              checker = true;

                        }
                  }

                  if(checker == true)
                  {
                        node_counter++;

                  }
            }

            //need to add precision to cap to two decimals
            double total;
            //cout << "DegreeC: " << degree_counter << endl;
            //cout << "NodeC: " << node_counter << endl;
            total = double(degree_counter)/double(node_counter);
            total = trunc(total*100)/100;
            return total;
     }
 
      ~Graph() {
            for (int i = 0; i < vertexCount; i++)
                  delete[] adjacencyMatrix[i];
            delete[] adjacencyMatrix;
      }
};