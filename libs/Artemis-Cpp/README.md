Artemis C++
===

A C++ port of [Artemis Entity System Framework](http://gamadu.com/artemis/tutorial.html).

The port was orignially written by [Sidar Talei](https://bitbucket.org/stalei/artemiscpp/src), in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc…
We wanted the framework to be portable, so we removed all C++11 feature usages.

## Compiling

### CMake

CMake is a cross-platform, open source build system. You can find more information about CMake [here](https://www.google.es/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&ved=0CDcQFjAA&url=http%3A%2F%2Fwww.cmake.org%2F&ei=ZRhEUtGFA6el4ATa64HIBw&usg=AFQjCNEmd4p8aUoUmYlZxJdYtwYJnn1-cw&sig2=rna57CyVBIF9Oxh-i-_4FQ&bvm=bv.53217764,d.bGE).

It is very simple to compile Artemis-Cpp using CMake. Just follow these steps:

1. Install CMake in your system.
2. Make sure you have cmake in your `$PATH` variable.
3. Open a new terminal and go to Artemis-Cpp's folder.
4. `mkdir build`.
5. `cd build`.
6. `cmake ..`.
7. `make`.
8. `sudo make install`.
9. Enjoy.

### Mac OS X Framework

You can use Artemis-Cpp as a Framework for Mac OS X development using the _Artemis.framework_ we provide or compile your own Framework using the XCode project inside the _XCode_ folder.

### PORTED CLASSES

- Component
- ComponentMapper
- ComponentType
- ComponentTypeManager
- Entity
- EntityProcessingSystem
- EntitySystem
- SystemBitManager
- ImmutableBag
- EntityManager
- DelayedEntityProcessingSystem
- DelayedEntitySystem
- GroupManager
- IntervalEntityProcessingSystem
- IntervalEntitySystem
- Manager
- SystemManager
- TagManager
- utils
- World
- Bag

### EXAMPLE

`VelocityComponent` and `PositionComponent`.

``` cpp
class VelocityComponent : public artemis::Component {
public:
    float velocityX;
    float velocityY;

    VelocityComponent(float velocityX, float velocityY)
    {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
    };
};

class PositionComponent : public artemis::Component
{

public:
    float posX;
    float posY;
    PositionComponent(float posX, float posY)
    {
        this->posX = posX;
        this->posY = posY;
    };
};
```
	
MovementSystem updates positions base on velocities

``` cpp
class MovementSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<MovementComponent> velocityMapper;
    artemis::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        addComponentType<VelocityComponent>();
        addComponentType<PositionComponent>();
    };

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    };

    virtual void processEntity(artemis::Entity &e) {
        positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
        positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
    };

};
```
	
Usage:

``` cpp
int main(int argc, char **argv) {

    artemis::World world;
    artemis::SystemManager * sm = world.getSystemManager();
    MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
    artemis::EntityManager * em = world.getEntityManager();

    sm->initializeAll();

    artemis::Entity & player = em->create();

    player.addComponent(new MovementComponent(2,4));
    player.addComponent(new PositionComponent(0,0));
    player.refresh();

    PositionComponent * comp = (PositionComponent*)player.getComponent<PositionComponent>();

    while(true){

        world.loopStart();
        world.setDelta(0.0016f);
        movementsys->process();

        std::cout << "X:"<< comp->posX << std::endl;
        std::cout << "Y:"<< comp->posY << std::endl;
        Sleep(160);
    }

    return 0;
}
```
### LOGS
- Dec 10, 2012:
	- [Fixed  bug](https://github.com/vinova/Artemis-Cpp/commit/449ee9d3167d6bdf8056a8da7554ebec016e5b65): calling Bag.get(index) not returning NULL when index > bag's size,
	which leads to memory violation when the number of entities becomes greater than initialized entities bag size.
- Nov 15, 2012:
	- [Fixed  bug](https://github.com/vinova/Artemis-Cpp/commit/fe291598b699cd283fc029ee727669b8e7a76e24): memory leak when add a component to an entity
	who already had this component.
- Sept 11, 2012:
	- [Fixed critical bug](https://github.com/vinova/Artemis-Cpp/commit/731d2c3e6f4afbd32e4d33f08f23373d62b91dd9): deleting World doesn't delete/reset all neccessary data,
which will lead to memory violation when a World is deleted and a new one is created.
- Sept 12, 2012:
	- Removed all C++11 feature usages.

### LISENCE

Copyright 2011 GAMADU.COM. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY GAMADU.COM ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL GAMADU.COM OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of GAMADU.COM.
