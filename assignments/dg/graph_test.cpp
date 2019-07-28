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
 *  1. Test default constructor. How to test:
 *  after initialized the vector with default constructor,
 *  check TODO:
 */
SCENARIO("Testing default constructor") {
  GIVEN("We will initialized a vector by all the possible ways by using the default constructor") {
    WHEN("when `EuclidenVector vec` -> then dimension should be 1, magnitudes[0] is 0") {
      EuclideanVector vec;
      REQUIRE(vec.GetNumDimensions() == 1);
      REQUIRE(vec[0] == 0);
    }

    WHEN("when we initialized a 0-dimension vector -> dimension should be 0, throw for "
         "maginitudes[0]") {
      EuclideanVector vec{0};
      REQUIRE(vec.GetNumDimensions() == 0);
      // if index 0 is not valid, we can say the whole vector is empty
      REQUIRE_THROWS_WITH(vec.at(0), "Index 0 is not valid for this EuclideanVector object");
    }

    WHEN("when initialized with some positive int, such d = 10 -> dimension = 10 and magnitudes "
         "are all 0") {
      EuclideanVector vec{10};
      REQUIRE(vec.GetNumDimensions() == 10);
      for (int i = 0; i < 10; ++i) {
        REQUIRE(vec[i] == 0);
      }
    }

    WHEN("when we initialized with some int type variable instead of numeric value, we should get "
         "the same result") {
      int d{5};
      EuclideanVector vec{d};

      REQUIRE(vec.GetNumDimensions() == 5);
      for (int i = 0; i < 5; ++i) {
        REQUIRE(vec[i] == 0);
      }
    }
  }
}