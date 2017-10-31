#include "catch.hpp"

#include <ginseng/ginseng.hpp>

using DB = Ginseng::Database;
using Ginseng::Not;
using Ginseng::Tag;
using Ginseng::Maybe;
using EntID = DB::EntID;
using ComID = DB::ComID;

TEST_CASE("Tag types do not use dynamic allocation", "[ginseng]")
{
    // Not sure how to actually test this, since allocations happen for the list nodes and entity vector.
    // Instead, I'll just check to make sure it actually compiles.

    DB db;

    struct SomeTag {};
    struct SomeTag2 {};

    auto ent = db.makeEntity();
    db.makeComponent(ent, Tag<SomeTag>{});

    int visited;

    visited = 0;
    db.visit([&](Tag<SomeTag>){
        ++visited;
    });
    REQUIRE(visited == 1);

    visited = 0;
    db.visit([&](Tag<SomeTag2>){
        ++visited;
    });
    REQUIRE(visited == 0);

    Maybe<Tag<SomeTag>> minfo;
    visited = 0;
    db.visit([&](Maybe<Tag<SomeTag>> info){
        ++visited;
        minfo = info;
    });
    REQUIRE(visited == 1);
    REQUIRE(bool(minfo) == true);
    
    Maybe<Tag<SomeTag2>> minfo2;
    visited = 0;
    db.visit([&](Maybe<Tag<SomeTag2>> info){
        ++visited;
        minfo2 = info;
    });
    REQUIRE(visited == 1);
    REQUIRE(bool(minfo2) == false);
}