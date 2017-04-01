#ifndef GUIFRAME_HPP_INCLUDE
#define GUIFRAME_HPP_INCLUDE

#include <unordered_map>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "guiobject.hpp"

#include "color3.hpp"

class DLL_EXPORT GuiFrame : public GuiObject
{
protected:
    virtual void DoDraw() const;

    std::unordered_map<std::string, GuiBase*> gui_id_map;

public:
    GuiFrame();
    GuiFrame(Vector2 size);
    GuiFrame(Vector2 size, Vector2 position);
    virtual ~GuiFrame();

    void SetGuiId(std::string id, GuiBase* gui);
    GuiBase* GetGuiById(std::string id);
};

#endif // GUIFRAME_HPP_INCLUDE
