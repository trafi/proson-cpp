#include "catch.hpp"

#include "dto.pb.h"
#include <proson/proson.hpp>

using namespace proson;

TEST_CASE("proson_nested_parse_test")
{
    dto::NestedParent parent;

    SECTION("check default values")
    {
        auto res = proson::merge(&parent, "{}");

        REQUIRE(res);
        REQUIRE(!parent.has_optionalchild());
        REQUIRE(parent.has_requiredchild());
        REQUIRE(parent.children_size() == 0);
        REQUIRE(parent.repdouble_size() == 0);
        REQUIRE(parent.repfloat_size() == 0);
        REQUIRE(parent.repint32_size() == 0);
        REQUIRE(parent.repint64_size() == 0);
        REQUIRE(parent.repuint32_size() == 0);
        REQUIRE(parent.repuint64_size() == 0);
        REQUIRE(parent.repsint32_size() == 0);
        REQUIRE(parent.repsint64_size() == 0);
        REQUIRE(parent.repfixed32_size() == 0);
        REQUIRE(parent.repfixed64_size() == 0);
        REQUIRE(parent.repbool_size() == 0);
        REQUIRE(parent.repstring_size() == 0);
        REQUIRE(parent.repbytes_size() == 0);
        REQUIRE(parent.repenum_size() == 0);
    }

    SECTION("parse nested values")
    {
        auto res = proson::merge(
            &parent,
            R"({ "OptionalChild": { "x": 1.0, "y": 2.0 }, "RequiredChild": { "x": 3.0, "y": 4.0 } })");

        REQUIRE(res);
        REQUIRE(parent.has_optionalchild());
        REQUIRE(parent.has_requiredchild());

        CHECK(parent.optionalchild().x() == 1.0);
        CHECK(parent.optionalchild().y() == 2.0);
        CHECK(parent.requiredchild().x() == 3.0);
        CHECK(parent.requiredchild().y() == 4.0);
    }

    SECTION("parse repeated values")
    {
        auto res
            = proson::merge(&parent,
                            R"({ "Children": [{ "x": 1.0, "y": 2.0 }, { "x": 3.0, "y": 4.0 }]})");

        REQUIRE(res);
        REQUIRE(parent.children_size() == 2);

        CHECK(parent.children(0).x() == 1.0);
        CHECK(parent.children(0).y() == 2.0);
        CHECK(parent.children(1).x() == 3.0);
        CHECK(parent.children(1).y() == 4.0);
    }

    SECTION("parse repeated value error")
    {
        auto res
            = proson::merge(&parent,
                            R"({ "Children": [{ "x": 1.0, "y": 2.0 }, { "x": 3.0, "y": true }]})");

        REQUIRE(!res);
        REQUIRE(res.err_value().message
                == "expected type double, but found value true at Children[1].y");
    }

    SECTION("repeated double")
    {
        SECTION("parse")
        {
            auto res = proson::merge(&parent,
                                     R"({ "RepDouble": [2.0,3.0] })");

            REQUIRE(res);
            REQUIRE(parent.repdouble_size() == 2);
            CHECK(parent.repdouble(0) == 2.0);
            CHECK(parent.repdouble(1) == 3.0);
        }

        SECTION("error")
        {
            auto res = proson::merge(&parent,
                                     R"({ "RepDouble": [true] })");

            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type double, but found value true at RepDouble[0]");
        }
    }

    SECTION("repeated float")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepFloat": [ 2.0, 3.0 ] })");

        REQUIRE(res);
        REQUIRE(parent.repfloat_size() == 2);
        CHECK(parent.repfloat(0) == 2.0);
        CHECK(parent.repfloat(1) == 3.0);
    }

    SECTION("repeated int32")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepInt32": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repint32_size() == 2);
        CHECK(parent.repint32(0) == 2);
        CHECK(parent.repint32(1) == 3);
    }

    SECTION("repeated int64")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepInt64": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repint64_size() == 2);
        CHECK(parent.repint64(0) == 2);
        CHECK(parent.repint64(1) == 3);
    }

    SECTION("repeated uint32")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepUInt32": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repuint32_size() == 2);
        CHECK(parent.repuint32(0) == 2);
        CHECK(parent.repuint32(1) == 3);
    }

    SECTION("repeated uint64")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepUInt64": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repuint64_size() == 2);
        CHECK(parent.repuint64(0) == 2);
        CHECK(parent.repuint64(1) == 3);
    }

    SECTION("repeated sint32")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepSInt32": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repsint32_size() == 2);
        CHECK(parent.repsint32(0) == 2);
        CHECK(parent.repsint32(1) == 3);
    }

    SECTION("repeated sint64")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepSInt64": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repsint64_size() == 2);
        CHECK(parent.repsint64(0) == 2);
        CHECK(parent.repsint64(1) == 3);
    }

    SECTION("repeated fixed32")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepFixed32": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repfixed32_size() == 2);
        CHECK(parent.repfixed32(0) == 2);
        CHECK(parent.repfixed32(1) == 3);
    }

    SECTION("repeated uint64")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepFixed64": [ 2, 3 ] })");

        REQUIRE(res);
        REQUIRE(parent.repfixed64_size() == 2);
        CHECK(parent.repfixed64(0) == 2);
        CHECK(parent.repfixed64(1) == 3);
    }

    SECTION("repeated bool")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepBool": [ true, false ] })");

        REQUIRE(res);
        REQUIRE(parent.repbool_size() == 2);
        CHECK(parent.repbool(0));
        CHECK(!parent.repbool(1));
    }

    SECTION("repeated string")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepString": [ "hello", "world" ] })");

        REQUIRE(res);
        REQUIRE(parent.repstring_size() == 2);
        CHECK(parent.repstring(0) == "hello");
        CHECK(parent.repstring(1) == "world");
    }

    SECTION("repeated bytes")
    {
        auto res = proson::merge(&parent,
                                 R"({ "RepBytes": [ "" ] })");

        REQUIRE(!res);
    }

    SECTION("repeated enum")
    {
        SECTION("parse")
        {
            auto res = proson::merge(&parent,
                                     R"({ "RepEnum": [ 1, 3 ] })");

            REQUIRE(res);
            REQUIRE(parent.repenum_size() == 2);
            CHECK(parent.repenum(0) == dto::EnumValue::Some);
            CHECK(parent.repenum(1) == dto::EnumValue::Other);
        }

        SECTION("error")
        {
            auto res = proson::merge(&parent,
                                     R"({ "RepEnum": [ 1, 2 ] })");

            REQUIRE(!res);
            REQUIRE(res.err_value().message == "expected one of None = 0, Some = 1, Other = 3, but "
                                               "found value 2 at RepEnum[1]");
        }
    }
}