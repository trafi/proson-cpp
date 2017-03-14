/*
 * Copyright 2017 TRAFI
 *
 * Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 * http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 * http://opensource.org/licenses/MIT>, at your option. This file may not be
 * copied, modified, or distributed except according to those terms.
 *
 */

#include "proson.hpp"

#include <google/protobuf/repeated_field.h>
#include <json.hpp>

#include "create_error.hpp"
#include "json_to_scalars.hpp"

using namespace std;
using namespace google::protobuf;
using namespace nlohmann;
using namespace proson;
using namespace proson::internal;

namespace {
    result merge_field(const std::shared_ptr<FieldRef>& field_ref,
                       google::protobuf::Message* m,
                       const google::protobuf::FieldDescriptor* f,
                       const json& j);

    maybe::result<void, MergeJsonError> merge_fields(const std::shared_ptr<FieldRef>& parent_ref,
                                                     google::protobuf::Message* m,
                                                     const json& j);

    result_value<const google::protobuf::EnumValueDescriptor*> enum_int_to_value_type(
        const std::shared_ptr<FieldRef>& field_ref,
        const google::protobuf::FieldDescriptor* f,
        int number)
    {
        const auto& enum_type = f->enum_type();
        const EnumValueDescriptor* value_type = nullptr;
        for (int i = 0; i < enum_type->value_count(); i++) {
            const auto& item = enum_type->value(i);
            if (item->number() == number) {
                value_type = item;
                break;
            }
        }
        if (nullptr == value_type) {
            return result_value<const google::protobuf::EnumValueDescriptor*>::err(
                error_json_field_invalid_enum_value_type(field_ref, number, enum_type));
        }
        return result_value<const google::protobuf::EnumValueDescriptor*>::ok(value_type);
    }

    result merge_field_repeated(const std::shared_ptr<FieldRef>& field_ref,
                                google::protobuf::Message* m,
                                const google::protobuf::FieldDescriptor* f,
                                const json& j)
    {
        const auto reflection = m->GetReflection();

        const auto& it = j.find(f->name());
        if (it == j.end()) {
            return result::ok();
        }

        reflection->ClearField(m, f);

        if (it->is_null()) {
            reflection->ClearField(m, f);
            return result::ok();
        }

        if (!it->is_array()) {
            return result::err(error_json_field_invalid_type(field_ref, "array", it->dump()));
        }

        reflection->ClearField(m, f);

        int index = 0;
        for (const auto& array_val : *it) {
            auto array_val_ref = make_shared<FieldRef>(index, field_ref);
            auto merge_res = result::ok();

            switch (f->type()) {
                case FieldDescriptor::TYPE_MESSAGE: {
                    merge_res
                        = merge_fields(array_val_ref, reflection->AddMessage(m, f), array_val);
                    break;
                }
                case FieldDescriptor::TYPE_STRING: {
                    merge_res = to_string(array_val_ref, array_val)
                                    .map([&](string val) {
                                        reflection->AddString(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                }
                case FieldDescriptor::TYPE_ENUM:
                    merge_res = to_enum_int(array_val_ref, array_val)
                                    .and_then([&](int number) {
                                        return enum_int_to_value_type(array_val_ref, f, number);
                                    })
                                    .and_then([&](
                                        const google::protobuf::EnumValueDescriptor* value_type) {
                                        reflection->AddEnum(m, f, value_type);
                                        return result_value<int>::ok(0);
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_DOUBLE:
                    merge_res = to_double(array_val_ref, array_val)
                                    .map([&](double val) {
                                        reflection->AddDouble(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_FLOAT:
                    merge_res = to_double(array_val_ref, array_val)
                                    .map([&](double val) {
                                        reflection->AddFloat(m, f, (float)val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_BOOL:
                    merge_res = to_bool(array_val_ref, array_val)
                                    .map([&](bool val) {
                                        reflection->AddBool(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_INT32:
                case FieldDescriptor::TYPE_SINT32:
                case FieldDescriptor::TYPE_SFIXED32:
                    merge_res = to_int32(array_val_ref, array_val)
                                    .map([&](int32_t val) {
                                        reflection->AddInt32(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_UINT32:
                case FieldDescriptor::TYPE_FIXED32:
                    merge_res = to_uint32(array_val_ref, array_val)
                                    .map([&](uint32_t val) {
                                        reflection->AddUInt32(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_INT64:
                case FieldDescriptor::TYPE_SINT64:
                case FieldDescriptor::TYPE_SFIXED64:
                    merge_res = to_int64(array_val_ref, array_val)
                                    .map([&](int64_t val) {
                                        reflection->AddInt64(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_UINT64:
                case FieldDescriptor::TYPE_FIXED64:
                    merge_res = to_uint64(array_val_ref, array_val)
                                    .map([&](uint64_t val) {
                                        reflection->AddUInt64(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                case FieldDescriptor::TYPE_BYTES:
                    return to_bytes(array_val_ref, array_val).map_void();
                case FieldDescriptor::TYPE_GROUP:
                    return result::err(
                        error_type_conversion_not_implemented(array_val_ref, "group"));
            }

            if (!merge_res) {
                return merge_res;
            }

            index++;
        }

        return result::ok();
    }

    result merge_field(const std::shared_ptr<FieldRef>& field_ref,
                       google::protobuf::Message* m,
                       const google::protobuf::FieldDescriptor* f,
                       const json& j)
    {
        const auto reflection = m->GetReflection();

        const auto& it = j.find(f->name());
        if (it == j.end()) {
            if (f->type() == FieldDescriptor::TYPE_MESSAGE && f->is_required()
                && !reflection->HasField(*m, f)) {
                reflection->MutableMessage(m, f);
            }

            return result::ok();
        }

        if (it->is_null() && !f->is_required()) {
            reflection->ClearField(m, f);
            return result::ok();
        }

        switch (f->type()) {
            case FieldDescriptor::TYPE_MESSAGE: {
                auto json_val = it->dump();
                return merge_fields(field_ref, reflection->MutableMessage(m, f), *it);
            }
            case FieldDescriptor::TYPE_STRING:
                return to_string(field_ref, *it)
                    .map([&](string val) {
                        reflection->SetString(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_ENUM:
                return to_enum_int(field_ref, *it)
                    .and_then(
                        [&](int number) { return enum_int_to_value_type(field_ref, f, number); })
                    .and_then([&](const google::protobuf::EnumValueDescriptor* value_type) {
                        reflection->SetEnum(m, f, value_type);
                        return result_value<int>::ok(0);
                    })
                    .map_void();
            case FieldDescriptor::TYPE_DOUBLE:
                return to_double(field_ref, *it)
                    .map([&](double val) {
                        reflection->SetDouble(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_FLOAT:
                return to_float(field_ref, *it)
                    .map([&](float val) {
                        reflection->SetFloat(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_BOOL:
                return to_bool(field_ref, *it)
                    .map([&](bool val) {
                        reflection->SetBool(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_INT32:
            case FieldDescriptor::TYPE_SINT32:
            case FieldDescriptor::TYPE_SFIXED32:
                return to_int32(field_ref, *it)
                    .map([&](int32_t val) {
                        reflection->SetInt32(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_UINT32:
            case FieldDescriptor::TYPE_FIXED32:
                return to_uint32(field_ref, *it)
                    .map([&](uint32_t val) {
                        reflection->SetUInt32(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_INT64:
            case FieldDescriptor::TYPE_SINT64:
            case FieldDescriptor::TYPE_SFIXED64:
                return to_int64(field_ref, *it)
                    .map([&](int64_t val) {
                        reflection->SetInt64(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_UINT64:
            case FieldDescriptor::TYPE_FIXED64:
                return to_uint64(field_ref, *it)
                    .map([&](uint64_t val) {
                        reflection->SetUInt64(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_BYTES:
                return to_bytes(field_ref, *it).map_void();
            case FieldDescriptor::TYPE_GROUP:
                return result::err(error_type_conversion_not_implemented(field_ref, "group"));
        }

        return result::ok();
    }

    maybe::result<void, MergeJsonError> merge_fields(const std::shared_ptr<FieldRef>& parent_ref,
                                                     google::protobuf::Message* m,
                                                     const json& j)
    {
        if (j.type() != json::value_t::object) {
            return result::err(error_json_field_invalid_type(parent_ref, "object", j.dump()));
        }

        const auto& descriptor = m->GetDescriptor();

        for (int i = 0; i < descriptor->field_count(); i++) {
            auto field_d = descriptor->field(i);
            auto field_ref = make_shared<FieldRef>(field_d->name(), parent_ref);

            if (field_d->is_repeated()) {
                auto merge_res = merge_field_repeated(field_ref, m, field_d, j);
                if (!merge_res) {
                    return merge_res;
                }
            } else {
                auto merge_res = merge_field(field_ref, m, field_d, j);
                if (!merge_res) {
                    return merge_res;
                }
            }
        }

        return result::ok();
    }

    result_value<json> dump_fields(const std::shared_ptr<FieldRef>& parent_ref,
                                   const google::protobuf::Message& m,
                                   const bool skip_default_values);

    result dump_field_repeated(const std::shared_ptr<FieldRef>& parent_ref,
                               const google::protobuf::Message& m,
                               const google::protobuf::FieldDescriptor* f,
                               json& obj,
                               const bool skip_default_values)
    {
        const auto reflection = m.GetReflection();
        std::vector<json> array;
        array.reserve((size_t)reflection->FieldSize(m, f));

        for (int i = 0; i < reflection->FieldSize(m, f); i++) {
            auto array_val_ref = make_shared<FieldRef>(i, parent_ref);

            switch (f->type()) {
                case FieldDescriptor::TYPE_MESSAGE: {
                    const auto& field_m = reflection->GetRepeatedMessage(m, f, i);
                    auto json = dump_fields(array_val_ref, field_m, skip_default_values);
                    if (!json) {
                        return result::err(json.err_value());
                    }
                    array.push_back(json.ok_value());
                    break;
                }
                case FieldDescriptor::TYPE_STRING: {
                    array.push_back(reflection->GetRepeatedString(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_ENUM: {
                    array.push_back(reflection->GetRepeatedEnum(m, f, i)->number());
                    break;
                }
                case FieldDescriptor::TYPE_DOUBLE: {
                    array.push_back(reflection->GetRepeatedDouble(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_FLOAT: {
                    array.push_back(reflection->GetRepeatedFloat(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_BOOL: {
                    array.push_back(reflection->GetRepeatedBool(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_INT32:
                case FieldDescriptor::TYPE_SINT32:
                case FieldDescriptor::TYPE_SFIXED32: {
                    array.push_back(reflection->GetRepeatedInt32(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_UINT32:
                case FieldDescriptor::TYPE_FIXED32: {
                    array.push_back(reflection->GetRepeatedUInt32(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_INT64:
                case FieldDescriptor::TYPE_SINT64:
                case FieldDescriptor::TYPE_SFIXED64: {
                    array.push_back(reflection->GetRepeatedInt64(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_UINT64:
                case FieldDescriptor::TYPE_FIXED64: {
                    array.push_back(reflection->GetRepeatedUInt64(m, f, i));
                    break;
                }
                case FieldDescriptor::TYPE_BYTES:
                    return result::err(error_type_conversion_not_implemented(parent_ref, "bytes"));
                case FieldDescriptor::TYPE_GROUP:
                    return result::err(error_type_conversion_not_implemented(parent_ref, "group"));
            }
        }

        if (skip_default_values && array.empty()) {
            return result::ok();
        }

        obj[f->name()] = array;

        return result::ok();
    }

    result dump_field(const std::shared_ptr<FieldRef>& parent_ref,
                      const google::protobuf::Message& m,
                      const google::protobuf::FieldDescriptor* f,
                      json& obj,
                      const bool skip_default_values)
    {
        const auto reflection = m.GetReflection();
        if (!reflection->HasField(m, f)) {
            if (!skip_default_values) {
                obj[f->name()] = nullptr;
            }
            return result::ok();
        }

        switch (f->type()) {
            case FieldDescriptor::TYPE_MESSAGE: {
                const auto& field_m = reflection->GetMessage(m, f, nullptr);
                auto json = dump_fields(parent_ref, field_m, skip_default_values);
                if (!json) {
                    return result::err(json.err_value());
                }
                if (skip_default_values && json.ok_value().empty()) {
                    break;
                }
                obj[f->name()] = json.ok_value();
                break;
            }
            case FieldDescriptor::TYPE_STRING: {
                auto val = reflection->GetString(m, f);
                if (skip_default_values && val == f->default_value_string()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_ENUM: {
                auto val = reflection->GetEnum(m, f);
                if (skip_default_values && val->number() == f->default_value_enum()->number()) {
                    break;
                }
                obj[f->name()] = (int64_t)val->number();
                break;
            }
            case FieldDescriptor::TYPE_DOUBLE: {
                auto val = reflection->GetDouble(m, f);
                if (skip_default_values && val == f->default_value_double()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_FLOAT: {
                auto val = reflection->GetFloat(m, f);
                if (skip_default_values && val == f->default_value_float()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_BOOL: {
                auto val = reflection->GetBool(m, f);
                if (skip_default_values && val == f->default_value_bool()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_INT32:
            case FieldDescriptor::TYPE_SINT32:
            case FieldDescriptor::TYPE_SFIXED32: {
                auto val = reflection->GetInt32(m, f);
                if (skip_default_values && val == f->default_value_int32()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_UINT32:
            case FieldDescriptor::TYPE_FIXED32: {
                auto val = reflection->GetUInt32(m, f);
                if (skip_default_values && val == f->default_value_uint32()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_INT64:
            case FieldDescriptor::TYPE_SINT64:
            case FieldDescriptor::TYPE_SFIXED64: {
                auto val = reflection->GetInt64(m, f);
                if (skip_default_values && val == f->default_value_int64()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_UINT64:
            case FieldDescriptor::TYPE_FIXED64: {
                auto val = reflection->GetUInt64(m, f);
                if (skip_default_values && val == f->default_value_uint64()) {
                    break;
                }
                obj[f->name()] = val;
                break;
            }
            case FieldDescriptor::TYPE_BYTES:
                return result::err(error_type_conversion_not_implemented(parent_ref, "bytes"));
            case FieldDescriptor::TYPE_GROUP:
                return result::err(error_type_conversion_not_implemented(parent_ref, "group"));
        }

        return result::ok();
    }

    result_value<json> dump_fields(const std::shared_ptr<FieldRef>& parent_ref,
                                   const google::protobuf::Message& m,
                                   const bool skip_default_values)
    {
        json value{};

        const auto& descriptor = m.GetDescriptor();

        for (int i = 0; i < descriptor->field_count(); i++) {
            auto field_d = descriptor->field(i);
            auto field_ref = make_shared<FieldRef>(field_d->name(), parent_ref);

            if (field_d->is_repeated()) {
                auto merge_res
                    = dump_field_repeated(field_ref, m, field_d, value, skip_default_values);
                if (!merge_res) {
                    return result_value<json>::err(merge_res.err_value());
                }
            } else {
                auto merge_res = dump_field(field_ref, m, field_d, value, skip_default_values);
                if (!merge_res) {
                    return result_value<json>::err(merge_res.err_value());
                }
            }
        }

        return result_value<json>::ok(value);
    }
}

result proson::merge(google::protobuf::Message& m, const std::string& json_string)
{
    try {
        auto json = json::parse(json_string);
        return merge_fields(nullptr, &m, json);
    } catch (std::invalid_argument& e) {
        return result::err(error_json_parse(e.what()));
    }
}

result_value<std::string> proson::dump(const google::protobuf::Message& m,
                                       const int indent,
                                       const bool skip_default_values)
{
    return dump_fields(nullptr, m, skip_default_values).map([=](json val) {
        return val.dump(indent);
    });
}