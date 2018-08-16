#include "catch.hpp"

#include <ginseng/ginseng.hpp>

using DB = ginseng::database;
using ginseng::deny;
using ginseng::tag;
using ginseng::optional;
using ent_id = DB::ent_id;
using com_id = DB::com_id;

TEST_CASE("tag types do deny use dynamic allocation", "[ginseng]")
{
    // Not sure how to actually test this.
    // Instead, I'll just check to make sure it actually compiles.

    DB db;

    struct Sometag {};
    struct Sometag2 {};

    auto ent = db.create_entity();
    db.create_component(ent, tag<Sometag>{});

    int visited;

    visited = 0;
    db.visit([&](tag<Sometag>){
        ++visited;
    });
    REQUIRE(visited == 1);

    visited = 0;
    db.visit([&](tag<Sometag2>){
        ++visited;
    });
    REQUIRE(visited == 0);

    optional<tag<Sometag>> minfo;
    visited = 0;
    db.visit([&](optional<tag<Sometag>> info){
        ++visited;
        minfo = info;
    });
    REQUIRE(visited == 1);
    REQUIRE(bool(minfo) == true);
    
    optional<tag<Sometag2>> minfo2;
    visited = 0;
    db.visit([&](optional<tag<Sometag2>> info){
        ++visited;
        minfo2 = info;
    });
    REQUIRE(visited == 1);
    REQUIRE(bool(minfo2) == false);
}
