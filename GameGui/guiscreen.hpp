#ifndef GUISCREEN_HPP_INCLUDE
#define GUISCREEN_HPP_INCLUDE

#include "guibase.hpp"
#include "guibutton.hpp"
#include "guitextbox.hpp"

#include "guiselectionservice.hpp"

#include "GameUtil/vector2.hpp"

#include "observer.hpp"

#include <unordered_map>

class
#ifdef WINDOWS
DLL_EXPORT
#endif
GuiScreen
{
protected:
    GuiBase* base;
    std::list<GuiBase*> interaction_guis;
    std::unordered_map<std::string, GuiBase*> gui_id_map;

    std::list<AbstractListener*> listeners;

    void RemoveInteractionGui(GuiBase* gui);
    GuiBase* FindGuiCoveringPoint(const Vector2& pos);

    void ParseChild(GuiBase* base);
    void PopulateListFromStructureParse();

public:
    GuiScreen(GuiBase* base);
    ~GuiScreen();

    bool HandleMouseDown(const Vector2& pos);
    bool HandleMouseUp(const Vector2& pos);
    bool HandleMouseMove(const Vector2& pos);

    void Draw();

    void SetGuiId(std::string id, GuiBase* gui);
    GuiBase* GetGuiById(std::string id);

    void RegisterListener(AbstractListener* listener);
};

#endif // GUISCREEN_HPP_INCLUDE
