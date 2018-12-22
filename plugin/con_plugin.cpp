// Copyright (c) 2018 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>
#include <phylanx/plugins/plugin_factory.hpp>

#include "con_plugin.hpp"

PHYLANX_REGISTER_PLUGIN_MODULE();

PHYLANX_REGISTER_PLUGIN_FACTORY(constants_of_nature_plugin,
    phylanx_plugin::constants_of_nature::match_data);
PHYLANX_REGISTER_PLUGIN_FACTORY(constants_of_nature_e_plugin,
    phylanx_plugin::constants_of_nature::match_data_e);
PHYLANX_REGISTER_PLUGIN_FACTORY(constants_of_nature_pi_plugin,
    phylanx_plugin::constants_of_nature::match_data_pi);
PHYLANX_REGISTER_PLUGIN_FACTORY(constants_of_nature_ua_plugin,
    phylanx_plugin::constants_of_nature::match_data_ua);
