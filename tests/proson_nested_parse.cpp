#include "catch.hpp"

#include "dto.pb.h"
#include <proson.hpp>

using namespace proson;

TEST_CASE("proson_nested_parse")
{
    dto::NestedParent parent;

    SECTION("check default values")
    {
        auto res = proson::merge(&parent, "{}");

        REQUIRE(res);
        REQUIRE(!parent.has_optional_child());
        REQUIRE(parent.has_required_child());
        REQUIRE(parent.childs_size() == 0);
    }

    SECTION("parse nested values")
    {
        auto res = proson::merge(&parent,
                                 "{ \"optional_child\": { \"x\": 1.0, \"y\": 2.0 }, "
                                 "\"required_child\": { \"x\": 3.0, \"y\": 4.0 } }");

        REQUIRE(res);
        REQUIRE(parent.has_optional_child());
        REQUIRE(parent.has_required_child());

        CHECK(parent.optional_child().x() == 1.0);
        CHECK(parent.optional_child().y() == 2.0);
        CHECK(parent.required_child().x() == 3.0);
        CHECK(parent.required_child().y() == 4.0);
    }

    SECTION("parse repeated values")
    {
        auto res = proson::merge(&parent,
                                 "{ \"childs\": "
                                 "["
                                 "{ \"x\": 1.0, \"y\": 2.0 }, "
                                 "{ \"x\": 3.0, \"y\": 4.0 } "
                                 "]"
                                 "}");

        REQUIRE(res);
        REQUIRE(parent.childs_size() == 2);

        CHECK(parent.childs(0).x() == 1.0);
        CHECK(parent.childs(0).y() == 2.0);
        CHECK(parent.childs(1).x() == 3.0);
        CHECK(parent.childs(1).y() == 4.0);
    }
}