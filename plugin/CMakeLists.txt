# Copyright (c) 2018 Hartmut Kaiser
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(plugin_headers
    ${CMAKE_CURRENT_LIST_DIR}/con_plugin.hpp
    ${CMAKE_CURRENT_LIST_DIR}/constants_of_nature.hpp)

set(plugin_sources
    ${CMAKE_CURRENT_LIST_DIR}/con_plugin.cpp
    ${CMAKE_CURRENT_LIST_DIR}/constants_of_nature.cpp)

add_phylanx_primitive_plugin(
    constants_of_nature
    HEADERS ${plugin_headers}
    SOURCES ${plugin_sources})
