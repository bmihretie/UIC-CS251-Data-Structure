/*graph.h*/

//
// << Birhanu Mihretie>>
//
// Basic graph class using a map of vertices. The project is using a struct 
// structure for effcient implmentation 
// 
//
// original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;


template<typename VertexT, typename WeightT>
class graph
{
private:
   
  // a structure of Edges 
  struct Edge
  {

	VertexT    to;
    WeightT    Weight;
	
	//  the operator that compares the struct edges and returns the boolean
	friend bool operator==(const Edge& e1, const Edge& e2){
	
		return e1.to == e2.to;
	
	
	}

  };
  
 
  map<VertexT,vector<Edge>> vertices;
  vector<VertexT>  Vertices;
  int numEdges;
 

  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns
  // true if found, otherwise returns false.
  //
  bool _LookupVertex(VertexT v) const
  {
    if(vertices.count(v) > 0) 
    
		return true;
		
    return false;
  }
  

public:

 
graph()
{
	numEdges = 0;
}
  

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const
  {
  
    return Vertices.size();
	
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const
  {
      return numEdges;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph  and if so
  // returns true.  If  the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v)
  {


    if (_LookupVertex(v) == true)
      return false;

    //
    // if we get here, vertex does not exist so insert.  Where
    //  
     vertices[v]; // adds the new vertex
	 Vertices.push_back(v); // push the vertex in the Vertex Vertices

    return true;
	
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight)
  {
    
	
    // we need to search the Vertices and edges and and check if it exists, if it doesn't return false
    if ((_LookupVertex(from) == false))  // not found:
		return false;
	 if ((_LookupVertex(to) == false))  // not found:
		return false;
	
	 // Here we will check using iterator to check the edges , 
	 // if the edge exists update the weight
	  Edge e;
	  e.to = to;
      e.wieght = weight;
	  auto it = find (vertices.at(from).begin(), vertices.at(from).end(), e);
	  if (it == vertices.at(from).end()){
		  Edge e = Edge();

		e.to = to;
		e.Weight = weight;
		vertices[from].push_back(e);

		numEdges++;
		}
      
	  else // insert new weight
		  it->Weight = weight;
	   

	 
	
    return true;
  }


  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const
  {
    //
    // we need to search the Vertices and find the position 
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    if (_LookupVertex(from) == false)  // not found:
		return false;
    if (_LookupVertex(to) == false)
		return false;
    
	for(size_t i = 0; i < vertices.at(from).size(); i++){
			if(vertices.at(from)[i].to == to){
				//Okay, the edge exists, return the weight via the reference parameter
				weight = vertices.at(from)[i].Weight;
				return true;
		}
	}	
		
    

    return false; //if we get here return false
	
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const
  {
    set<VertexT>  S;

    //
    // we need to search the Vertices if is exists if it doesnt exist return false
    //

    bool isExist = _LookupVertex(v);

    if (isExist == false)  // not found:
      return S;


    
	int size = vertices.at(v).size();
	
	for(int i = 0; i < size; i++){
		
		vector<Edge> t = vertices.at(v);
		S.insert(t[i].to); //insert it to set
	}	
		
    return S;
	
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const

  {
  
	
    return Vertices;  // returns a copy:
	
  }
  
// // using begin() to print map 
//     for (auto it = mymap.begin(); 
//          it != mymap.end(); ++it) 
//         cout << it->first << " = "
//              << it->second << '\n'; 
//   //
//   // dump
  // 
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) //const
  {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

   output << "**Num vertices: " << Vertices.size() << endl;
   output << "**Num edges: " << numEdges << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (size_t i = 0; i < Vertices.size() ; ++i)
    {
       
	   output << " " << i << ". " << Vertices.at(i) << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
	sort(Vertices.begin(),Vertices.end());
    for ( size_t vertexIndex = 0; vertexIndex < Vertices.size(); ++vertexIndex)
    {
    
	  output << Vertices.at(vertexIndex) << ": ";
	  
	  int size = vertices.at(Vertices.at(vertexIndex)).size();
      for (int edgeIndex = 0; edgeIndex < size; ++edgeIndex)
      {
       
          output << "(" << Vertices[vertexIndex] << ","
	
            << vertices[Vertices[vertexIndex]][edgeIndex].to << "," 
           << vertices[Vertices[vertexIndex]][edgeIndex].Weight
            << ") ";
    
      }

      output << endl;
    }

    output << "**************************************************" << endl;
  }

};
