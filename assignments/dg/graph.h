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
  //TODO: const correctness
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

      class const_iterator {
        public:
          using iterator_category = std::bidirectional_iterator_tag;
          using value_type = std::tuple<N, N, E>;
          using reference = std::tuple<const N&, const N&, const E&>;
          using difference_type = int;

          reference operator*() const {
            return {src_->value, dst_->value, *edge_};
          }

          const_iterator operator++(){

          }

          const_iterator operator++(int){

          }

        private:
          explicit const_iterator(Node& src, Node& dst, E& edge):src_{src}, dst_{dst},edge_{edge}{};
          Node* src_;
          Node* dst_;
          E* edge_;

          friend class Graph;
      };

      //constructor
      Graph() noexcept;
      Graph(
        typename std::vector<N>::const_iterator,
        typename std::vector<N>::const_iterator
      ) noexcept ;
      Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
            typename std::vector<std::tuple<N, N, E>>::const_iterator) noexcept ; //TODO:typename
      Graph(std::initializer_list<N>) noexcept;
      Graph(const gdwg::Graph<N, E>&) noexcept ;
      Graph(gdwg::Graph<N, E>&&) noexcept ;
      ~Graph() = default;

      //copy and move assignment
      Graph& operator=(const gdwg::Graph<N, E>&) noexcept;
      Graph& operator=(gdwg::Graph<N, E>&&) noexcept;

      //methods
      bool InsertNode(const N& val);
      bool InsertEdge(const N& src, const N& dst, const E& w);
      bool IsNode(const N& val);
      bool IsConnected(const N& src, const N& dst);
      std::vector<N> GetNodes();
      bool DeleteNode(const N&);
      void Clear();
      std::vector<N> GetConnected(const N& src);
      std::vector<E> GetWeights(const N& src, const N& dst);
      bool erase(const N& src, const N& dst, const E& w);
      bool Replace(const N& oldData, const N& newData);
      void MergeReplace(const N& oldData, const N& newData);
      //      const_iterator erase(const_iterator it);
//      const_iterator find(const N&, const N&, const E&);

      //iterator
      const_iterator cbegin();
      const_iterator cend();
    public:
      /*
       * friends implementation
       */
      //TODO:: == and !=
     friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g){
        for(const auto& node: g.nodes_){
          //write node value
          os << node.first->value << "(\n";

          //write edges
          for(const auto& edge: node.second){
            auto dst_ptr = edge.first.lock();
            if(dst_ptr){
              os << "  "<< dst_ptr->value << " | " << edge.second<< '\n';
            }
          }

          os << ")\n";
        }

        return os;
      }

    private:
      std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>> nodes_;
  };

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
