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
      std::string s10{"a"};
      std::string s20{"b"};
      std::string s30{"c"};
      auto e10 = std::make_tuple(s1, s2, 1);
      auto e20 = std::make_tuple(s1, s3, 2);
      auto es = std::vector<std::tuple<std::string, std::string, double>>{e10, e20};
      gdwg::Graph<std::string, double> g1{es.begin(), e.end()};
      THEN("remove 'b' -> a->null, a->c(2), c:{} "){
        g1.DeleteNode("b");

        AND_THEN("cbegin() should be a->c(2)"){
          auto it = g.cbegin();
          REQUIRE(std::get<0>(*it) == "a");
          REQUIRE(std::get<1>(*it) == "c");
          REQUIRE(std::get<2>(*it) == 2);
        }
      }
    }

//    WHEN("empty graph"){
//      g.Clear();
//      THEN("cbegin() == cend()"){
//        REQUIRE(g.begin() == g.cend());
//      }
//    }
  }
}