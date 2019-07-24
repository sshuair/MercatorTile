#include "MercatorTile.h"
#include <iostream>
#include <deque>
#include <math.h>

using namespace std;
using namespace mercatortile;

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    vector<int> a = {1,2,3,4};
    cout<<a.front();
    a.erase(a.begin());
    for (auto x:a)
    {
        std::cout<<x<<endl;
    }
    

    // float n = pow(2,3);
    // std::cout<<n<<endl;

    // LngLat aa;
    // cout<<aa.lng<<endl;
    // float lng = 120;
    // float lat = 40;
    // float x;
    // float y;
    // mercatortile::xy(lng, lat, &x, &y);
    // std::cout<<x<<std::endl;
    // std::cout<<y<<std::endl;

    // float truct_lng = 120;
    // float truct_lat = 120;
    // mercatortile::truncate_lonlat(&truct_lng, &truct_lat);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;

    // float truct_lng = 120;
    // float truct_lat = 120;
    // // mercatortile::lonlat(&x, &y,);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;
   
    // // check function ul
    // mercatortile::Tile tile = {0,0,1};
    // mercatortile::LngLat lnglat = {0,0};
    // mercatortile::ul(tile, &lnglat);
    // cout<<lnglat.lng<<"  "<<lnglat.lat<<endl;

    // check function bounds
    // mercatortile::Tile tile = {0,0,0};
    // mercatortile::LngLatBbox llbbox = {0,0};
    // mercatortile::bounds(tile, &llbbox);
    // cout<<llbbox.west<<"  "<<llbbox.south<<" "<< llbbox.east <<" "<<llbbox.north<<endl;
// parent
    // Tile tile {230,439,8};
    // Tile parent_tile = mercatortile::parent(tile, 4);
    // cout<<parent_tile.x<<endl;
    // cout<<parent_tile.y<<endl;
    // cout<<parent_tile.z<<endl;

// child - 1 level
    // cout<<"example - [child]: "<<endl;
    // Tile tile {230,439,8};
    // vector<Tile> child_tiles = mercatortile::child(tile);
    // for (const auto &child:child_tiles){
    //     cout<<child.x<<endl;
    //     cout<<child.y<<endl;
    //     cout<<child.z<<endl;
    //     cout<<endl;
    // };

// child - n level
    cout<<"example - [child]: "<<endl;
    Tile tile {1,1,5};
    std::vector<Tile> child_tiles = mercatortile::child(tile, 18);
    for (const auto &child:child_tiles){
        cout<<child.x<<endl;
        cout<<child.y<<endl;
        cout<<child.z<<endl;
        cout<<endl;
    };

    return 0;
};