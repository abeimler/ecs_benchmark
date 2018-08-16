# Ginseng

Ginseng is an entity-component-system (ECS) library designed for use in games.

The main advantage over similar libraries is that the component types do not need to be listed or registered.
Component types are detected dynamically.

Any function-like object can be used as a system.
The function's parameters are used to determine the required components.

## Features

- Fully type safe!
- No dynamic casts.
- Type erasure; no intrusive inheritance.
- No exceptions are thrown.
- Unlimited component types.
- Systems are just regular functions.

## Status

Ginseng is currently in-development, but it already works exceptionally well.

It is not stable yet, but a 1.0 release is approaching quickly.

## Dependencies

There are none! Ginseng is a single-header library that only requires C++14.

## Example

An example of Ginseng being used in a game:

```c++
#include <ginseng/ginseng.hpp>

using ginseng::database;
using ginseng::tag;
using ginseng::deny;

// Components can be any value type.

struct NameCom {
    std::string name;
};

struct PositionCom {
    double x;
    double y;
};

// Tag components will not contain a value (no allocation).
using IsEnemyTag = tag<struct IsEnemy>;

struct Game {
    database db; // Databases are value types.
    
    Game() {
        // db.create_entity() returns an entity ID.
        auto player = db.create_entity();
        
        // db.create_component() copies the given component into the entity.
        db.create_component(player, NameCom{"The Player"});
        db.create_component(player, PositionCom{12, 42});
        
        auto enemy = db.create_entity();
        db.create_component(enemy, NameCom{"An Enemy"});
        db.create_component(enemy, PositionCom{7, 53});
        db.create_component(enemy, IsEnemyTag{});
    }
    
    void run_game() {
        // db.visit() automatically detects visitor parameters.
        db.visit([](const NameCom& name, const PositionCom& pos){
            std::cout << "Entity " << name.name
                      << " is at (" << pos.x << "," << pos.y << ")."
                      << std::endl;
        });
    
        // The Not<> annotation can be used to skip unwanted entities.
        db.visit([](const NameCom& name, deny<IsEnemyTag>){
            std::cout << name.name << " is not an enemy." << std::endl;
        });
    }
};
```

## License

MIT

See [LICENSE.txt](https://github.com/dbralir/ginseng/blob/master/LICENSE.txt).

Copyright 2015 Jeramy Harrison
