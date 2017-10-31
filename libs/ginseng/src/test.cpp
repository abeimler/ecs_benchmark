#include "catch.hpp"

#include <ginseng/ginseng.hpp>

#include <array>
#include <memory>

using DB = Ginseng::Database;
using Ginseng::Not;
using Ginseng::Maybe;
using EntID = DB::EntID;
using ComID = DB::ComID;

TEST_CASE("Entities can be added and removed from a database", "[ginseng]")
{
    DB db;
    REQUIRE(db.size() == 0);

    EntID ent1 = db.makeEntity();
    REQUIRE(db.size() == 1);

    EntID ent2 = db.makeEntity();
    REQUIRE(db.size() == 2);

    db.eraseEntity(ent2);
    REQUIRE(db.size() == 1);

    db.eraseEntity(ent1);
    REQUIRE(db.size() == 0);
}

TEST_CASE("Components can be added, accessed, and removed from entities", "[ginseng]")
{
    DB db;
    auto ent = db.makeEntity();

    struct ComA {
        int x;
    };
    struct ComB {
        double y;
    };

    db.makeComponent(ent, ComA{7});
    REQUIRE(db.hasComponent<ComA>(ent) == true);
    ComA *com1ptr1 = &db.getComponent<ComA>(ent);
    REQUIRE(com1ptr1 != nullptr);

    db.makeComponent(ent, ComB{4.2});
    REQUIRE(db.hasComponent<ComB>(ent) == true);
    ComB *com2ptr1 = &db.getComponent<ComB>(ent);
    REQUIRE(com2ptr1 != nullptr);

    REQUIRE(&db.getComponent<ComA>(ent) == com1ptr1);
    REQUIRE(db.getComponent<ComA>(ent).x == 7);

    REQUIRE(&db.getComponent<ComB>(ent) == com2ptr1);
    REQUIRE(db.getComponent<ComB>(ent).y == 4.2);

    db.eraseComponent<ComA>(ent);

    REQUIRE(&db.getComponent<ComB>(ent) == com2ptr1);
    REQUIRE(db.getComponent<ComB>(ent).y == 4.2);

    db.eraseComponent<ComB>(ent);
}

TEST_CASE("Databases can visit entities with specific components", "[ginseng]")
{
    DB db;

    struct ID { int id; };
    struct Data1 { double val; };
    struct Data2 { std::unique_ptr<int> no_move; };

    int next_id = 0;

    auto make_ent = [&](bool give_Data1, bool give_Data2)
    {
        auto ent = db.makeEntity();
        db.makeComponent(ent, ID{next_id});
        ++next_id;
        if (give_Data1) { db.makeComponent(ent, Data1{7}); }
        if (give_Data2) { db.makeComponent(ent, Data2{nullptr}); }
        return ent;
    };

    make_ent(false, false);
    make_ent(true, false);
    make_ent(true, false);
    make_ent(false, true);
    make_ent(false, true);
    make_ent(false, true);
    make_ent(true, true);
    make_ent(true, true);
    make_ent(true, true);
    make_ent(true, true);

    REQUIRE(next_id == 10);
    REQUIRE(db.size() == next_id);

    std::array<int,10> visited;
    std::array<int,10> expected_visited;

    visited = {};
    expected_visited = {{1,1,1,1,1,1,1,1,1,1}};
    db.visit([&](ID& id){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{0,1,1,0,0,0,1,1,1,1}};
    db.visit([&](ID& id, Data1&){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{0,0,0,1,1,1,1,1,1,1}};
    db.visit([&](ID& id, Data2&){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{0,0,0,0,0,0,1,1,1,1}};
    db.visit([&](ID& id, Data1&, Data2&){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{1,0,0,1,1,1,0,0,0,0}};
    db.visit([&](ID& id, Not<Data1>){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{0,0,0,1,1,1,0,0,0,0}};
    db.visit([&](ID& id, Not<Data1>, Data2&){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{0,1,1,0,0,0,0,0,0,0}};
    db.visit([&](ID& id, Data1&, Not<Data2>){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    visited = {};
    expected_visited = {{1,0,0,0,0,0,0,0,0,0}};
    db.visit([&](ID& id, Not<Data1>, Not<Data2>){
        ++visited[id.id];
    });
    REQUIRE(visited == expected_visited);

    int num_visited = 0;
    db.visit([&](Not<ID>){
        ++num_visited;
    });
    REQUIRE(num_visited == 0);
}

TEST_CASE("Maybe can be used instead of components", "[ginseng]")
{
    DB db;

    struct Data {};
    struct Data2 {};

    auto ent = db.makeEntity();
    db.makeComponent(ent,Data{});

    int visited = 0;
    Maybe<Data> mdata;
    Maybe<Data2> mdata2;
    db.visit([&](Maybe<Data> data, Maybe<Data2> data2){
        ++visited;
        mdata = data;
        mdata2 = data2;
    });
    REQUIRE(visited == 1);
    REQUIRE(bool(mdata) == true);
    REQUIRE(bool(mdata2) == false);
}

