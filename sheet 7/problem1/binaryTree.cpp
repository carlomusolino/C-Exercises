/** sample program for a fixed-depth binary tree
  */
#include <iostream>
#include <math.h>
using namespace std;

/**
  * class definition for a single node
  */
struct Node 
{
 Node* left;              // left child (pointer to)
 Node* right;             // right child
 int   myDepth;           // layer/depth
 int   myData;            // any data
//
 static int nInstances;   // # of class instances created
//
 Node()                   // overwriting default constructor
   {
   myData  = 0.0;
   left    = NULL;        // set them later
   right   = NULL;
   myDepth = -1;          // needs to be set 
   nInstances++;          // one more instance
   }
};
int Node::nInstances = 0; // initialization of class variable nNodes
                          // done using namespace operator
/**
  * generating the entire binary tree
  */
void generateTree(int depth, int nNodes, Node myTree[])
{
 int iNode = 0;                        // node counter
 int lastLayerStart = 0;               // starting of lastLayer
 myTree[0].myDepth  = 0;               // define root
//
 for (int iLayer=0; iLayer<(depth-1); iLayer++)
   {
   int lastLayerEnd = iNode + 1;
   printf("# %5d | %5d %5d\n", iLayer, lastLayerStart, lastLayerEnd);
   for (int iLast = lastLayerStart;       
            iLast < lastLayerEnd; iLast++)  // loop over last layer nodes
     {
     iNode++;                      
     myTree[iLast].left  = myTree + iNode;  // pointer to new left child
     iNode++;                     
     myTree[iLast].right = myTree + iNode;  // using pointer arithmetics
     myTree[iLast].left->myDepth  = iLayer + 1;   // set layer(depth)
     myTree[iLast].right->myDepth = iLayer + 1;   // of new modes
     }
   lastLayerStart = lastLayerEnd;
   } // end of loop over layers
// 
// output
//
 printf("# in generateTree() - number of instances generated\n");
 printf("# %5d %5d\n", Node::nInstances, nNodes);
// 
// testing
/*
 for (int iNodes=0; iNodes<nNodes; iNodes++)
   printf("%5d", myTree[iNodes].myDepth);
 printf("\n");
*/
}

/**
  * print the tree
  */
void printTree(int depth, int nNodes, Node myTree[])
{
 myTree[0].myDepth  = 0;               // define root
 printf("\n");
 printf("# the binary tree \n");
 printf("# layer depths \n");
 for (int iLayer=0; iLayer<depth; iLayer++)
   {
   printf("# %5d | ", iLayer);
   for (int iNodes=0; iNodes<nNodes; iNodes++)
     if (myTree[iNodes].myDepth==iLayer)
       printf("%5d", iNodes);
   printf("\n");
   }
//
}

/**
  *  entry point
  */
int main()
{
/** using lambda expression for total number of nodes */
 const int depth = 3;          
 const int nNodes = [depth](){int number = 0;
	                      for (int i=0; i<depth; i++)
                                 number += pow(2,i);
			      return number;
                              }();           // executed once
//
 printf("#  depth, nNodes : %8d %8d\n", depth, nNodes);
//
 auto allNodes = new Node[nNodes];       // with default constructor
 generateTree(depth, nNodes, allNodes);  // generate links (pointers)
 printTree(depth, nNodes, allNodes);     // print tree
//
// set data (example)
//
 for (int iNodes=0; iNodes<nNodes; iNodes++)
   allNodes[iNodes].myData = iNodes;
//
// transversing the tree (example)
//
 Node* currentNode = allNodes;    // start with root
 for (int iDepth = 0; iDepth < depth; iDepth++)
   {
   printf("%5d | %5d\n", iDepth, currentNode->myData);
   currentNode = (iDepth%2==0) ? currentNode->left
	                       : currentNode->right;
   }
 return 1;
}
