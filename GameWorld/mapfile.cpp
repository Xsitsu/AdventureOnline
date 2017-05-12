#include "mapfile.hpp"

#include "mapwarpregular.hpp"

MapFile::MapFile() : FileBase()
{

}

MapFile::MapFile(std::string filename) : FileBase(filename)
{

}

MapFile::~MapFile()
{

}

void MapFile::Read(Map* map)
{
    this->filestream.seekg(0, this->filestream.beg);

    char signature[4];
    signature[0] = 'A';
    signature[1] = 'O';
    signature[2] = 'M';
    signature[3] = 'F';

    int version;

    this->CheckHeader(signature, &version);

    try
    {
        if (version == 1)
        {
            return this->DoReadV1(map);
        }
        else
        {
            throw FileException::FileCorrupted(this->filename);
        }
    }
    catch (std::bad_alloc& e)
    {
        throw FileException::FileCorrupted(this->filename);
    }


}

void MapFile::Write(Map* map)
{
    this->filestream.seekg(0, this->filestream.beg);

    this->DoWriteV1(map);
}

struct WarpData
{
    uint16_t x_pos;
    uint16_t y_pos;
    uint8_t warp_type;
    uint32_t targ_map_id;
    uint16_t targ_x_pos;
    uint16_t targ_y_pos;
};

void MapFile::DoReadV1(Map* map)
{
    uint32_t id = this->TryRead32();
    uint16_t width = this->TryRead16();
    uint16_t height = this->TryRead16();

    if (id != map->GetMapId())
    {
        throw FileException::FileCorrupted(this->filename);
    }

    map->size = Vector2(width, height);

    map->tiles = new MapTile*[width];
    for (uint16_t x = 0; x < width; x++)
    {
        map->tiles[x] = new MapTile[height];

        for (uint16_t y = 0; y < height; y++)
        {
            uint16_t sprite_id = this->TryRead16();
            uint8_t move_perm = this->TryRead8();

            MapTile& tile = map->tiles[x][y];
            tile.SetSpriteId(sprite_id);
            tile.SetMovementPermissions(static_cast<MapTile::MovementPermissions>(move_perm));
        }
    }

    uint16_t num_warps = this->TryRead16();
    for (uint16_t i = 0; i < num_warps; i++)
    {
        WarpData wpdt;
        wpdt.x_pos = this->TryRead16();
        wpdt.y_pos = this->TryRead16();
        wpdt.warp_type = this->TryRead8();
        wpdt.targ_map_id = this->TryRead32();
        wpdt.targ_x_pos = this->TryRead16();
        wpdt.targ_y_pos = this->TryRead16();

        MapWarpBase *warp = nullptr;

        if (wpdt.warp_type == 1)
        {
            warp = new MapWarpRegular(map, wpdt.targ_map_id, Vector2(wpdt.targ_x_pos, wpdt.targ_y_pos));
        }

        if (warp)
        {
            map->GetTile(Vector2(wpdt.x_pos, wpdt.y_pos)).SetMapWarp(warp);
        }
    }
}

void MapFile::DoWriteV1(Map* map)
{
    this->DoWrite8('A');
    this->DoWrite8('O');
    this->DoWrite8('M');
    this->DoWrite8('F');

    this->DoWrite8(1);

    uint16_t width = map->GetSize().x;
    uint16_t height = map->GetSize().y;

    this->DoWrite32(map->GetMapId());
    this->DoWrite16(width);
    this->DoWrite16(height);

    std::list<WarpData> warps;

    for (uint16_t x = 0; x < width; x++)
    {
        for (uint16_t y = 0; y < height; y++)
        {
            MapTile& tile = map->tiles[x][y];

            MapWarpBase *warp = tile.GetMapWarp();
            if (warp)
            {
                WarpData wpdt;
                wpdt.x_pos = x;
                wpdt.y_pos = y;
                wpdt.warp_type = warp->GetWarpType();
                wpdt.targ_map_id = warp->GetTargetMapId();
                wpdt.targ_x_pos = warp->GetTargetCoordinates().x;
                wpdt.targ_y_pos = warp->GetTargetCoordinates().y;

                warps.push_back(wpdt);
            }

            this->DoWrite16(tile.GetSpriteId());
            this->DoWrite8(static_cast<uint8_t>(tile.GetMovementPermissions()));
        }
    }

    this->DoWrite16((uint16_t)warps.size());

    std::list<WarpData>::iterator iter;
    for (iter = warps.begin(); iter != warps.end(); ++iter)
    {
        WarpData wpdt = *iter;

        this->DoWrite16(wpdt.x_pos);
        this->DoWrite16(wpdt.y_pos);
        this->DoWrite8(wpdt.warp_type);
        this->DoWrite32(wpdt.targ_map_id);
        this->DoWrite16(wpdt.targ_x_pos);
        this->DoWrite16(wpdt.targ_y_pos);
    }
}
