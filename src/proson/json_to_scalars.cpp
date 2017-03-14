/*
 * Copyright 2017 TRAFI
 *
 * Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 * http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 * http://opensource.org/licenses/MIT>, at your option. This file may not be
 * copied, modified, or distributed except according to those terms.
 *
 */

#include "json_to_scalars.hpp"

#include <proson/create_error.hpp>

using namespace std;
using namespace nlohmann;
using namespace proson;
using namespace proson::internal;

result_value<string> proson::internal::to_string(const std::shared_ptr<FieldRef>& field_ref,
                                                 const json& value)
{
    switch (value.type()) {
        case json::value_t::string:
            return result_value<string>::ok(value.get<string>());
        default:
            return result_value<string>::err(
                error_json_field_invalid_type(field_ref, "string", value.dump()));
    }
}

result_value<float> proson::internal::to_float(const shared_ptr<FieldRef>& field_ref,
                                               const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer:
            return result_value<float>::ok(value.get<int64_t>());
        case json::value_t::number_unsigned:
            return result_value<float>::ok(value.get<uint64_t>());
        case json::value_t::number_float:
            return result_value<float>::ok(value.get<float>());
        default:
            return result_value<float>::err(
                error_json_field_invalid_type(field_ref, "float", value.dump()));
    }
}

result_value<double> proson::internal::to_double(const shared_ptr<FieldRef>& field_ref,
                                                 const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer:
            return result_value<double>::ok(value.get<int64_t>());
        case json::value_t::number_unsigned:
            return result_value<double>::ok(value.get<uint64_t>());
        case json::value_t::number_float:
            return result_value<double>::ok(value.get<double>());
        default:
            return result_value<double>::err(
                error_json_field_invalid_type(field_ref, "double", value.dump()));
    }
}

result_value<int32_t> proson::internal::to_int32(const shared_ptr<FieldRef>& field_ref,
                                                 const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer: {
            int64_t sval = value.get<int64_t>();
            if (sval > INT32_MAX) {
                return result_value<int32_t>::err(
                    error_json_field_invalid_type(field_ref, "int32", value.dump()));
            }
            return result_value<int32_t>::ok((int32_t)sval);
        }
        case json::value_t::number_unsigned: {
            uint64_t uval = value.get<uint64_t>();
            if (uval > INT32_MAX) {
                return result_value<int32_t>::err(
                    error_json_field_invalid_type(field_ref, "int32", value.dump()));
            }
            return result_value<int32_t>::ok((int32_t)uval);
        }
        default:
            return result_value<int32_t>::err(
                error_json_field_invalid_type(field_ref, "int32", value.dump()));
    }
}

result_value<uint32_t> proson::internal::to_uint32(const shared_ptr<FieldRef>& field_ref,
                                                   const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer: {
            int64_t sval = value.get<int64_t>();
            if (sval < 0 || sval > UINT32_MAX) {
                return result_value<uint32_t>::err(
                    error_json_field_invalid_type(field_ref, "uint32", value.dump()));
            }
            return result_value<uint32_t>::ok((uint32_t)sval);
        }
        case json::value_t::number_unsigned: {
            uint64_t uval = value.get<uint64_t>();
            if (uval > UINT32_MAX) {
                return result_value<uint32_t>::err(
                    error_json_field_invalid_type(field_ref, "uint32", value.dump()));
            }
            return result_value<uint32_t>::ok((uint32_t)uval);
        }
        default:
            return result_value<uint32_t>::err(
                error_json_field_invalid_type(field_ref, "uint32", value.dump()));
    }
}

result_value<int> proson::internal::to_enum_int(const shared_ptr<FieldRef>& field_ref,
                                                const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer: {
            int64_t sval = value.get<int64_t>();
            if (sval > INT_MAX) {
                return result_value<int>::err(
                    error_json_field_invalid_type(field_ref, "enum", value.dump()));
            }
            return result_value<int>::ok((int)sval);
        }
        case json::value_t::number_unsigned: {
            uint64_t uval = value.get<uint64_t>();
            if (uval > INT_MAX) {
                return result_value<int>::err(
                    error_json_field_invalid_type(field_ref, "enum", value.dump()));
            }
            return result_value<int>::ok((int)uval);
        }
        default:
            return result_value<int>::err(
                error_json_field_invalid_type(field_ref, "enum", value.dump()));
    }
}

result_value<uint64_t> proson::internal::to_uint64(const shared_ptr<FieldRef>& field_ref,
                                                   const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer: {
            int64_t sval = value.get<int64_t>();
            if (sval < 0) {
                return result_value<uint64_t>::err(
                    error_json_field_invalid_type(field_ref, "uint64", value.dump()));
            }
            return result_value<uint64_t>::ok((uint64_t)sval);
        }
        case json::value_t::number_unsigned: {
            return result_value<uint64_t>::ok(value.get<uint64_t>());
        }
        default:
            return result_value<uint64_t>::err(
                error_json_field_invalid_type(field_ref, "uint64", value.dump()));
    }
}

result_value<bool> proson::internal::to_bool(const shared_ptr<FieldRef>& field_ref,
                                             const json& value)
{
    switch (value.type()) {
        case json::value_t::boolean: {
            return result_value<bool>::ok(value.get<bool>());
        }
        default:
            return result_value<bool>::err(
                error_json_field_invalid_type(field_ref, "bool", value.dump()));
    }
}

result_value<bool> proson::internal::to_bytes(const shared_ptr<FieldRef>& field_ref,
                                              const json& value)
{
    return result_value<bool>::err(error_type_conversion_not_implemented(field_ref, "bytes"));
}

result_value<int64_t> proson::internal::to_int64(const shared_ptr<FieldRef>& field_ref,
                                                 const json& value)
{
    switch (value.type()) {
        case json::value_t::number_integer:
            return result_value<int64_t>::ok(value.get<int64_t>());
        case json::value_t::number_unsigned: {
            auto val = value.get<uint64_t>();
            if (val > INT64_MAX) {
                return result_value<int64_t>::err(
                    error_json_field_invalid_type(field_ref, "int64", value.dump()));
            }
            return result_value<int64_t>::ok((int64_t)val);
        }
        default:
            return result_value<int64_t>::err(
                error_json_field_invalid_type(field_ref, "int64", value.dump()));
    }
}
