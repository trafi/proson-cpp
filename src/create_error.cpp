/*
 * Copyright 2017 TRAFI
 *
 * Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 * http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 * http://opensource.org/licenses/MIT>, at your option. This file may not be
 * copied, modified, or distributed except according to those terms.
 *
 */

#include "create_error.hpp"

#include <sstream>

using namespace std;
using namespace proson;

MergeJsonError proson::internal::error_json_parse(const std::string& message)
{
    MergeJsonError err;

    err.kind = MergeJsonErrorType::JsonParse;
    err.message = message;

    return err;
}

MergeJsonError proson::internal::error_json_field_invalid_type(
    const std::shared_ptr<FieldRef>& field, const std::string& expected_type, std::string value)
{
    MergeJsonError err;

    err.kind = MergeJsonErrorType::JsonFieldInvalidType;

    std::ostringstream ss;
    ss << "expected type " << expected_type << ", but found value " << value;
    if (nullptr != field) {
        ss << " at " << field->full_name();
    }

    err.message = ss.str();

    return err;
}

MergeJsonError proson::internal::error_json_field_invalid_enum_value_type(
    const std::shared_ptr<FieldRef>& field,
    int invalid_value,
    const google::protobuf::EnumDescriptor* enum_desc)
{
    MergeJsonError err;

    err.kind = MergeJsonErrorType::JsonFieldInvalidEnumType;

    std::ostringstream ss;
    ss << "expected one of ";

    for (int i = 0; i < enum_desc->value_count(); i++) {
        if (i > 0) {
            ss << ", ";
        }
        const auto& value_type = enum_desc->value(i);
        ss << value_type->name() << " = " << value_type->number();
    }

    ss << ", but found value " << invalid_value;

    if (nullptr != field) {
        ss << " at " << field->full_name();
    }

    err.message = ss.str();

    return err;
}

MergeJsonError proson::internal::error_type_conversion_not_implemented(
    const std::shared_ptr<FieldRef>& field, const std::string& expected_type)
{
    MergeJsonError err;

    err.kind = MergeJsonErrorType::TypeConversionNotImplemented;

    std::ostringstream ss;
    ss << "type conversion from " << expected_type
       << " is not implemented, but pull requests are welcome";
    if (nullptr != field) {
        ss << " at " << field->full_name();
    }

    err.message = ss.str();

    return err;
}