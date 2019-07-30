#include <iostream>
#include <string>

#include "assignments/dg/graph.h"
#include <cassert>

// Note: At the moment, there is no client.sampleout. Please do your own testing

int main() {


  // ========================== test constructor/assignment ========================
  gdwg::Graph<std::string, int> g;

  std::cout << "insert node 'how' succeed? => " << g.InsertNode("how") << "\n";
  std::cout << "insert node 'are' succeed? => " << g.InsertNode("are") << "\n";
  std::cout << "insert node 'you?' succeed? => " << g.InsertNode("you?") << "\n";
  std::cout << "insert node 'hello' succeed? => " << g.InsertNode("hello") << "\n";

  std::cout << "insert hello<-2->are succeed? => " << g.InsertEdge("hello", "are", 2) << "\n";
  std::cout << "insert how<-4->hello succeed? => " << g.InsertEdge("how", "hello", 4) << "\n";
  std::cout << "insert how<-1->you? succeed? => " << g.InsertEdge("how", "you?", 1) << "\n";
  std::cout << "insert are<-3->you? succeed? => " << g.InsertEdge("are", "you?", 3) << "\n";
  std::cout << g << '\n';

  g.InsertNode("a");
  g.InsertNode("b");
  g.InsertNode("c");
  g.InsertEdge("a", "c", 8);
  g.InsertEdge("a", "b", 5);

  std::cout << g << '\n';

  gdwg::Graph<int, int> g1{1,2,3,4};
  std::cout << ">>>>>>>g1\n" << g1 << "\n";
  gdwg::Graph<int, int> g2{5,6,7,8};
  gdwg::Graph<int, int> g3{g1};
  gdwg::Graph<int, int> g4{std::move(g2)};
  std::cout << ">>>>>>>g4\n" << g4 << "\n";
  assert(g2.GetNodes().size() == 0);
  // move assignment
  auto g5 = std::move(g1);
  std::cout << ">>>>>>>g5\n" << g5 << "\n";
  assert(g1.GetNodes().size() == 0);
  // copy assignment
  auto g6 = g4;
  std::cout << ">>>>>>>g6\n" << g6 << "\n";

  g4.InsertEdge(5, 6, 5);
  std::cout << ">>>>>>>g4\n" << g4 << "\n";
  std::cout << ">>>>>>>g6\n" << g6 << "\n";

  // TODO: interator constructor
  std::vector<std::string> v{"Hello", "how", "are", "you"};
  gdwg::Graph<std::string, double> g7 {v.begin(), v.end()};
  std::cout << ">>>>>>>g7\n" << g7 << "\n";

  std::string s1{"Hello"};
  std::string s2{"how"};
  std::string s3{"are"};
  auto e1 = std::make_tuple(s1, s2, 5.4);
  auto e2 = std::make_tuple(s2, s3, 7.6);
  auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
  gdwg::Graph<std::string, double> g8 {e.begin(), e.end()};
  std::cout << ">>>>>>>g8\n" << g8 << "\n";

  // ========================== test method ========================
  g8.DeleteNode("how");
  std::cout << ">>>>>>>g8\n" << g8 << "\n";
  g.DeleteNode("how");
  g.DeleteNode("hello");
  std::cout << ">>>>>>>g\n" << g << "\n";

  g4.Clear();
  std::cout << ">>>>>>>g4\n" << g4 << "\n";

  for (const auto& it : g.GetConnected("a")) {
    std::cout << it << "\n";
  }

  std::cout << "\nthe weight betwee a and boolin g\n";
  for (const auto& it : g.GetWeights("a", "b")) {
    std::cout << it << "\n";
  }

  // TODO: replace and merge replace
  auto e3 = std::make_tuple("A", "B", 5);
  auto e4 = std::make_tuple("A", "C", 6);
  auto e5 = std::make_tuple("A", "D", 7);
  auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e3, e4, e5};
  gdwg::Graph<std::string, double> g_mergeReplace {v_tmp.begin(), v_tmp.end()};
  g_mergeReplace.InsertEdge("C", "B", 10);
  g_mergeReplace.InsertEdge("B", "D", 1);
  g_mergeReplace.InsertEdge("D", "A", 10);
  g_mergeReplace.InsertEdge("A", "A", 10);
  std::cout << ">>>>>>>g_mergeReplace\n" << g_mergeReplace << "\n";
  g_mergeReplace.MergeReplace("A", "B");
  std::cout << ">>>>>>>g_mergeReplace\n" << g_mergeReplace << "\n";

//  auto iter = g.begin();
//  --iter;
//  std::cout << std::get<0>(*iter) << " -> " << std::get<1>(*iter) << " (weight " << std::get<2>(*iter) << ")\n";

  // This is a structured binding.
  // https://en.cppreference.com/w/cpp/language/structured_binding
  // It allows you to unpack your tuple.
//  for (const auto& [from, to, weight] : g) {
//    std::cout << from << " -> " << to << " (weight " << weight << ")\n";
//  }

}
