#!/bin/bash

git subtree pull --prefix libs/anax https://github.com/miguelmartin75/anax.git master --squash 
git subtree pull --prefix libs/Artemis-Cpp https://github.com/vinova/Artemis-Cpp.git master --squash 

git subtree pull --prefix libs/entityx1 https://github.com/alecthomas/entityx.git master --squash 
git subtree pull --prefix libs/entityx2 https://github.com/alecthomas/entityx.git experimental/compile_time --squash 

git subtree pull --prefix libs/entt https://github.com/skypjack/entt.git master --squash
git subtree pull --prefix libs/eventpp https://github.com/abeimler/eventpp master --squash 

git subtree pull --prefix libs/ginseng https://github.com/apples/ginseng.git master --squash 

## repo is not uptodate
#git subtree pull --prefix libs/benchpress https://github.com/abeimler/benchpress master --squash 

