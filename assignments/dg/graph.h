#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

namespace gdwg {

// Custom comparator
template<typename N>
struct CompareByNode {
  // comparator for Graph -> compare Node value
  bool operator()(const N& lhs, const N& rhs) const { return lhs->value < rhs->value; }
};
//
template<typename EP>
struct CompareByEdgePair {
  bool operator()(const EP& lhs, const EP& rhs) const {
    // comparator for EdgeSet -> compare Node value in each EdgePair
    return (std::get<0>(lhs).lock()->value < std::get<0>(rhs).lock()->value);
  }
};

// TODO: const correctness
template<typename N, typename E>
class Graph {
 private:
  // Vertex of graph
  struct Node {
    // constructor for Node
    Node(N value) : value{value} {};
    N value;
  };

 public:
  // type alias
  using EdgePair = std::pair<std::weak_ptr<Node>, E>;
  using EdgeSet = std::set<EdgePair, CompareByEdgePair<EdgePair>>;//,
  using NodePtr = std::shared_ptr<Node>;
/*

  class const_iterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N&, const N&, const E&>;
    using difference_type = int;

    reference operator*() const {
      return {outer_iterator_->first->value, inner_iterator_->first.lock()->value,
              inner_iterator_->second};
    }

    const_iterator operator++() {
      if (outer_iterator_ != outer_end_) {
        if (std::distance(inner_iterator_, std::end(outer_iterator_->second)) > 1) {

          std::advance(inner_iterator_, 1);
          for (; inner_iterator_ != std::end(outer_iterator_->second); ++inner_iterator_) {
            auto edge_ptr = inner_iterator_->first.lock();
            if (edge_ptr) {
              return *this;
            }
          }
        }
        // if reach end of edge set, go to next node
        ++outer_iterator_;
        FindValidEdgeForward();
      }
      return *this;
    }

    const_iterator operator++(int) {
      auto copy{*this};
      ++(*this);
      return copy;
    }
    */
/*
     * if begin--, then stay at begin
     * otherwise will -- for valid edge
     * ps: iterator in outside is always with valid edge. do not worry [from, invalid, invalid]
     * algorithm:
     *  if(outer_end):
     *    --outer first, then find a valid edge iterator to return,FinvaValidBackward()
     *  else:
     *    //-- to find prev valid edge in the curr edgeSet
     *    if(not at the begin of edgeSet):
     *        --iter;
     *        for(iter != begin of edgeSet):
     *            if(valid):
     *              return
     *             else:
     *              continue
     *        //reach the begin of edgeSet here
     *        check the begin element of this edgeSet:
     *          if (valid):
     *            return
     *
     *    else: //if at the begin of edgeSet
     *      if(outer == outer_begin): // so no more entity to check
     *        return;
     *      else: //still more entity to check
     *        --outer first, then find prev valid edge iterator, FinvaValidBackward()
     *//*

    const_iterator operator--() {
      // if begin == end all the time -> return segmentation fault
      if (outer_iterator_ == outer_end_) {
        --outer_iterator_;
        FindValidEdgeBackward();
      } else {
        if (std::distance(inner_iterator_, std::begin(outer_iterator_->second)) > 0) {
          std::advance(inner_iterator_, -1);
          for (; inner_iterator_ != std::begin(outer_iterator_->second); --inner_iterator_) {
            // stop here if we find a valid edge
            NodePtr ptr = inner_iterator_->first.lock();
            if (ptr) {
              return *this;
            }
          }
          // we still left the head element to check, if we reach here
          NodePtr ptr = inner_iterator_->first.lock();
          if (ptr) {
            return *this;
          }

        } else {
          if (outer_iterator_ != outer_begin_) {
            --outer_iterator_;
            FindValidEdgeBackward();
          }
        }
      }
      return *this;
    }

    const_iterator operator--(int) {
      auto copy{*this};
      --(*this);
      return copy;
    }
    // TODO: compare too less field. FIX
    friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
      bool outer_equal = (lhs.outer_iterator_ == rhs.outer_iterator_);
      bool inner_equal = (lhs.inner_iterator_ == rhs.inner_iterator_);
      return (outer_equal && inner_equal);
    }

    friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
      return !(lhs == rhs);
    }

   private:
    explicit const_iterator(
        typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator curr,
        typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator begin,
        typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator end)
      : outer_iterator_{curr}, outer_begin_{begin}, outer_end_{end} {
      FindValidEdgeForward();
    };

    bool FindValidEdgeForward() {
      for (; outer_iterator_ != outer_end_; ++outer_iterator_) {
        // find and set the first valid edge
        if (!outer_iterator_->second.empty()) {
          // check valid edge in this node? //since we might deleteNode
          for (inner_iterator_ = std::begin(outer_iterator_->second);
               inner_iterator_ != std::end(outer_iterator_->second); ++inner_iterator_) {
            // stop here if we find a valid edge
            NodePtr ptr = inner_iterator_->first.lock();
            if (ptr) {
              return true;
            }
          }
        }
        // if there is no valid edge, we will continue to next outer_iterator_
      }
      inner_iterator_ = std::end(outer_iterator_->second);
      return false;
    }

    */
/*
     * so we only have -- operator to call this function,
     * and Assumption: whenever we call this function -> outer_iterator != outer_begin && outer_end
     *//*

    bool FindValidEdgeBackward() {
      for (; outer_iterator_ != outer_begin_; --outer_iterator_) {
        // find and set the first valid edge
        if (!outer_iterator_->second.empty()) {
          // check valid edge in this node? //since we might deleteNode
          if (findValidInEdgeSetBackward()) {
            return true;
          }
        }
        // left outer.begin() to check, if we reach here
        // assign to last element of edge set,
        // now outer_iterator == begin
        if (!outer_iterator_->second.empty()) {
          if (findValidInEdgeSetBackward()) {
            return true;
          }
        }
      }
      // reach here, mean cannot find a valid edge from the whole nodes_ map
      return false;
    }

    */
/*
     * algorithm:
     *   assign to last element of this edge set
     *   for(!=begin):
     *      if(valid edege):
     *        return true;
     *   //reach here, we are at the begin of edeg set
     *   if(begin is valid edge):
     *      return true;
     *   return false;
     *//*

    bool findValidInEdgeSetBackward() {
      // assign to last element of edge set
      inner_iterator_ = std::end(outer_iterator_->second);
      std::advance(inner_iterator_, -1);
      for (; inner_iterator_ != std::begin(outer_iterator_->second); --inner_iterator_) {
        // stop here if we find a valid edge
        NodePtr ptr = inner_iterator_->first.lock();
        if (ptr) {
          return true;
        }
      }
      // we still left the head element to check, if we reach here
      NodePtr ptr = inner_iterator_->first.lock();
      if (ptr) {
        return true;
      }

      return false;
    }

    typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator outer_iterator_;
    typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator outer_begin_;
    typename std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>>::iterator outer_end_;
    typename EdgeSet::iterator inner_iterator_;

    friend class Graph;
  };  // end of iterator class
*/

//  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // constructor
  Graph() noexcept;
  Graph(typename std::vector<N>::const_iterator, typename std::vector<N>::const_iterator) noexcept;
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator) noexcept;
  Graph(std::initializer_list<N>) noexcept;
  Graph(const gdwg::Graph<N, E>&) noexcept;
  Graph(gdwg::Graph<N, E>&&) noexcept;
  ~Graph() = default;

  // copy and move assignment
  Graph& operator=(const gdwg::Graph<N, E>&) noexcept;
  Graph& operator=(gdwg::Graph<N, E>&&) noexcept;

  // methods
  bool InsertNode(const N& val) noexcept ;
  bool InsertEdge(const N& src, const N& dst, const E& w);
  bool IsNode(const N& val) const noexcept ;
  bool IsConnected(const N& src, const N& dst);
  std::vector<N> GetNodes() noexcept;
  bool DeleteNode(const N&) noexcept;
  void Clear() noexcept ;
  std::vector<N> GetConnected(const N& src);
  std::vector<E> GetWeights(const N& src, const N& dst);
  bool erase(const N& src, const N& dst, const E& w);
  bool Replace(const N& oldData, const N& newData);
  void MergeReplace(const N& oldData, const N& newData);
//  const_iterator erase(const_iterator it);  // TODO: what's invalid iterator?
//  const_iterator find(const N&, const N&, const E&);

  // iterator
//  const_iterator cbegin();
//  const_iterator cend();
//  const_iterator begin() { return cbegin(); };
//  const_iterator end() { return cend(); };
//  const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; }
//  const_reverse_iterator crend() const { return const_reverse_iterator{cbegin()}; }
//  const_reverse_iterator rbegin() const { return crbegin(); }
//  const_reverse_iterator rend() const { return crend(); }

  /*
   * friends implementation
   */
  friend bool operator==(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
    return (lhs.nodes_ == rhs.nodes_);
  }

  friend bool operator!=(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
    return !(lhs.nodes_ == rhs.nodes_);
  }

  friend std::ostream& operator<<(std::ostream& os, const gdwg::Graph<N, E>& g) {

    for (const auto& node : g.nodes_) {
      // write node value
      os << node.first->value << ": {";
      // write edges
      for (const auto& edge : node.second) {
        auto dst_ptr = edge.first.lock();
        if (dst_ptr) {
          os << " "  << node.first->value << "--" << edge.second << "-->" <<dst_ptr->value << " ";
        }
      }

      os << "}\n";
    }

    return os;
  }

 private:
  std::map<NodePtr, EdgeSet, CompareByNode<NodePtr>> nodes_; //
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
