# MercatorTile

Spherical mercator tile and coordinate utilities for [C++](https://en.cppreference.com/w/).

The tools provides `ul` function that return the upper left corner longitudes and latitudes, a `bounds` function return the bounding longitudes and latitudes, a `xy` function that return the spherical mercator x and y coordinates, a `tile` function that returns the tile containing a given point. And lots of other usful functions.

You can check out the [Utility Functions](#utility-functions) or [examples](./examples/example.cpp).


# How to use

```C++
#include "MercatorTile.h"
using namespace mercatortile;

LngLat ul_result = ul(Tile{3425, 1549, 12});
cout<<"lng: "<<ul_result.lng<<" lat:"<<ul_result.lat<<"\n"<<endl;

Tile tile = mercatortile::tile(120.32, 43.5, 10);

Tile ttile = tile(lng, lat, 4);
cout<<ttile.x<<" "<<ttile.y<<" "<<ttile.z<<endl;
```

# Data Structures
- `struct Tile {x,y,z}` defines an XYZ web mercator tile. `x` for column number, `y` for row number, `z` for zoom level.

- `struct LngLat {lng, lat}` defines a longitude and latitude pair.

- `struct XY {x, y}` defines a x and y pair of web mercator.

- `struct Bbox {west, sourth, east, north}` defines a web mercator bounding box.

- `struct LngLatBbox {left, bottom, right, top}` defines a geographic bounding box, value should be longitude and latitude.


# Utility Functions

- `ul(const Tile &tile) -> LngLat`: get the upper left longitude and latitude of a tile.

- `bounds(const Tile &tile) -> LngLatBbox`: get the lonlat bounding box of a tile.

- `xy(const double &lng, const double &lat)->XY`: convert longtitude and latitude to web mercator x, y.

- `lonlat(const double &x, const double &y) -> LngLat`: convert  web mercator x, y to longtitude and latitude.

- `xy_bounds(const Tile &tile) -> Bbox`: get the web mercator bounding box of a tile.

- `tile(const double &lng, const double &lat, const int &zoom) -> Tile`: get the tile containing a longitude and latitude.

- `parent(const Tile &tile) -> Tile`: get the parent tile of a tile.
- `parent(const Tile &tile, const int &zoom) -> TIle`: get the parent tile of a tile.

- `children(const Tile &tile) -> std::vector<Tile>`: get the children of a tile.
- `children(const Tile &tile, const int &zoom) -> std::vector<Tile>`: get the children of a tile.

- `tiles(const LngLatBbox &bbox, const int &zoom) -> std::vector<Tile>`: get the tiles intersecting a geographic bounding box.

- `quadkey(const Tile &tile) -> std::string`:  get the quadkey of a tile.

- `quadkey_to_tile(const std::string &qk) -> Tile`: get the tile corresponding to a quadkey.

# Install
```
mkdir build && cd build
cmake ..
make
make install
```

# Reference

- [https://github.com/mapbox/mercantile](https://github.com/mapbox/mercantile)