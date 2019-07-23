#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <map>
#include <set>
#include <memory>
#include <utility>
#include <vector>
#include <tuple>
#include <algorithm>

namespace gdwg {

  //Custom comparator
  template<typename N>
  struct CompareByNode {
    bool operator()(const N& lhs, const N& rhs) {
      return lhs->value < rhs->value;
    }
  };// comparator for Graph -> compare Node value

  template <typename EP>
  struct CompareByEdgePair{
      bool operator()(const EP& lhs, const EP& rhs){
        return (std::get<0>(lhs).lock()->value < std::get<0>(rhs).lock()->value);
      }
  }; //comparator for EdgeSet -> compare Node value in each EdgePair
  //End of custom comparator

  //Graph implementation
  template<typename N, typename E>
  class Graph {
      // Node struct
    private:
      struct Node {
          Node(N value): value{value}{};
          N value;
      };

    public:
      //type alias
      using EdgePair = std::pair<std::weak_ptr<Node>, E>;
      using EdgeSet = std::set<EdgePair, CompareByEdgePair<EdgePair>>;
      using NodePtr = std::shared_ptr<Node>;

      class const_iterator {};

      //constructor
      Graph() noexcept;
      Graph(
        typename std::vector<N>::const_iterator,
        typename std::vector<N>::const_iterator
      );
      Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
            typename std::vector<std::tuple<N, N, E>>::const_iterator) noexcept ; //TODO
      
      //TODO:delete
      auto get_nodes_(){
        return nodes_;
      }

      //methods
      bool InsertNode(const N& val);
      bool InsertEdge(const N& src, const N& dst, const E& w);
      bool IsNode(const N& val);
      bool IsConnected(const N& src, const N& dst);

    private:
      std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>> nodes_;
  };

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
