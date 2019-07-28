#include <iostream>
#include <string>

#include "assignments/dg/graph.h"

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {
  gdwg::Graph<std::string, int> g;
//  gdwg::Graph<int, int> g1{1,2,3,4};
//  gdwg::Graph<int, int> g2{5,6,7,8};
//
//  gdwg::Graph<int, int> g3{g1};
//  gdwg::Graph<int, int> g4{std::move(g2)};
//
//  g4.InsertNode(1);
//  g4 = g1;

//
  //
////end of own test
//
  std::cout << "insert node 'how' succeed? => " << g.InsertNode("how") << "\n";
  std::cout << "insert node 'are' succeed? => " << g.InsertNode("are") << "\n";
  std::cout << "insert node 'you?' succeed? => " << g.InsertNode("you?") << "\n";
  std::cout << "insert node 'hello' succeed? => " << g.InsertNode("hello") << "\n";

  std::cout << "insert hello<-2->are succeed? => " << g.InsertEdge("hello", "are", 2) << "\n";
  std::cout << "insert how<-4->hello succeed? => " << g.InsertEdge("how", "hello", 4) << "\n";
  std::cout << "insert how<-1->you? succeed? => " << g.InsertEdge("how", "you?", 1) << "\n";
  std::cout << "insert are<-3->you? succeed? => " << g.InsertEdge("are", "you?", 3) << "\n";
  std::cout << g << '\n';

//  g.InsertEdge("a", "c", 8);
//  g.InsertEdge("a", "b", 5)
//  g.InsertNode("a")
//  g.InsertNode("b");
//  g.InsertNode("c");

//  auto iter = g.begin();
//  --iter;
//  std::cout << std::get<0>(*iter) << " -> " << std::get<1>(*iter) << " (weight " << std::get<2>(*iter) << ")\n";

//  gdwg::Graph<std::string, int> g2{g};
//
//  std::cout << g2 << "\n";

  // This is a structured binding.
  // https://en.cppreference.com/w/cpp/language/structured_binding
  // It allows you to unpack your tuple.
//  for (const auto& [from, to, weight] : g) {
//    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
//  }

}
