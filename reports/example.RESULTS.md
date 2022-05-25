# Results

## TL;DR Results

![Summary SystemsUpdate Plot](img/SystemsUpdate.png)
_(lower is better)_

|                                     | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Update  10k entities with 2 Systems | 0.0008s   | 0.0002s | 0.0002s   | 0.0007s    | 0.0005s |
| Update 100k entities with 2 Systems | 0.0092s   | 0.0023s | 0.0026s   | 0.0070s    | 0.0057s |
| Update 500k entities with 2 Systems | 0.0401s   | 0.0127s | 0.0140s   | 0.0334s    | 0.0198s |
| Update   1M entities with 2 Systems | 0.0796s   | 0.0240s | 0.0243s   | 0.0631s    | 0.0557s |

## Details


### Environment

* **OS:** Linux
* **CPU:** 3.10GHz@4Cores
* **RAM:** 7.64GB

### More Results

#### Create Entities

![CreateEntities Plot](img/CreateEntities.png)
_(lower is better)_

|                                          | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:-----------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Create  10k entities with two Components | 0.0007s   | 0.0002s | 0.0008s   | 0.0004s    | 0.0000s |
| Create 100k entities with two Components | 0.0064s   | 0.0021s | 0.0084s   | 0.0034s    | 0.0004s |
| Create 500k entities with two Components | 0.0369s   | 0.0106s | 0.0438s   | 0.0169s    | 0.0013s |
| Create   1M entities with two Components | 0.0763s   | 0.0213s | 0.0944s   | 0.0380s    | 0.0026s |


#### Destroy Entities

![DestroyEntities Plot](img/DestroyEntities.png)
_(lower is better)_

|                                           | EntityX   | EnTT    | Ginseng   | mustache   | OOP       |
|:------------------------------------------|:----------|:--------|:----------|:-----------|:----------|
| Destroy  10k entities with two Components | 0.0003s   | 0.0003s | 0.0012s   | 0.0002s    | 0.2422s   |
| Destroy 100k entities with two Components | 0.0034s   | 0.0033s | 0.0119s   | 0.0018s    | 15.5223s  |
| Destroy 500k entities with two Components | 0.0166s   | 0.0172s | 0.0633s   | 0.0091s    | 719.3013s |


#### Get one component from Entity

![UnpackOneComponent Plot](img/UnpackOneComponent.png)
_(lower is better)_

|                                       | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:--------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack one Component in  10k entities | 0.0000s   | 0.0001s | 0.0001s   | 0.0002s    | 0.0000s |
| Unpack one Component in 100k entities | 0.0005s   | 0.0009s | 0.0006s   | 0.0020s    | 0.0006s |
| Unpack one Component in 500k entities | 0.0027s   | 0.0057s | 0.0040s   | 0.0104s    | 0.0051s |
| Unpack one Component in   1M entities | 0.0053s   | 0.0109s | 0.0073s   | 0.0215s    | 0.0074s |


#### Get two components from Entity

![UnpackTwoComponents Plot](img/UnpackTwoComponents.png)
_(lower is better)_

|                                        | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:---------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack two Components in  10k entities | 0.0001s   | 0.0002s | 0.0001s   | 0.0004s    | 0.0000s |
| Unpack two Components in 100k entities | 0.0012s   | 0.0020s | 0.0012s   | 0.0037s    | 0.0003s |
| Unpack two Components in 500k entities | 0.0061s   | 0.0091s | 0.0062s   | 0.0190s    | 0.0040s |
| Unpack two Components in   1M entities | 0.0119s   | 0.0209s | 0.0140s   | 0.0382s    | 0.0078s |


#### Get three components from Entity

![UnpackThreeComponentsFromMixedEntities Plot](img/UnpackThreeComponentsFromMixedEntities.png)
_(lower is better)_

|                                          | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:-----------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Unpack three Components in  10k entities | 0.0002s   | 0.0002s | 0.0002s   | 0.0005s    | 0.0000s |
| Unpack three Components in 100k entities | 0.0019s   | 0.0028s | 0.0019s   | 0.0061s    | 0.0003s |
| Unpack three Components in 500k entities | 0.0083s   | 0.0155s | 0.0096s   | 0.0291s    | 0.0046s |
| Unpack three Components in   1M entities | 0.0180s   | 0.0270s | 0.0191s   | 0.0603s    | 0.0107s |


#### System Updates (for-each entities)

![SystemsUpdate Plot](img/SystemsUpdate.png)
_(lower is better)_

|                                     | EntityX   | EnTT    | Ginseng   | mustache   | OOP     |
|:------------------------------------|:----------|:--------|:----------|:-----------|:--------|
| Update  10k entities with 2 Systems | 0.0008s   | 0.0002s | 0.0002s   | 0.0007s    | 0.0005s |
| Update 100k entities with 2 Systems | 0.0092s   | 0.0023s | 0.0026s   | 0.0070s    | 0.0057s |
| Update 500k entities with 2 Systems | 0.0401s   | 0.0127s | 0.0140s   | 0.0334s    | 0.0198s |
| Update   1M entities with 2 Systems | 0.0796s   | 0.0240s | 0.0243s   | 0.0631s    | 0.0557s |

