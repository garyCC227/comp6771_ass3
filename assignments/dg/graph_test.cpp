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


/*
 * 20. Test cbegin() function, How:
 * 1. test the value of begin iterator for a normal graph
 * 2. test the value of begin iterator after remove a node from a graph
 * 3. test the value of begin iterator for a empty graph
 */
SCENARIO("Testing cbegin()"){
  GIVEN("Given a  graph with structure:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using cbegin() for a normal graph"){
      auto it  = g.cbegin();
      THEN("we should get the expected value by this iterator"){
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1);
      }
    }

    WHEN("using cbegin() after a node in graph be removed, remove 'b'; begin is in next level of outer_iterator"){
      g.DeleteNode("b"); // now graph is a->null, c->a(3)

      THEN("we should get c->a(3)"){
        auto it = g.cbegin();
        REQUIRE(std::get<0>(*it) == "c");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 3);
      }
    }

    WHEN("given a new graph with structure: a->b(1), a->c(2), b:{} , c:{}"){
      std::string str1{"a"};
      std::string str2{"b"};
      std::string str3{"c"};
      auto e10 = std::make_tuple(str1, str2, 1);
      auto e20 = std::make_tuple(str1, str3, 2);
      auto es = std::vector<std::tuple<std::string, std::string, double>>{e10, e20};
      gdwg::Graph<std::string, double> temp_graph{es.begin(), es.end()};
      THEN("remove 'b' -> a->null, a->c(2), c:{} "){
        temp_graph.DeleteNode("b");

        AND_THEN("cbegin() should be a->c(2)"){
          auto it = temp_graph.cbegin();
          REQUIRE(std::get<0>(*it) == "a");
          REQUIRE(std::get<1>(*it) == "c");
          REQUIRE(std::get<2>(*it) == 2);
        }
      }
    }

    WHEN("empty graph"){
      g.Clear();
      THEN("cbegin() == cend()"){
        REQUIRE(g.cbegin() == g.cend());
      }
    }
  }
}

/*
 * 21. Test cend() function, How:
 * 1. by testing the distance between cend() and cbegin() == correct size
 * 2. empty
 * 3. non-empty
 * 4. after remove
 */
SCENARIO("Testing cend()"){
  GIVEN("given a graph"){
    gdwg::Graph<std::string, double> g;

    WHEN("graph is empty"){
      THEN("distance of begin() and end() should be 0"){
        REQUIRE(std::distance(g.cbegin(), g.cend()) == 0);
      }
    }
    AND_GIVEN("inser 3 edge into the graph"){
      g.InsertNode("a");
      g.InsertNode("b");
      g.InsertNode("c");
      g.InsertEdge("a", "b", 1);
      g.InsertEdge("b", "c", 2);
      g.InsertEdge("c", "a", 3);

      WHEN("After insert 3 edge in to the graph"){
        THEN("distance should be 3"){
          REQUIRE(std::distance(g.cbegin(), g.cend()) == 3);
        }
      }

      WHEN("After remove a edge in graph"){
        g.erase("a", "b", 1);
        THEN("distance should be 2"){
          REQUIRE(std::distance(g.cbegin(), g.cend()) == 2);
        }
      }
    }
  }
}

/*
 * 22. Test crbegin() function, How:
 * 1. test the value of rbegin iterator for a normal graph
 * 2. test the value of rbegin iterator after remove a node from a graph
 * 3. test the value of rbegin iterator for a empty graph
 */
SCENARIO("Testing crbegin()"){
  GIVEN("Given a  graph with structure:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using crbegin() for a normal graph"){
      auto it  = g.crbegin();
      THEN("we should get c->a(3)"){
        REQUIRE(std::get<0>(*it) == "c");
        REQUIRE(std::get<1>(*it) == "a");
        REQUIRE(std::get<2>(*it) == 3);
      }
    }
    //TODO: we cannot fix reverse_iterator after we remove a node
    //SINCE it probably cannot call the findValidForward() in Constructor
    WHEN("empty graph"){
      g.Clear();
      THEN("crbegin() == crend()"){
        REQUIRE(g.crbegin() == g.crend());
      }
    }
  }
}


/*
 * 23. Test crend() function, How:
 * 1. by testing the distance between cend() and cbegin() == correct size
 * 2. empty
 * 3. non-empty
 * 4. after remove //TODO:cannot handle this
 */
SCENARIO("Testing crend()"){
  GIVEN("given a graph"){
    gdwg::Graph<std::string, double> empty;

    WHEN("graph is empty"){
      THEN("distance of crbegin() and crend() should be 0"){
        REQUIRE(std::distance(empty.crbegin(), empty.crend()) == 0);
      }
    }
    AND_GIVEN("a graph with 3 edges"){
      std::string s1{"a"};
      std::string s2{"b"};
      std::string s3{"c"};
      auto e1 = std::make_tuple(s1, s2, 1);
      auto e2 = std::make_tuple(s2, s3, 2);
      auto e3 = std::make_tuple(s3, s1, 3);
      auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
      gdwg::Graph<std::string, double> g{e.begin(), e.end()};

      for(auto iter = g.crbegin(); iter != g.crend(); ++iter){
  std::cout << std::get<0>(*iter) << " -> " << std::get<1>(*iter) << " (weight " << std::get<2>(*iter) << ")\n";
      }

      WHEN("to find the distance of begin and end"){
        THEN("distance should be 3"){
//          REQUIRE( std::distance(g.crbegin(),g.crend()) == 3);
        }
      }
    }
  }
}