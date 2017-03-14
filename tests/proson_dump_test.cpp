#include "catch.hpp"

#include "example_dto.pb.h"
#include <json.hpp>
#include <proson/proson.hpp>

using namespace proson;
using namespace example_dto;
using namespace nlohmann;

TEST_CASE("proson_dump_test")
{
    Servo servo;

    auto merge_ok = proson::merge(servo, R"json(
        {
            "targets": [
                {
                    "updated_at": 1434555532,
                    "pos": {
                        "x": 3,
                        "y": 5
                    }
                },
                {
                    "updated_at": 1437234456,
                    "pos": {
                        "x": 5,
                        "y": 9
                    }
                }
            ],
            "rpm": 400.0,
            "air": 5
        }
    )json");

    auto dumped = proson::dump(servo);

    REQUIRE(dumped);
    std::string dumped_json = json(dumped.ok_value());

    // clang-format off
    std::string expected_json
        = json({
            {"rpm", 400.0},
            {"targets", {
                {
                    {"pos", {
                        {"x", 3.0},
                        {"y", 5.0}
                    }},
                    {"updated_at", 1434555532}
                },
                {
                    {"pos", {
                        {"x", 5.0},
                        {"y", 9.0}
                    }},
                    {"updated_at", 1437234456}
                }
            }}
        }).dump();
    // clang-format on

    REQUIRE(dumped_json == expected_json);
}