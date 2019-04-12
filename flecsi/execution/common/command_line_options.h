/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Los Alamos National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*!
  @file

  This file defines common command-line options for use with
  boost::program_options.
 */

#include <string>

inline std::string __flecsi_tags = "all";

#define FLECSI_FLOG_TAG_OPTION                                                 \
  ("flog-tags",                                                                \
  value(&__flecsi_tags)->implicit_value("0"),                                  \
  "Enable the specified output tags, e.g., --flog-tags=tag1,tag2."             \
  " Passing --flog-tags by itself will print the available tags.")

#define FLECSI_COLORS_PER_RANK_OPTION                                          \
  ("colors-per-rank",                                                          \
  value<size_t>()->default_value(1),                                           \
  "Specify the number of colors per rank.")