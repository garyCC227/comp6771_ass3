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

 //Assume reverse_iterator works if const_iterator works.
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
      decltype(g) empty;
      THEN("cbegin() == cend()"){
        REQUIRE(empty.cbegin() == empty.cend());
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

    WHEN("using crbegin() after a node in graph be removed, remove 'c'; begin is in next level of outer_iterator"){
      g.DeleteNode("c"); // now graph is a->b(1), b->null

      THEN("we should get a->b(1)"){
        auto it = g.cbegin();
        REQUIRE(std::get<0>(*it) == "a");
        REQUIRE(std::get<1>(*it) == "b");
        REQUIRE(std::get<2>(*it) == 1);
      }
    }

    WHEN("given a new graph with structure: a:{}, b:{} , c->a(1), c->b(2)"){
      std::string str1{"a"};
      std::string str2{"b"};
      std::string str3{"c"};
      auto e10 = std::make_tuple(str3, str1, 1);
      auto e20 = std::make_tuple(str3, str2, 2);
      auto es = std::vector<std::tuple<std::string, std::string, double>>{e10, e20};
      gdwg::Graph<std::string, double> temp_graph{es.begin(), es.end()};
      THEN("remove 'b' -> a:{}, c->a(1), c->null(2) "){
        temp_graph.DeleteNode("b");

        AND_THEN("crbegin() should be c->a(1)"){
          auto it = temp_graph.crbegin();
          REQUIRE(std::get<0>(*it) == "c");
          REQUIRE(std::get<1>(*it) == "a");
          REQUIRE(std::get<2>(*it) == 1);
        }
      }
    }

    WHEN("empty graph"){
      decltype(g) empty;
      THEN("crbegin() == crend()"){
        REQUIRE(empty.crbegin() == empty.crend());
      }
    }
  }
}


/*
 * 23. Test crend() function, How:
 * 1. by testing the distance between cend() and cbegin() == correct size
 * 2. empty
 * 3. non-empty
 * 4. after remove
 */
SCENARIO("Testing crend()"){
  GIVEN("given a graph"){
    gdwg::Graph<std::string, double> g;

    WHEN("graph is empty"){
      THEN("distance of crbegin() and crend() should be 0"){
        REQUIRE(std::distance(g.crbegin(), g.crend()) == 0);
      }
    }

    AND_GIVEN("insert 3 edge into the graph"){
      g.InsertNode("a");
      g.InsertNode("b");
      g.InsertNode("c");
      g.InsertEdge("a", "b", 1);
      g.InsertEdge("b", "c", 2);
      g.InsertEdge("c", "a", 3);

      WHEN("After insert 3 edge in to the graph"){
        THEN("distance should be 3"){
          REQUIRE(std::distance(g.crbegin(), g.crend()) == 3);
        }
      }

      WHEN("After remove a edge in graph"){
        g.erase("a", "b", 1);
        THEN("distance should be 2"){
          REQUIRE(std::distance(g.crbegin(), g.crend()) == 2);
        }
      }
    }
  }
}

/*
 * 24.Test: const_iterator ++operator()
 *  1. loop through all to compare the src and edge value
 *  2. test postfix operator++ working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test ++end() still == end()

 */
SCENARIO("Test: const_iterator -> ++operator for const_iterator"){
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph"){
      THEN("the result should be the same"){
        auto edge = e.begin();
        for(auto it=g.cbegin(); it != g.cend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("testing postfix ++ operator"){
      auto it = g.begin();
      auto old = it++;
      THEN("it now is b->c(2), and old should be a->b(1)"){
        //check it
        REQUIRE("b"== std::get<0>(*it));
        REQUIRE("c" == std::get<1>(*it));
        REQUIRE(2 == std::get<2>(*it));

        //check old
        REQUIRE("a"== std::get<0>(*old));
        REQUIRE("b" == std::get<1>(*old));
        REQUIRE( 1 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b"){
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)"){
        auto edge = edges.begin();
        for(auto it=g.cbegin(); it != g.cend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("++end() is still end()"){
      auto it = g.cend();
      ++it;
      THEN("++it == end()"){
        REQUIRE(it == g.cend());
      }
    }


  }
}

/*
 * 25.Test: const_iterator --operator()
 *  1. loop through all , then compare the src and edge value
 *  2. test postfix operator-- working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test --begin() still == begin()

 */
SCENARIO("Test: const_iterator -> --operator"){
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph"){
      THEN("the result should be the same"){
        auto edge = e.end();
        auto it=g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.cbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("testing postfix -- operator"){
      auto it = g.begin();
      ++it; // second position
      auto old = it--;
      THEN("it now is a->b(1), and old should be b->c(2)"){

        REQUIRE("a"== std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(1 == std::get<2>(*it));

        //check old
        REQUIRE("b"== std::get<0>(*old));
        REQUIRE("c" == std::get<1>(*old));
        REQUIRE( 2 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b"){
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)"){
        auto edge = edges.end();
        auto it=g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.cbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("--begin() is still begin()"){
      auto it = g.cbegin();
      --it;
      THEN("--it == cbegin()"){
        REQUIRE(it == g.cbegin());
      }
    }
  }
}

/*
 * 26. test ++ and -- operator work properly
 * 1. ++ and -- randomly
 * 2. test with erase edge
 * 3. test with erase node
 */
SCENARIO("Test ++ and -- randomly, and ensure they work properly"){
  GIVEN("given a normal graph with mutiple edges. check comment for structure"){
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("end--, then ++"){
      auto it = g.cend();
      --it;
      THEN("it == c->b(8)"){
        REQUIRE("c" == std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(8 == std::get<2>(*it));
      }

      AND_WHEN("++it"){
        ++it;
        THEN("it == cend()"){
          REQUIRE(it == g.cend());
        }
      }
    }

    WHEN("loop through--"){
      THEN("check expected value"){
        auto edge = e.cend();
        auto it=g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.cbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("we want to loop through the whole graph by ++"){
      THEN("the result should be the same"){
        auto edge = e.begin();
        for(auto it=g.cbegin(); it != g.cend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    AND_WHEN("remove 'c', now graph is a->b(1), b->a(5)"){
      g.DeleteNode("c");
      auto new_edges = std::vector<std::tuple<std::string, std::string, double>>{e1, e5};
      THEN("loop through the whole graph by ++"){
        auto edge = new_edges.begin();
        for(auto it=g.cbegin(); it != g.cend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }

      THEN("-- loop through"){
        auto edge = new_edges.cend();
        auto it=g.cend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.cbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }
  }
}

/*
 * 27.Test: const_reverse_iterator ++operator()
 *  1. loop through all to compare the src and edge value
 *  2. test postfix operator++ working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test ++end() still == end()

 */
SCENARIO("Test: const_reverse_iterator -> ++operator for const_reverse_iterator"){
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph"){
      THEN("the result should be the same"){
        auto edge = e.crbegin();
        for(auto it=g.crbegin(); it != g.crend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("testing postfix ++ operator"){
      auto it = g.crbegin();
      auto old = it++;
      THEN("it now is b->c(2), and old should be c->a(3)"){
        //check it
        REQUIRE("b"== std::get<0>(*it));
        REQUIRE("c" == std::get<1>(*it));
        REQUIRE(2 == std::get<2>(*it));

        //check old
        REQUIRE("c"== std::get<0>(*old));
        REQUIRE("a" == std::get<1>(*old));
        REQUIRE( 3 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b"){
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)"){
        auto edge = edges.crbegin();
        for(auto it=g.crbegin(); it != g.crend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    WHEN("++crend() is still end()"){
      auto it = g.crend();
      ++it;
      THEN("++it == end()"){
        REQUIRE(it == g.crend());
      }
    }

  }
}

/*
 * 28.Test: const_reverse_iterator --operator()
 *  1. loop through all , then compare the src and edge value
 *  2. test postfix operator-- working correct
 *  3. after remove someone node from a graph, loop through and compare
 *  4. test --crbegin() still == crbegin()

 */
SCENARIO("Test: const_reverse_iterator -> --operator"){
  GIVEN("given a graph:a->b(1), b->c(2), c->a(3)"){
    std::string s1{"a"};
    std::string s2{"b"};
    std::string s3{"c"};
    auto e1 = std::make_tuple(s1, s2, 1);
    auto e2 = std::make_tuple(s2, s3, 2);
    auto e3 = std::make_tuple(s3, s1, 3);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("we want to loop through the whole graph"){
      THEN("the result should be the same"){
        auto edge = e.crend();
        auto it=g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.crbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("testing postfix -- operator"){
      auto it = g.crbegin();
      ++it; // second position
      auto old = it--;
      THEN("it now is c->a(3), and old should be b->c(2)"){

        REQUIRE("c"== std::get<0>(*it));
        REQUIRE("a" == std::get<1>(*it));
        REQUIRE(3 == std::get<2>(*it));

        //check old
        REQUIRE("b"== std::get<0>(*old));
        REQUIRE("c" == std::get<1>(*old));
        REQUIRE( 2 == std::get<2>(*old));
      }
    }

    WHEN("we want to loop through the whole graph after remove a node, remove a->b"){
      g.erase("a", "b", 1);
      auto edges = std::vector<std::tuple<std::string, std::string, double>>{e2, e3};
      THEN("graph now is b->a(2), c->a(3)"){
        auto edge = edges.crend();
        auto it=g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.crbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("--cbregin() is still crbegin()"){
      auto it = g.crbegin();
      --it;
      THEN("--it == cbegin()"){
        REQUIRE(it == g.crbegin());
      }
    }
  }
}


/*
 * 29. test ++ and -- operator work properly for const_reverse_iterator
 * 1. ++ and -- randomly
 * 2. test with erase edge
 * 3. test with erase node
 */
SCENARIO("Test ++ and -- randomly, and ensure they work properly for const_reverse_iterator"){
  GIVEN("given a normal graph with mutiple edges. check comment for structure"){
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("end--, then ++"){
      auto it = g.crend();
      --it;
      THEN("it == a->b(1)"){
        REQUIRE("a" == std::get<0>(*it));
        REQUIRE("b" == std::get<1>(*it));
        REQUIRE(1 == std::get<2>(*it));
      }

      AND_WHEN("++it"){
        ++it;
        THEN("it == crend()"){
          REQUIRE(it == g.crend());
        }
      }
    }

    WHEN("loop through--"){
      THEN("check expected value"){
        auto edge = e.crend();
        auto it=g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.crbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }

    WHEN("we want to loop through the whole graph by ++"){
      THEN("the result should be the same"){
        auto edge = e.crbegin();
        for(auto it=g.crbegin(); it != g.crend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }
    }

    AND_WHEN("remove 'c', now graph is a->b(1), b->a(5)"){
      g.DeleteNode("c");
      auto new_edges = std::vector<std::tuple<std::string, std::string, double>>{e1, e5};
      THEN("loop through the whole graph by ++"){
        auto edge = new_edges.crbegin();
        for(auto it=g.crbegin(); it != g.crend(); ++it){
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          ++edge;
        }
      }

      THEN("-- loop through"){
        auto edge = new_edges.crend();
        auto it=g.crend();
        std::advance(it, -1);
        std::advance(edge, -1);
        for(; it != g.crbegin(); --it){ // compare from last element to begin-1
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          --edge;
        }
        //compare begin element
        REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
        REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
        REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
      }
    }
  }
}

/*
 * 30. Testing == operator
 * 1. for const_iterator
 * 2. for const_reverse_iterator
 */
SCENARIO("Testing == operator"){
 GIVEN("given a graph with structure(check comments)"){
   /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using const_iterator and loop through to compare with begin()"){
      auto begin = g.cbegin();
      int i = 0;
      THEN("only the first one == begin(), others all !(it == begin())")
      for(auto it = g.cbegin(); it != g.cend();++it){
        if(i == 0){
          REQUIRE(begin == it);
        }else{
          REQUIRE(!(begin == it));
        }
        ++i;
      }
    }

    WHEN("using const_reverse_iterator and loop through to compare with rbegin()"){
      auto rbegin = g.crbegin();
      int i = 0;
      THEN("only the first one == rbegin(), others all !(it == rbegin())")
      for(auto it = g.crbegin(); it != g.crend();++it){
        if(i == 0){
          REQUIRE(rbegin == it);
        }else{
          REQUIRE(!(rbegin == it));
        }
        ++i;
      }
    }
 }
}

/*
 * 31. Testing != operator
 * 1. for const_iterator
 * 2. for const_reverse_iterator
 */
SCENARIO("Testing != operator"){
 GIVEN("given a graph with structure(check comments)"){
   /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("using const_iterator and loop through to compare with begin()"){
      auto begin = g.cbegin();
      int i = 0;
      THEN("only !(first one != begin()), others all (it != begin())")
      for(auto it = g.cbegin(); it != g.cend();++it){
        if(i == 0){
          REQUIRE(!(begin != it));
        }else{
          REQUIRE(begin != it);
        }
        ++i;
      }
    }

    WHEN("using const_reverse_iterator and loop through to compare with rbegin()"){
      auto rbegin = g.crbegin();
      int i = 0;
      THEN("only  !(first one != begin()), others all (it != begin())")
      for(auto it = g.crbegin(); it != g.crend();++it){
        if(i == 0){
          REQUIRE( !(rbegin != it) );
        }else{
          REQUIRE(rbegin != it);
        }
        ++i;
      }
    }
 }
}


/*
 * 32. test const_iterator find()
 * with a complex graph structure
 * 1. find the element at very first
 * 2. find the element at middle of first level edgeSet
 * 3. find the element at the last of first level edgeSet
 * 4. find the element at the begin of second level edgeSet
 * 5. find the element at the end of second level edge set
 * 6. find the element at the begin of last level of edgeSet
 * 7. find the element at the very very last
 * 8. cannot find the element will return cend()
 */
SCENARIO("Testing find()"){
  GIVEN("give a complex graph with structure(check comments)"){
    /*
     * a: a->b(1), a->c(2), a->c(3), a->c(4)
     * b: b->a(5), b->c(6)
     * c: c->b(7), c->b(8)
     */
    std::string a{"a"};
    std::string b{"b"};
    std::string c{"c"};
    auto e1 = std::make_tuple(a, b, 1);
    auto e2 = std::make_tuple(a, c, 2);
    auto e3 = std::make_tuple(a, c, 3);
    auto e4 = std::make_tuple(a, c, 4);
    auto e5 = std::make_tuple(b, a, 5);
    auto e6 = std::make_tuple(b, c, 6);
    auto e7 = std::make_tuple(c, b, 7);
    auto e8 = std::make_tuple(c, b, 8);
    auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
    gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("1. find a->b(1) "){
      auto found = g.find(a, b, 1);
      THEN("check the value of found iterator"){
        REQUIRE("a"== std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(1 == std::get<2>(*found));
      }
    }

    WHEN("2. find a->c(2) "){
      auto found = g.find(a, c, 2);
      THEN("check the value of found iterator"){
        REQUIRE("a"== std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(2 == std::get<2>(*found));
      }
    }

    WHEN("3. find a->c(4) "){
      auto found = g.find(a, c, 4);
      THEN("check the value of found iterator"){
        REQUIRE("a"== std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(4 == std::get<2>(*found));
      }
    }
    WHEN("4. find b->a(5) "){
      auto found = g.find(b, a, 5);
      THEN("check the value of found iterator"){
        REQUIRE("b"== std::get<0>(*found));
        REQUIRE("a" == std::get<1>(*found));
        REQUIRE(5 == std::get<2>(*found));
      }
    }
    WHEN("5. find b->c(6) "){
      auto found = g.find(b, c, 6);
      THEN("check the value of found iterator"){
        REQUIRE("b"== std::get<0>(*found));
        REQUIRE("c" == std::get<1>(*found));
        REQUIRE(6 == std::get<2>(*found));
      }
    }

    WHEN("6. find c->b(7) "){
      auto found = g.find(c, b, 7);
      THEN("check the value of found iterator"){
        REQUIRE("c"== std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(7 == std::get<2>(*found));
      }
    }
    WHEN("7. find c->b(8) "){
      auto found = g.find(c, b, 8);
      THEN("check the value of found iterator"){
        REQUIRE("c"== std::get<0>(*found));
        REQUIRE("b" == std::get<1>(*found));
        REQUIRE(8 == std::get<2>(*found));
      }
    }

    WHEN("8. cannot find a edge "){
      auto found = g.find(b, c, 100);
      THEN("return cend()"){
        REQUIRE(found == g.cend());
      }
    }
  }
}

/*
 * 33. Test: const_iterator erase() -> all check its next element
 *  1. erase the element at very first
 * 2. erase the element at middle of first level edgeSet
 * 3. erase the element at the last of first level edgeSet
 * 4. erase the element at the begin of second level edgeSet
 * 5. erase the element at the end of second level edge set
 * 6. erase the element at the begin of last level of edgeSet
 * 7. erase the element at the very very last
 * 8. the element that cannot find to erase ->  will return cend()
 * 9. check after erase, -- and ++ run through that iterator_pos -> work properly
 */
SCENARIO("Testing erase()"){
  GIVEN("give a complex graph with structure(check comments) for each test case"){
    /*
       * a: a->b(1), a->c(2), a->c(3), a->c(4)
       * b: b->a(5), b->c(6)
       * c: c->b(7), c->b(8)
       */
      std::string a{"a"};
      std::string b{"b"};
      std::string c{"c"};
      auto e1 = std::make_tuple(a, b, 1);
      auto e2 = std::make_tuple(a, c, 2);
      auto e3 = std::make_tuple(a, c, 3);
      auto e4 = std::make_tuple(a, c, 4);
      auto e5 = std::make_tuple(b, a, 5);
      auto e6 = std::make_tuple(b, c, 6);
      auto e7 = std::make_tuple(c, b, 7);
      auto e8 = std::make_tuple(c, b, 8);
      auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
      gdwg::Graph<std::string, double> g{e.begin(), e.end()};

    WHEN("1. erase a->b(1) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, b, 1);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->b(1) anymore, and erase return a->c(2)"){
        //check next element
        REQUIRE("a"== std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(2 == std::get<2>(*next));

        REQUIRE(copy_g.find(a,b,1) == copy_g.cend());
      }
    }

    WHEN("2. erase a->c(2) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, c, 2);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->c(2) anymore, and erase return a->c(3)"){
        //check next element
        REQUIRE("a"== std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(3 == std::get<2>(*next));
        REQUIRE(copy_g.find(a,c,2) == copy_g.cend());
      }
    }

    WHEN("3. erase a->c(4) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(a, c, 4);
      auto next = copy_g.erase(found);
      THEN("then we cannot find a->c(4) anymore, and erase return b->a(5)"){
        //check next element
        REQUIRE("b"== std::get<0>(*next));
        REQUIRE("a" == std::get<1>(*next));
        REQUIRE(5 == std::get<2>(*next));
        REQUIRE(copy_g.find(a,c,4) == copy_g.cend());
      }
    }

    WHEN("4. erase b->a(5) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(b, a, 5);
      auto next = copy_g.erase(found);
      THEN("then we cannot find b->a(5) anymore,and erase return b->c(6) "){
        //check next element
        REQUIRE("b"== std::get<0>(*next));
        REQUIRE("c" == std::get<1>(*next));
        REQUIRE(6 == std::get<2>(*next));
        REQUIRE(copy_g.find(b,a,5) == copy_g.cend());
      }
    }

    WHEN("5. erase b->c(6) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(b, c, 6);
      auto next = copy_g.erase(found);
      THEN("then we cannot find b->c(6) anymore,and erase return c->b(7) "){
        //check next element
        REQUIRE("c"== std::get<0>(*next));
        REQUIRE("b" == std::get<1>(*next));
        REQUIRE(7 == std::get<2>(*next));
        REQUIRE(copy_g.find(b,c,6) == copy_g.cend());
      }
    }

    WHEN("6. erase c->b(7) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(c, b, 7);
      auto next = copy_g.erase(found);
      THEN("then we cannot find c->b(7) anymore, and erase return c->b(8)"){
        //check next element
        REQUIRE("c"== std::get<0>(*next));
        REQUIRE("b" == std::get<1>(*next));
        REQUIRE(8 == std::get<2>(*next));
        REQUIRE(copy_g.find(c,b,7) == copy_g.cend());
      }
    }

    WHEN("7. erase c->b(8) "){
      decltype(g) copy_g{g};
      auto found = copy_g.find(c, b, 8);
      auto next = copy_g.erase(found);
      THEN("then we cannot find c->b(8) anymore, and erase return cend()"){
        REQUIRE(next == copy_g.cend());
        REQUIRE(copy_g.find(c,b,8) == copy_g.cend());
      }
    }
    WHEN("8. cannot find one to erase "){
      decltype(g) copy_g{g};
      auto found = copy_g.cend();
      auto result = copy_g.erase(found);
      THEN("we will return cend()"){
        REQUIRE(result == copy_g.cend());
      }
    }

    WHEN("check after erase with -- and ++ through that position"){
      decltype(g) copy_g{g};
      auto found = copy_g.find(a,c,2);
      auto result = copy_g.erase(found);
      THEN("--result should be a->b(1)"){
        --result;
        REQUIRE("a"== std::get<0>(*result));
        REQUIRE("b" == std::get<1>(*result));
        REQUIRE(1 == std::get<2>(*result));

        AND_THEN("++result will be a->c(3)"){
          ++result;
          REQUIRE("a"== std::get<0>(*result));
          REQUIRE("c" == std::get<1>(*result));
          REQUIRE(3 == std::get<2>(*result));
        }
      }
    }
  }
}

/*
 *  34. Test: const object with iterator
 *  --- 9 to 10 will do const_iterator and const_reverse_iterator together
 *  9. ++ look through whole graph
 *  10. -- look through whole graph
 *  11. find
 *  12. ==
 *  13. !=
 *  -----
 *  1.have cbegin() to call
 *  2.have cend()
 *  3. have begin()
 *  4. have end()
 *  5.have crbegin()
 *  6.have crend()
 *  7. have rbegin()
 *  8. have rend()
 *
 */
SCENARIO("Test const graph with iterator"){
  GIVEN("given a const graph "){
    /*
       * a: a->b(1), a->c(2), a->c(3), a->c(4)
       * b: b->a(5), b->c(6)
       * c: c->b(7), c->b(8)
       */
      std::string a{"a"};
      std::string b{"b"};
      std::string c{"c"};
      auto e1 = std::make_tuple(a, b, 1);
      auto e2 = std::make_tuple(a, c, 2);
      auto e3 = std::make_tuple(a, c, 3);
      auto e4 = std::make_tuple(a, c, 4);
      auto e5 = std::make_tuple(b, a, 5);
      auto e6 = std::make_tuple(b, c, 6);
      auto e7 = std::make_tuple(c, b, 7);
      auto e8 = std::make_tuple(c, b, 8);
      auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2, e3,e4,e5,e6,e7,e8};
      const gdwg::Graph<std::string, double> g{e.begin(), e.end()};


      WHEN("test case from 1-8. ensure const graph have these iterator function to call"){
        THEN("they should all work properly"){
          REQUIRE_NOTHROW(g.cbegin());
          REQUIRE_NOTHROW(g.cend());
          REQUIRE_NOTHROW(g.begin());
          REQUIRE_NOTHROW(g.end());
          REQUIRE_NOTHROW(g.crbegin());
          REQUIRE_NOTHROW(g.crend());
          REQUIRE_NOTHROW(g.rbegin());
          REQUIRE_NOTHROW(g.rend());
        }
      }

      WHEN("9. use ++ to look through for const_iterator"){
        THEN("we should get whatever the value we expected"){
          auto edge = e.cbegin();
          for(auto it=g.cbegin(); it != g.cend(); ++it){
            REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
            REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
            REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
            ++edge;
          }
        }

        AND_WHEN("++ look through by const_reverse_iterator"){
          THEN("we still get the expected value"){
            auto edge = e.crbegin();
            for(auto it=g.crbegin(); it != g.crend(); ++it){
              REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
              REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
              REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
              ++edge;
            }
          }
        }
      }

      WHEN("10. loop through-- by const_iterator"){
        THEN("check expected value"){
          auto edge = e.cend();
          auto it=g.cend();
          std::advance(it, -1);
          std::advance(edge, -1);
          for(; it != g.cbegin(); --it){ // compare from last element to begin-1
            REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
            REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
            REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
            --edge;
          }
          //compare begin element
          REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
          REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
          REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
        }

        AND_WHEN("loop through-- by const_reverse_iterator"){
          THEN("check expected value"){
            auto edge = e.crend();
            auto it=g.crend();
            std::advance(it, -1);
            std::advance(edge, -1);
            for(; it != g.crbegin(); --it){ // compare from last element to begin-1
              REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
              REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
              REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
              --edge;
            }
            //compare begin element
            REQUIRE(std::get<0>(*edge) == std::get<0>(*it));
            REQUIRE(std::get<1>(*edge) == std::get<1>(*it));
            REQUIRE(std::get<2>(*edge) == std::get<2>(*it));
          }
        }
      }

      WHEN("11. const obeject call find()"){
        THEN("work properly"){
          REQUIRE_NOTHROW(g.find(a, b, 1));
        }
      }

      WHEN("12. const obeject call == operator for const_iterator and const_reverse_iterator"){
        THEN("work properly"){
          REQUIRE_NOTHROW(g.cbegin() == g.cbegin());
          REQUIRE_NOTHROW(g.crbegin() == g.crbegin());
          REQUIRE_NOTHROW(g.cend() == g.cend());
          REQUIRE_NOTHROW(g.crend() == g.crend());
        }
      }

      WHEN("13. const obeject call != operator for const_iterator and const_reverse_iterator"){
        THEN("work properly"){
          REQUIRE_NOTHROW(g.cend() != g.cbegin());
          REQUIRE_NOTHROW(g.crend() != g.crbegin());
          REQUIRE_NOTHROW(g.cbegin() != g.cend());
          REQUIRE_NOTHROW(g.crbegin() != g.crend());
        }
      }

  }
}