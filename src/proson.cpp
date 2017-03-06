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
            return result::err(error_json_field_invalid_type(field_ref, "array", j.dump()));
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
                case FieldDescriptor::Type::TYPE_STRING: {
                    merge_res = to_string(array_val_ref, array_val)
                                    .map([&](string val) {
                                        reflection->AddString(m, f, val);
                                        return val;
                                    })
                                    .map_void();
                    break;
                }
                case FieldDescriptor::TYPE_ENUM:
                case FieldDescriptor::Type::TYPE_DOUBLE:
                case FieldDescriptor::Type::TYPE_FLOAT:
                case FieldDescriptor::Type::TYPE_BOOL:
                case FieldDescriptor::Type::TYPE_INT32:
                case FieldDescriptor::Type::TYPE_SINT32:
                case FieldDescriptor::Type::TYPE_SFIXED32:
                case FieldDescriptor::Type::TYPE_UINT32:
                case FieldDescriptor::Type::TYPE_FIXED32:
                case FieldDescriptor::Type::TYPE_INT64:
                case FieldDescriptor::Type::TYPE_SINT64:
                case FieldDescriptor::Type::TYPE_SFIXED64:
                case FieldDescriptor::Type::TYPE_UINT64:
                case FieldDescriptor::Type::TYPE_FIXED64:
                case FieldDescriptor::Type::TYPE_BYTES:
                case FieldDescriptor::TYPE_GROUP:
                    break;
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
            case FieldDescriptor::TYPE_MESSAGE:
                return merge_fields(field_ref, reflection->MutableMessage(m, f), *it);
            case FieldDescriptor::Type::TYPE_STRING:
                return to_string(field_ref, *it)
                    .map([&](string val) {
                        reflection->SetString(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::TYPE_ENUM:
                return to_enum_int(field_ref, *it)
                    .and_then([&](int number) {
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
                            return result_value<int>::err(error_json_field_invalid_enum_value_type(
                                field_ref, number, enum_type));
                        }
                        reflection->SetEnum(m, f, value_type);
                        return result_value<int>::ok(number);
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_DOUBLE:
                return to_double(field_ref, *it)
                    .map([&](double val) {
                        reflection->SetDouble(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_FLOAT:
                return to_double(field_ref, *it)
                    .map([&](double val) {
                        reflection->SetFloat(m, f, (float)val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_BOOL:
                return to_bool(field_ref, *it)
                    .map([&](bool val) {
                        reflection->SetBool(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_INT32:
            case FieldDescriptor::Type::TYPE_SINT32:
            case FieldDescriptor::Type::TYPE_SFIXED32:
                return to_int32(field_ref, *it)
                    .map([&](int32_t val) {
                        reflection->SetInt32(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_UINT32:
            case FieldDescriptor::Type::TYPE_FIXED32:
                return to_uint32(field_ref, *it)
                    .map([&](uint32_t val) {
                        reflection->SetUInt32(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_INT64:
            case FieldDescriptor::Type::TYPE_SINT64:
            case FieldDescriptor::Type::TYPE_SFIXED64:
                return to_int64(field_ref, *it)
                    .map([&](int64_t val) {
                        reflection->SetInt64(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_UINT64:
            case FieldDescriptor::Type::TYPE_FIXED64:
                return to_uint64(field_ref, *it)
                    .map([&](uint64_t val) {
                        reflection->SetUInt64(m, f, val);
                        return val;
                    })
                    .map_void();
            case FieldDescriptor::Type::TYPE_BYTES:
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
            result::err(error_json_field_is_not_an_object(parent_ref));
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
}

result proson::merge(google::protobuf::Message* m, const std::string& json_string)
{
    try {
        auto json = json::parse(json_string);
        return merge_fields(nullptr, m, json);
    } catch (std::invalid_argument& e) {
        return result::err(error_json_parse(e.what()));
    }
}
