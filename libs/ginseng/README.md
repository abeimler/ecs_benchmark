# Ginseng

An entity component framework designed for use in games.

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

using Ginseng::Database;
using Ginseng::Not;
using Ginseng::Tag;

// Components can be any value type.

struct NameCom {
    std::string name;
};

struct PositionCom {
    double x;
    double y;
};

// Tag components will not contain a value (no allocation).
using IsEnemyTag = Tag<struct IsEnemy>;

struct Game {
    Database db; // Databases are value types.
    
    Game() {
        // db.makeEntity() returns an entity ID.
        auto player = db.makeEntity();
        
        // db.makeComponent() copies the given component into the entity.
        db.makeComponent(player, NameCom{"The Player"});
        db.makeComponent(player, PositionCom{12, 42});
        
        auto enemy = db.makeEntity();
        db.makeComponent(enemy, NameCom{"An Enemy"});
        db.makeComponent(enemy, PositionCom{7, 53});
        db.makeComponent(enemy, IsEnemyTag{});
    }
    
    void run_game() {
        // db.visit() automatically detects visitor parameters.
        db.visit([](const NameCom& name, const PositionCom& pos){
            std::cout << "Entity " << name.name
                      << " is at (" << pos.x << "," << pos.y << ")."
                      << std::endl;
        });
    
        // The Not<> annotation can be used to skip unwanted entities.
        db.visit([](const NameCom& name, Not<IsEnemyTag>){
            std::cout << name.name << " is not an enemy." << std::endl;
        });
    }
};
```

## License

See [LICENSE.txt](https://github.com/dbralir/ginseng/blob/master/LICENSE.txt).
