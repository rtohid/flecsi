/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Triad National Security, LLC
   All rights reserved.
                                                                              */

#include <flecsi/utils/ftest.hh>

#define __FLECSI_PRIVATE__
#include <flecsi/execution/common/task_attributes.hh>

flog_register_tag(task_attributes);

using namespace flecsi;

int
task_attributes(int argc, char ** argv) {

  FTEST();

  {
    size_t mask = loc | leaf;

    ASSERT_TRUE(execution::leaf_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::loc);
  }

  {
    size_t mask = loc | inner;

    ASSERT_TRUE(execution::inner_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::loc);
  }

  {
    size_t mask = loc | idempotent;

    ASSERT_TRUE(execution::idempotent_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::loc);
  }

  {
    size_t mask = toc | leaf;

    ASSERT_TRUE(execution::leaf_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::toc);
  }

  {
    size_t mask = toc | inner;

    ASSERT_TRUE(execution::inner_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::toc);
  }

  {
    size_t mask = toc | idempotent;

    ASSERT_TRUE(execution::idempotent_task(mask));
    ASSERT_EQ(execution::mask_to_processor_type(mask),
      execution::task_processor_type_t::toc);
  }

  return FTEST_RESULT();
}

ftest_register_driver(task_attributes);