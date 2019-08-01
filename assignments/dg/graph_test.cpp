/*

  == Explanation and rational of testing ==
    this test will have the coverage:
    1. function coverage: all the functions will be called in this test
    2. branch/ statement/ expression coverage:
        I will cover all the possible input as much as I can, so guarantee that
        all the statement/expression/if_else branch would be implemented(in this function).
            such as
            (1) type (int, double, double/int)
            (2) weired input(e.g. 0-dimesnion vector)
            (3) special input that will call the if_else branch (or others expression/ statement)
            (4) normal input
            e.t.c
    and with 1. and 2. , we hopefully we can cover all the situations, then we will compare the my
    output with the expected output. Finally, if all match, we could say all my functions work
 properly.

    - for const vector:
        we will test for any const vector will have valid const memeber function to call.
        but some of methods both have setter and getter, then I will only test for getter,
        since Clion will tell us setter cannot be use, since we have const vector object.

 -------------------------------------------------------------------------------------------
                        Table of Content For Each Test Case
                    (To see detail, go the corresponding test case section)
 -------------------------------------------------------------------------------------------
 1. default constructor         6. copy assignment                          11. *= operator
 2. constructor                 7. move assignment                          12. /= operator
 3. range constructor           8. subscript operator(getter and modifier)  13. std::vector type
 conversion
 4. copy constructor            9. += operator                              14. std::list type
 conversion
 5. move constructor           10. -= operator                              15. at() methods
 ============================================================================================
 16.GetNumDimensions()         20. != operator                              24. / operator
 17.GetEuclideanNorm()         21. + operator                               25. << operator
 18.CreateUnitVector()         22. - operator                               26. const vector
 19. == operator               23. * operator
*/

#include "assignments/dg/graph.h"
#include "catch.h"

using Catch::Matchers::Contains;

/*
 *  1. Test constructors. How to test:
 *  How to test: Initiate constructors using all constructors available
 *
 *  method: Constructors
 */
SCENARIO("Testing default constructor") {
  GIVEN("We will initialise a Graph using the default constructor") {
    WHEN("when empty graph is intialised") {
      gdwg::Graph<int, int> g;
      THEN("-> then dimension should be 1, magnitudes[0] is 0")
        REQUIRE(g.GetNodes().size() == 0);
    }
  }

  GIVEN("We will initialise a Graph in using the given iterators") {
    WHEN("when graph is intialised") {
      std::vector<std::string> v{"1", "2", "3", "4"};
      gdwg::Graph<std::string, double> g {v.begin(), v.end()};
      THEN("-> then dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("The printed graph should be") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "1: {}\n"
                            "2: {}\n"
                            "3: {}\n"
                            "4: {}\n");
      }

    }
  }

  GIVEN("We will initialise a Graph using the list constructor using the given list") {
    WHEN("when empty graph is intialised") {
      gdwg::Graph<int, int> g{1,2,3,4};
      THEN("-> then dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("The printed graph should be") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "1: {}\n"
                            "2: {}\n"
                            "3: {}\n"
                            "4: {}\n");
      }
    }
  }

  GIVEN("We will initialise a Graph in  by using the given edge tuples") {
    WHEN("when empty graph is intialised") {
      THEN("-> then dimension should be 4") {
        auto e1 = std::make_tuple("A", "B", 5);
        auto e2 = std::make_tuple("A", "C", 6);
        auto e3 = std::make_tuple("A", "D", 7);

        auto v_tmp = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
        gdwg::Graph<std::string, double> g {v_tmp.begin(), v_tmp.end()};
          REQUIRE(g.GetNodes().size() == 4);
        AND_THEN("The printed graph should be") {
          std::ostringstream os;
          os << g;
          REQUIRE(os.str() == "A: { 5-->B  6-->C  7-->D }\n"
                              "B: {}\n"
                              "C: {}\n"
                              "D: {}\n");
        }
      }
    }
  }

  GIVEN("We will copy the Graph from a given graph") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1,2,3,4};
      THEN("-> the dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We copy to another graph") {
        gdwg::Graph<int, int> g1{g};
        THEN("-> the dimension should be 4") {
          REQUIRE(g.GetNodes().size() == g1.GetNodes().size());
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g;
            REQUIRE(os.str() == "1: {}\n"
                                "2: {}\n"
                                "3: {}\n"
                                "4: {}\n");
          }
        }
        AND_WHEN("Modify the new graph") {
          g1.Clear();
          THEN("the new node should be empty now") {
            REQUIRE(g1.GetNodes().size() == 0);
          }
          AND_THEN("should not affect the old") {
            REQUIRE(g.GetNodes().size() == 4);
          }
        }
      }
    }
  }

  GIVEN("We will move the Graph from a given graph") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1,2,3,4};
      THEN("-> the dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We move another graph") {
        gdwg::Graph<int, int> g1{std::move(g)};
        THEN("-> the new dimension should be 4") {
          REQUIRE(g1.GetNodes().size() == 4);
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g1;
            REQUIRE(os.str() == "1: {}\n"
                                "2: {}\n"
                                "3: {}\n"
                                "4: {}\n");
          }
        }
        AND_WHEN("New graph is constructed, the old graph should be empty") {
          REQUIRE(g.GetNodes().size() == 0);
        }
      }
    }
  }

  GIVEN("We will copy graph via = operator") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1,2,3,4};
      THEN("-> the dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We copy to another graph") {
        gdwg::Graph<int, int> g1 = g;
        THEN("-> the dimension should be 4") {
          REQUIRE(g.GetNodes().size() == g1.GetNodes().size());
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g;
            REQUIRE(os.str() == "1: {}\n"
                                "2: {}\n"
                                "3: {}\n"
                                "4: {}\n");
          }
        }
        AND_WHEN("Modify the new graph") {
          g1.Clear();
          THEN("the new node should be empty now") {
            REQUIRE(g1.GetNodes().size() == 0);
          }
          AND_THEN("should not affect the old") {
            REQUIRE(g.GetNodes().size() == 4);
          }
        }
      }
    }
  }

  GIVEN("We will move the Graph via = operator") {
    WHEN("when a graph is given") {
      gdwg::Graph<int, int> g{1,2,3,4};
      THEN("-> the dimension should be 4")
        REQUIRE(g.GetNodes().size() == 4);
      AND_THEN("We move another graph") {
        gdwg::Graph<int, int> g1 = std::move(g);
        THEN("-> the new dimension should be 4") {
          REQUIRE(g1.GetNodes().size() == 4);
          AND_THEN("The printed graph should be") {
            std::ostringstream os;
            os << g1;
            REQUIRE(os.str() == "1: {}\n"
                                "2: {}\n"
                                "3: {}\n"
                                "4: {}\n");
          }
        }
        AND_WHEN("New graph is constructed, the old graph should be empty") {
          REQUIRE(g.GetNodes().size() == 0);
        }
      }
    }
  }
}


/*
 *  2. Test the templates.
 *  How to test: Initialise graph of various data types, including int, double, string char
 *
 *  method: Constructors
 */
SCENARIO("Testing templates") {
  GIVEN("Graph of strings") {
    gdwg::Graph<std::string, std::string> g{"alpha", "beta", "charlie", "delta"};
    THEN("The dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "alpha: {}\n"
                          "beta: {}\n"
                          "charlie: {}\n"
                          "delta: {}\n");
    }
  }

  GIVEN("Graph of int") {
    gdwg::Graph<int, int> g{1, 3, 5, 7};
    THEN("The dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
        REQUIRE(os.str() == "1: {}\n"
                            "3: {}\n"
                            "5: {}\n"
                            "7: {}\n");
    }
  }

  GIVEN("Graph of double") {
    gdwg::Graph<double, double> g{1.1, 3.3, 5.5, 7.7};
    THEN("The dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
        REQUIRE(os.str() == "1.1: {}\n"
                            "3.3: {}\n"
                            "5.5: {}\n"
                            "7.7: {}\n");
    }
  }

  GIVEN("Graph of chars") {
    gdwg::Graph<char, char> g{'a', 'b', 'c', 'd'};
    THEN("The dimension should be 4")
      REQUIRE(g.GetNodes().size() == 4);
    THEN("The printed graph shoudl be") {
      std::ostringstream os;
      os << g;
        REQUIRE(os.str() == "a: {}\n"
                            "b: {}\n"
                            "c: {}\n"
                            "d: {}\n");
    }
  }
}

/*
 *  3. Test the property related methods of Graph.
 *  How to test: Retrieve information via getter method then
 *               check if the order and value and exception match
 *
 *  method: GetNodes(), GetConnected(const N&), GetWeights(const N&, const N&)
 *          IsNode(const N&)  IsConnected(const N&, const N&)
 */
SCENARIO("Getting graph info from provided functions") {

  GIVEN("A non empty graph") {
    gdwg::Graph<double, double> g{1.1, 5.5, 3.3, 7.7};

    THEN("the size should be 4") REQUIRE(g.GetNodes().size() == 4);

    WHEN("check nodes that is not part of graph") {
      bool predicate = g.IsNode(100);
      THEN("it should return false") {
        REQUIRE(predicate == false);
      }
    }
    AND_WHEN("check nodes that is part of graph") {
      THEN("it should return true") {
        REQUIRE(g.IsNode(1.1) == true);
      }
    }

    WHEN("We try to retrieve the nodes in the graph") {
      std::vector node = g.GetNodes();
      THEN("the size should be 4") REQUIRE(node.size() == 4);
      AND_THEN("The node value and oder matches") {
        REQUIRE(node.at(0) == 1.1);
        REQUIRE(node.at(1) == 3.3);
        REQUIRE(node.at(2) == 5.5);
        REQUIRE(node.at(3) == 7.7);
      }
    }
  }

  GIVEN("A non empty graph with edges") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    std::tuple e1 = std::make_tuple(s1, s2, 5.4);
    std::tuple e2 = std::make_tuple(s2, s3, 7.6);
    std::vector e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    THEN("Get the vertex from the graph") {
      std::vector node = g.GetNodes();
      AND_THEN("the size should be 3") REQUIRE(node.size() == 3);

      AND_THEN("The node value and order matches") {
        REQUIRE(node.at(0) == "Hello");
        REQUIRE(node.at(1) == "are");
        REQUIRE(node.at(2) == "how");
      }

      THEN("The output matches") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "Hello: { 5.4-->how }\n"
                            "are: {}\n"
                            "how: { 7.6-->are }\n");
      }
    }

    WHEN("Find the edges that doesn't exist") {
      std::string excp = "Cannot call Graph::GetConnected if src doesn't exist in the graph";
      REQUIRE_THROWS_AS(g.GetConnected("doesn't exist"), std::out_of_range);
      REQUIRE_THROWS_WITH(g.GetConnected("doesn't exist"), excp);
    }

    WHEN("Find the weights that doesn't exist") {
      std::string excp = "Cannot call Graph::GetWeights if src or dst node don't exist in the graph";
      WHEN("src doesn't exist") {
        REQUIRE_THROWS_AS(g.GetWeights("doesn't exist", "are"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("doesn't exist", "are"), excp);
      }
      WHEN("dest doesn't exist") {
        REQUIRE_THROWS_AS(g.GetWeights("are", "doesn't exist"), std::out_of_range);
        REQUIRE_THROWS_WITH(g.GetWeights("are", "doesn't exist"), excp);
      }
    }

    WHEN("Find the outgoing edges from how") {
      std::vector edges = g.GetConnected("how");
      AND_THEN("Only 1 edge with weight 7.6") {
        REQUIRE(edges.size() == 1);
        THEN("The returned edges should match the graph") {
          REQUIRE(edges.at(0) == "are");
        }
        WHEN("We try to find the weight between two vertex") {
          std::vector weights = g.GetWeights("how", "are");
          THEN("Only one weight and should match") {
            REQUIRE(weights.size() == 1);
            REQUIRE(weights.at(0) == 7.6);
          }

          std::string excp = "Cannot call Graph::IsConnected if src or dst node don't exist in the graph";
          WHEN("NODES that doesn't exist") {
            REQUIRE_THROWS_AS(g.IsConnected("doesn't exist", "are"), std::runtime_error);
            REQUIRE_THROWS_WITH(g.IsConnected("doesn't exist", "are"), excp);
          }

          WHEN("NODES that doesn't exist") {
            REQUIRE_THROWS_AS(g.IsConnected("are", "doesn't exist"), std::runtime_error);
            REQUIRE_THROWS_WITH(g.IsConnected("are", "doesn't exist"), excp);
          }

          AND_THEN("the two nodes should be connected") {
            REQUIRE(g.IsConnected("how", "are") == true);
          }
        }
      }
    }
  }

   GIVEN("A non empty graph that has node with multiple edges") {
    std::string s1{"Hello"};
    std::string s2{"how"};
    std::string s3{"are"};
    std::tuple e1 = std::make_tuple(s1, s2, 5.4);
    std::tuple e2 = std::make_tuple(s2, s3, 7.6);
    std::tuple e3 = std::make_tuple(s1, s3, 10);
    std::vector e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    THEN("The output matches") {
      std::ostringstream os;
      os << g;
      REQUIRE(os.str() == "Hello: { 10-->are  5.4-->how }\n"
                          "are: {}\n"
                          "how: { 7.6-->are }\n");
    }

    WHEN("Find the outgoing edges from Hello") {
      std::vector edges = g.GetConnected("Hello");
      AND_THEN("2 outgoing edge with weight 7.6 and 10") {
        REQUIRE(edges.size() == 2);
        THEN("The returned edges should have sorted and match the graph") {
          REQUIRE(edges.at(0) == "are");
          REQUIRE(edges.at(1) == "how");
        }

        WHEN("We try to find the weight between two vertex") {
          std::vector w1 = g.GetWeights("Hello", "are");
          std::vector w2 = g.GetWeights("Hello", "how");
          THEN("Only one weight and should match") {
            REQUIRE(w1.size() == 1);
            REQUIRE(w1.at(0) == 10);
            REQUIRE(w2.size() == 1);
            REQUIRE(w2.at(0) == 5.4);
          }
          AND_THEN("the two nodes should be connected") {
            REQUIRE(g.IsConnected("Hello", "are") == true);
            REQUIRE(g.IsConnected("Hello", "how") == true);
          }
        }
      }
    }
  }
}

/*
 *  4. Test graph modifications.
 *  How to test:
 *              Perform insertion and deletion operations of node and edges
 *              Check order
 *
 *  method: InsertNode(const N& val) InsertEdge(const N& src, const N& dst, const E& w)
 *          DeleteNode(const N&)
 *
 *  getting graph info from provided function
 */
SCENARIO("Modify graph from provided functions") {
  GIVEN("A empty graph") {
    gdwg::Graph<std::string, double> g{};
    WHEN("Insert nodes") {
      g.InsertNode("a");
      g.InsertNode("b");
      THEN("the graph should be updated") {
        std::ostringstream os;
        os << g;
        REQUIRE(os.str() == "a: {}\n"
                            "b: {}\n");
        REQUIRE(g.GetNodes().size() == 2);
      }
    }
  }
}

/*
 *  5. Test extended modifications.
 *  How to test:
 *              TODO:
 *  method: Replace(const N&, const N&)
 *          MergeReplace(const N&, const N&)
 */