#include "mapfile.hpp"

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

void MapFile::DoReadV1(Map* map)
{
    uint32_t id = this->TryRead32();
    uint16_t width = this->TryRead16();
    uint16_t height = this->TryRead16();

    if (id != map->GetMapId())
    {
        //throw FileException::FileCorrupted(this->filename);
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

    for (uint16_t x = 0; x < width; x++)
    {
        for (uint16_t y = 0; y < height; y++)
        {
            MapTile& tile = map->tiles[x][y];
            this->DoWrite16(tile.GetSpriteId());
            this->DoWrite8(static_cast<uint8_t>(tile.GetMovementPermissions()));
        }
    }
}
