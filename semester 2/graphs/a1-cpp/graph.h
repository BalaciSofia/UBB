#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
class Graph {
private:
   std::map<int,std::vector<int>> d_in;
   std::map<int,std::vector<int>> d_out;
   std::map<std::pair<int,int>,int> cost;
public:
   Graph() = default;
   Graph(int v);
   Graph(std::vector<int> v);
   Graph(std::map<int,std::vector<int>> in,std::map<int,std::vector<int>> out,std::map<std::pair<int,int>,int> costs);
   ~Graph() = default;

   int Number_of_Vertices();
   std::vector<int> Parse_Vertices();
   bool Valid_Vertex(int v);
   bool Is_Edge(int x, int y);
   std::pair<int, int> InOut_Degree(int x);
   std::vector<int> Parse_Out(int x);
   std::vector<int> Parse_In(int y);
   int Get_Cost(int v1, int v2);
   void Update_Cost(int v1, int v2, int cost);
   void Append_Edge(int x, int y, int c);
   void Delete_Edge(int x, int y);
   void Append_Vertex(int x);
   void Delete_Vertex(int x);
   void Print_Graph();
   std::map<int,std::vector<int>> get_d_out();
   Graph Copy_Graph() const;
};