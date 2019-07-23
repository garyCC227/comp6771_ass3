
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
    nodes_[curr] = empty;
    return true;
  }

  return false;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  //TODO
  return false;
}

template<typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {
  NodePtr curr = std::make_shared<Node>(val);
  if(nodes_.find(curr) != nodes_.end()) {
    return true;
  }
  return false;
}
template<typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) {
  //check is Node existed?
  if(!IsNode(src) || !IsNode(dst)){
    //TODO:check exception message: print "src or dst" |  "src" or "dst"
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
  }

  NodePtr src_ptr = std::make_shared<Node>(src);
  EdgeSet edges = nodes_[src_ptr];

  auto predicate = [&dst](const EdgePair& edge){
    return (edge.first.lock()->value == dst);
  };//predicate: check is such edge exist?

  auto found = std::find_if(std::begin(edges), std::end(edges), predicate);
  if(found != std::end(edges)){
    return true;
  }
  return false;
}
