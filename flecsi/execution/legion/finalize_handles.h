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

/*! @file */

namespace flecsi {
namespace execution {

/*!
  FIXME
  @ingroup execution
 */
struct finalize_handles_t : public utils::tuple_walker__<finalize_handles_t> {

  /*!
    FIXME
     @ingroup execution
   */

  template<
      typename T,
      size_t EXCLUSIVE_PERMISSIONS,
      size_t SHARED_PERMISSIONS,
      size_t GHOST_PERMISSIONS>
  void handle(dense_accessor__<
              T,
              EXCLUSIVE_PERMISSIONS,
              SHARED_PERMISSIONS,
              GHOST_PERMISSIONS> & a) {} // handle

  template<
    typename T,
    size_t EXCLUSIVE_PERMISSIONS,
    size_t SHARED_PERMISSIONS,
    size_t GHOST_PERMISSIONS
  >
  void
  handle(
    sparse_accessor <
    T,
    EXCLUSIVE_PERMISSIONS,
    SHARED_PERMISSIONS,
    GHOST_PERMISSIONS
    > &a
  )
  {
    // TODO: implement
  }

  template<
    typename T
  >
  void
  handle(
    sparse_mutator<
    T
    > &m
  )
  {
    // TODO: implement
  }

  /*!
     The finalize_handles_t type can be called to walk task args after task
     execution. This allows us to free memory allocated during the task.

     @ingroup execution
   */

  template<typename T, size_t PERMISSIONS>
  typename std::enable_if_t<
      std::is_base_of<topology::mesh_topology_base_t, T>::value>
  handle(data_client_handle__<T, PERMISSIONS> & h) {

    if (PERMISSIONS == wo || PERMISSIONS == rw) {
      auto & context_ = context_t::instance();
      auto & ssm = context_.index_subspace_info();

      for (size_t i{0}; i < h.num_index_subspaces; ++i) {
        data_client_handle_index_subspace_t & iss = h.handle_index_subspaces[i];

        auto itr = ssm.find(iss.index_subspace);
        clog_assert(itr != ssm.end(), "invalid index subspace");
        context_t::index_subspace_info_t & si = itr->second;

        clog_assert(si.size == 0, "index subspace size already set");
        si.size = h.get_index_subspace_size_(iss.index_subspace);
      }
    }

    h.delete_storage();
  } // handle

  template<typename T, size_t PERMISSIONS>
  typename std::enable_if_t<
      !std::is_base_of<topology::mesh_topology_base_t, T>::value>
  handle(data_client_handle__<T, PERMISSIONS> & h) {
    h.delete_storage();
  } // handle

  /*!
    If this is not a data handle, then simply skip it.
   */

  template<typename T>
  static typename std::enable_if_t<
      !std::is_base_of<dense_accessor_base_t, T>::value>
  handle(T &) {} // handle

}; // struct finalize_handles_t

} // namespace execution
} // namespace flecsi
