
#include "assignments/dg/graph.h"

#include <iostream>
#include <algorithm>

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

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& old) noexcept : nodes_{old.nodes_} {}

// move constructor
template<typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& old) noexcept : nodes_{std::move(old.nodes_)} {}

// copy assignment
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
bool gdwg::Graph<N, E>::IsNode(const N& val) const noexcept{
  auto curr = std::make_shared<Node>(val);

  // find if graph map has this key
  if (nodes_.find(curr) != nodes_.end()) return true;

  return false;
}

// true if edge betwee two nodes, false otherwise
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst){
  // check is Node existed?
  if (!IsNode(src) || !IsNode(dst)) {
    // TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error(
        "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  // get EdgeSet from the entity
  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet& edges = nodes_[src_ptr]; 

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
std::vector<N> gdwg::Graph<N, E>::GetNodes() const noexcept{
  std::vector<N> result;

  for (const auto& node : nodes_) {
    result.push_back(node.first->value);
  }

  return result;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& val) noexcept{
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
void gdwg::Graph<N, E>::Clear() noexcept {
  nodes_.clear();
}

template<typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) const {
  if (!IsNode(src)) {
    throw std::out_of_range(
        "Cannot call Graph::GetConnected if src doesn't exist in the graph");  //TODO:error message
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
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) const{
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
  }
  return result;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) noexcept {
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

  // if newdata already exist, return false
  if (IsNode(newData)) {
    return false;
  }

  auto old_ptr = std::make_shared<Node>(oldData);
  auto new_ptr = std::make_shared<Node>(newData);

  // iterate through the map to find oldData(need to be reaplce)
  // and extract-insert to the newData
  for (auto& entry : nodes_) {
    for (auto& edge : entry.second) {
      if (edge.first.lock()->value == oldData) {
        // extract->change dest->insert back
        auto edgeHandler = entry.second.extract(edge);
        edgeHandler.value().first = new_ptr;
        entry.second.insert(std::move(edgeHandler));
      }
    }
  }
  // extract->change keys to newData->insert the entry back
  auto edgeSetHandler = nodes_.extract(old_ptr);
  edgeSetHandler.key() = new_ptr;
  nodes_.insert(std::move(edgeSetHandler));


  return true;
}

// remove all the incoming and outgoing edges for newData
// change the old_node->value to newData
template<typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error("Cannot call Graph::MergeReplace on old or new data if they don't "
                             "exist in the graph");  // TODO: need to change to the actual value ???`
  }

  auto old_ptr = std::make_shared<Node>(oldData);
  auto new_ptr = std::make_shared<Node>(newData);
  // copy of the edgeSet and append edges from new data to old
  auto new_edgeSet = nodes_[new_ptr];
  nodes_[old_ptr].insert(new_edgeSet.begin(), new_edgeSet.end());

  auto src_entity = nodes_.find(old_ptr);

  // iterate through the map to find oldData(need to be reaplce)
  // and extract-insert to the newData
  for (auto& entry : nodes_) {
    for (auto& edge : entry.second) {
      if (edge.first.lock()->value == newData) {
        // extract->change dest->insert back
        auto edgeHandler = entry.second.extract(edge);
        edgeHandler.value().first = src_entity->first;
        entry.second.insert(std::move(edgeHandler));
      }
    }
  }
  // remove to_be_replaced Entry
  nodes_.erase(new_ptr);
  // change to new value
  src_entity->first->value = newData;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin()  const{
  return gdwg::Graph<N, E>::const_iterator(nodes_.begin(), nodes_.begin(), nodes_.end());
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() const{
  return gdwg::Graph<N, E>::const_iterator(nodes_.end(), nodes_.begin(), nodes_.end());
}
//
template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& e) const noexcept {
  for(auto it = cbegin(); it != cend(); ++it){
    //compare src
    if (std::get<0>(*it) != src) continue;
    //compare dst
    if(std::get<1>(*it) != dst) continue;
    //compare weight
    if(std::get<2>(*it) == e) return it;
  }

  return cend();
}
template<typename N, typename E>
typename gdwg::Graph<N,E>::const_iterator gdwg::Graph<N, E>::erase(typename gdwg::Graph<N,E>::const_iterator it) noexcept {
  //for clean code, we using reference here
  const auto& src = std::get<0>(*it);
  const auto& dst = std::get<1>(*it);
  const auto& e = std::get<2>(*it);

  //iterator through the whole graph
  for(auto iter = cbegin(); iter != cend(); ++iter){
    //compare src
    if (std::get<0>(*it) != src) continue;
    //compare dst
    if(std::get<1>(*it) != dst) continue;
    //compare weight
    if(std::get<2>(*it) == e){
      //erase the edge by value
      erase(src, dst, e);
      //return the iterator after the one we just removed
      return (++it);
    }
  }

  //return here, mean we cannot find one to remove, so we just return cend()
  //e.g if someone pass a cend() into this function.
  return cend();
}
