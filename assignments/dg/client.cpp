#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  gdwg::Graph<std::string, int> g;
  gdwg::Graph<int, int> g1{1,2,3,4};
  gdwg::Graph<int, int> g2{5,6,7,8};

  gdwg::Graph<int, int> g3{g1};
  gdwg::Graph<int, int> g4{std::move(g2)};

  g4.InsertNode(1);
  g4 = g1;
  std::cout << g4 << '\n';
  std::cout << g1 <<'\n';
  //own test
//
//  g.InsertNode("hello");
//  g.InsertNode("how");
//  g.InsertNode("are");
//
////end of own test
//
//  g.InsertNode("how");
//  g.InsertNode("are");
//  g.InsertNode("you?");
////
//  g.InsertEdge("hello", "how", 5);
//  g.InsertEdge("hello", "are", 8);
//  g.InsertEdge("hello", "are", 2);
//
//  g.InsertEdge("how", "you?", 1);
//  g.InsertEdge("how", "hello", 4);
//
//  g.InsertEdge("are", "you?", 3);


//  auto nodes = g.get_nodes_();
//  for(const auto& node: nodes){
//    std::cout << node.first->value << '\n';
//
//
//  }
//  std::cout << g << '\n';
//
//  gdwg::Graph<std::string, int> g2{g};
//
//  std::cout << g2 << "\n";
//
//  // This is a structured binding.
//  // https://en.cppreference.com/w/cpp/language/structured_binding
//  // It allows you to unpack your tuple.
//  for (const auto& [from, to, weight] : g) {
//    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
//  }
}
