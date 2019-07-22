#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <map>
#include <set>
#include <memory>
#include <utility>

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

      

      bool IsEmpty(){
        return nodes_.empty();
      }

    private:
      std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>> nodes_;
  };

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
