#include <gtest/gtest.h>

#include "search.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_kdtree_xxx()
{
}


void test_kdtree_findTenNearestAirfields()
{
  int16_t airports[10] = {0};

  find_airports(520, 91, airports);
  
  // compare against expected
  //TEST_ASSERT_EQUAL_STRING
}
