
#include "assignments/dg/graph.h"

template<typename N, typename E>
gdwg::Graph<N, E>::Graph() noexcept :nodes_{} {}

template<typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator begin, typename std::vector<N>::const_iterator end){
//  int size = std::distance(begin, end);

  for(;begin != end; ++begin){
    InsertNode(*begin); // TODO: so we ignore duplicate value,
                        // but if we care duplicate value, put if_else
  }
}


template<typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>,
                                     std::allocator<std::tuple<N, N, E>>>::const_iterator,
                         typename std::vector<std::tuple<N, N, E>,
                                     std::allocator<std::tuple<N,
                                                               N,
                                                               E>>>::const_iterator) noexcept {

  //TODO
}

//methods
template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
  if(!IsNode(val)){
    NodePtr curr = std::make_shared<Node>(val);
    EdgeSet empty;
    nodes_[curr] = empty; // initialize empty edge set
    return true;
  }

  return false;
}

//return false if already a edge exist
template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  //check is Node existed?
  if(!IsNode(src) || !IsNode(dst)){
    //TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  //check already a edge exist?
  if(IsConnected(src, dst)) return false;

  //insert edge
  NodePtr src_ptr = std::make_shared<Node>(src);
  NodePtr dst_ptr = std::make_shared<Node>(dst);

  auto src_entity = nodes_.find(src_ptr);
  auto dst_entity = nodes_.find(dst_ptr);

  std::weak_ptr<Node> dst_wp = dst_entity->first;
  src_entity->second.insert((std::make_pair(dst_wp, w)));
  return true;
}

//true if node exist, false otherwise
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {
  NodePtr curr = std::make_shared<Node>(val);
  if(nodes_.find(curr) != nodes_.end()) {
    return true; //true if node exist
  }
  return false; //false if node no exist
}

//true if connected, false otherwise
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) {
  //check is Node existed?
  if(!IsNode(src) || !IsNode(dst)){
    //TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  //get EdgeSet from the entity
  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  auto predicate = [&dst](const EdgePair& edge){
    auto dst_ptr = edge.first.lock();
    if(dst_ptr){
      return (dst_ptr->value == dst);
    }
    return false;
  };//predicate: check is such edge exist?

  //run through the EdgeSet to check if is connected?
  auto found = std::find_if(std::begin(edges), std::end(edges), predicate);
  if(found != std::end(edges)){
    return true;
  }
  return false;
}

