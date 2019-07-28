#include "assignments/dg/graph.h"

template<typename N, typename E>
gdwg::Graph<N, E>::Graph() noexcept : nodes_{} {}

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator begin,
                         typename std::vector<N>::const_iterator end) noexcept {
  //  int size = std::distance(begin, end);

  for (; begin != end; ++begin) {
    InsertNode(*begin);  // if is duplicate value, InsertNode() will ignore it
  }
}

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>, std::allocator<std::tuple<N, N, E>>>::const_iterator
    begin,
    typename std::vector<std::tuple<N, N, E>, std::allocator<std::tuple<N, N, E>>>::const_iterator
    end) noexcept {

  for (; begin != end; ++begin) {
    // trying to check existence of node, then decide to insert
    InsertNode(std::get<0>(*begin));
    InsertNode(std::get<1>(*begin));
    InsertEdge(std::get<0>(*begin), std::get<1>(*begin), std::get<2>(*begin));
  }
}

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(std::initializer_list<N> ls) noexcept {
  for (const auto& l : ls) {
    InsertNode(l);
  }
}

// TODO: check this new graph after deleting old
template<typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& old) noexcept : nodes_{old.nodes_} {}

// move constructor
template<typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& old) noexcept : nodes_{std::move(old.nodes_)} {}

// copy assignment
// TODO: check this
template<typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E>& old) noexcept {
  // check reference(identity)
  if (this != &old) {
//    Graph<N, E> tmp{old};
//    std::swap(tmp, *this);
    nodes_ = old.nodes_;
  }

  return *this;
}

// move assignment
template<typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E>&& old) noexcept {
  // check reference(identity)
  if (this != &old) {
    nodes_ = std::move(old.nodes_);
  }
  return *this;
}

/*
 * Methods
 */
// node successfully insert will return true,
// otherwise insert and return false
template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) noexcept {
  // if node isn't in the graph
  if (!IsNode(val)) {
    auto curr = std::make_shared<Node>(val);
    nodes_[curr]; // initialize empty edge set
  //    EdgeSet empty;
  //    nodes_[curr] = empty;
    return true;
  }
  return false;
}

// return false if already a edge exist
template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  // check is Node existed?
  if (!IsNode(src) || !IsNode(dst)) {
    // TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  // check already a edge exist
  if (IsConnected(src, dst)) return false;

  // insert edge
  auto src_ptr = std::make_shared<Node>(src);
  auto dst_ptr = std::make_shared<Node>(dst);
  auto src_entity = nodes_.find(src_ptr);
  auto dst_entity = nodes_.find(dst_ptr);

  std::weak_ptr<Node> dst_wp = dst_entity->first;
  src_entity->second.insert((std::make_pair(dst_wp, w)));

  return true;
}

// true if node exist, false otherwise
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) const {
  auto curr = std::make_shared<Node>(val);

  // find if graph map has this key
  if (nodes_.find(curr) != nodes_.end()) return true;

  return false;
}

// true if edge betwee two nodes, false otherwise
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) {
  // check is Node existed?
  if (!IsNode(src) || !IsNode(dst)) {
    // TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  // get EdgeSet from the entity
  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  auto predicate = [&dst](const EdgePair& edge) {
    auto dst_ptr = edge.first.lock();
    if (dst_ptr) {
      return (dst_ptr->value == dst);
    }
    return false;
  };  // predicate: check is such edge exist?

  // run through the EdgeSet to check if is connected?
  auto found = std::find_if(std::begin(edges), std::end(edges), predicate);
  if (found != std::end(edges)) {
    return true;
  }
  return false;
}

template<typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() {
  std::vector<N> result;

  for (const auto& node : nodes_) {
    result.push_back(node.first->value);
  }

  return result;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& val) {
  if (!IsNode(val))
    return false;

  for (auto begin = nodes_.begin(); begin != nodes_.end(); ++begin) {
    if (begin->first->value == val) {
      nodes_.erase(begin);
      break;
    }
  }

  return true;
}

template<typename N, typename E>
void gdwg::Graph<N, E>::Clear() {
  nodes_.clear();
}

template<typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {
  if (!IsNode(src)) {
    throw std::out_of_range(
        "Cannot call Graph::GetConnected if src doesn't exist in the graph");  // TODO:check error
    // info is src || the
    // actual value of src
  }

  std::vector<N> result;
  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  for (const auto& edge : edges) {
    auto edge_ptr = edge.first.lock();
    if (edge_ptr) {
      result.push_back(edge_ptr->value);
    }
  }

  return result;
}

template<typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::out_of_range("Cannot call Graph::GetWeights if src or dst node don't exist in the "
                            "graph");  // TODO: check error info is src or dst || the actual value
  }

  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  std::vector<E> result;
  if (IsConnected(src, dst)) {
    auto predicate = [&dst](const EdgePair& edge) {
      auto dst_ptr = edge.first.lock();
      if (dst_ptr) {
        return (dst_ptr->value == dst);
      }
      return false;
    };  // predicate: check is such edge exist?

    // find the edge
    auto found = std::find_if(std::begin(edges), std::end(edges), predicate);
    if (found != std::end(edges)) {
      result.push_back(found->second);
    }
  }  // TODO: I only do src -> dst right now
  // TODO: only src -> dst? || it can be dst -> src?
  return result;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
  if (!IsNode(src) || !IsNode(dst)) {
    return false;
  }

  if (!IsConnected(src, dst)) {
    return false;
  }

  // find the edge, and check the weight
  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  // predicate to check dst and weight
  auto predicate = [&dst, w](const EdgePair& edge) {
    auto edge_ptr = edge.first.lock();
    if (edge_ptr) {
      return ((edge_ptr->value == dst) && (edge.second == w));
    }
    return false;
  };

  // find the edge pair
  auto found = std::find_if(std::begin(edges), std::end(edges), predicate);
  if (found != std::end(edges)) {
    // if we found it, erase it
    edges.erase(found);
    nodes_[src_ptr] = edges;  // update edges set
  }

  // return false, since we didnt find the edge with that weight
  return false;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& oldData, const N& newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
  }

  // if newdate already exist, return false
  if (IsNode(newData)) {
    return false;
  }

  // just update the node->value to newData
  for (const auto& node : nodes_) {
    if (node.first->value == oldData) {
      node.first->value = newData;
      break;
    }
  }

  return true;
}

// remove all the incoming and outgoing edges for newData
// change the old_node->value to newData
template<typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error("Cannot call Graph::MergeReplace on old or new data if they don't "
                             "exist in the graph");  // TODO: need to change to the actual value ???
  }

  NodePtr old_ptr = std::make_shared<Node>(oldData);
  NodePtr new_ptr = std::make_shared<Node>(newData);
  // remove newData node
  nodes_.erase(new_ptr);

  // update old_node->value to newData
  for (const auto& node : nodes_) {
    if (node.first->value == oldData) {
      node.first->value = newData;
      break;
    }
  }  // TODO:check all the test case, and algorithm correct?
}

//template <typename N, typename E>
//typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() {
//  return gdwg::Graph<N, E>::const_iterator(nodes_.begin(), nodes_.begin(), nodes_.end());
//}
//
//template <typename N, typename E>
//typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() {
//  return gdwg::Graph<N, E>::const_iterator(nodes_.end(), nodes_.end(), nodes_.end());
//  // TODO:fix
//}
//
//template <typename N, typename E>
//typename gdwg::Graph<N, E>::const_iterator
//gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& e) {
//  for (const auto& edge_itr : *this) {
//    if ((std::get<0>(edge_itr) == src) && (std::get<1>(edge_itr) == dst) &&
//        (std::get<2>(edge_itr) == e)) {
//      return edge_itr;
//    }
//  }
//
//  // no find
//  return *this->cend();
//}
