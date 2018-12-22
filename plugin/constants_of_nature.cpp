// Copyright (c) 2018 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>

#include <hpx/include/lcos.hpp>
#include <hpx/include/util.hpp>
#include <hpx/throw_exception.hpp>

#include <cstdint>
#include <cstddef>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "constants_of_nature.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace phylanx_plugin
{
    constexpr char const* const help_string = R"(
        con(name)
        Args:

            name (string) : either `"e"`, `"pi"`, or `"ua"`

        Returns:

            the value of either `"e"`, `"pi"`, or `"ua"`
        )";

    ///////////////////////////////////////////////////////////////////////////
    phylanx::execution_tree::match_pattern_type const
        constants_of_nature::match_data =
        {
            hpx::util::make_tuple("con",
                std::vector<std::string>{"con(_1)"},
                &create_constants_of_nature,
                &phylanx::execution_tree::create_primitive<constants_of_nature>,
                help_string
            )
        };

    phylanx::execution_tree::match_pattern_type const
        constants_of_nature::match_data_e =
        {
            hpx::util::make_tuple("e",
                std::vector<std::string>{"e()"},
                &create_constants_of_nature,
                &phylanx::execution_tree::create_primitive<constants_of_nature>,
                help_string
            )
        };

    phylanx::execution_tree::match_pattern_type const
        constants_of_nature::match_data_pi =
        {
            hpx::util::make_tuple("pi",
                std::vector<std::string>{"pi()"},
                &create_constants_of_nature,
                &phylanx::execution_tree::create_primitive<constants_of_nature>,
                help_string
            )
        };

    phylanx::execution_tree::match_pattern_type const
        constants_of_nature::match_data_ua =
        {
            hpx::util::make_tuple("ua",
                std::vector<std::string>{"ua()"},
                &create_constants_of_nature,
                &phylanx::execution_tree::create_primitive<constants_of_nature>,
                help_string
            )
        };

    namespace detail
    {
        std::string extract_function_name(std::string const& name)
        {
            using namespace phylanx::execution_tree::compiler;

            primitive_name_parts name_parts;
            if (!parse_primitive_name(name, name_parts))
            {
                return name;
            }
            return name_parts.primitive;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    constants_of_nature::constants_of_nature(
            primitive_arguments_type&& operands, std::string const& name,
            std::string const& codename)
      : phylanx::execution_tree::primitives::primitive_component_base(
            std::move(operands), name, codename)
    {}

    ///////////////////////////////////////////////////////////////////////////
    double constants_of_nature::calculate_constant(std::string const& name) const
    {
        if (name == "e")
        {
            return 2.718281828459045235360287471352662497757247093699959574966;
        }
        else if (name == "pi")
        {
            return 3.141592653589793238462643383279502884197169399375105820974;
        }
        else if (name == "ua")
        {
            return 42;
        }

        HPX_THROW_EXCEPTION(hpx::bad_parameter,
            "constants_of_nature::eval",
            generate_error_message(
                "unknown constant of nature requested: " + name));
    }

    ///////////////////////////////////////////////////////////////////////////
    hpx::future<phylanx::execution_tree::primitive_argument_type>
    constants_of_nature::eval(primitive_arguments_type const& operands,
        primitive_arguments_type const& args, eval_context ctx) const
    {
        if (operands.size() > 1)
        {
            HPX_THROW_EXCEPTION(hpx::bad_parameter,
                "constants_of_nature::eval",
                generate_error_message(
                    "constants_of_nature accepts either none or exactly one "
                    "argument"));
        }

        if (operands.empty())
        {
            // no arguments, derive functionality from primitive name
            return hpx::make_ready_future(primitive_argument_type{
                calculate_constant(detail::extract_function_name(name_))});
        }

        auto this_ = this->shared_from_this();
        return string_operand(
                operands[0], args, name_, codename_, std::move(ctx))
            .then(
                [this_](hpx::future<std::string> val)
                ->  primitive_argument_type
                {
                    return primitive_argument_type{
                        this_->calculate_constant(val.get())};
                });
    }
}
