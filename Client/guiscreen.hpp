#ifndef GUISCREEN_HPP_INCLUDE
#define GUISCREEN_HPP_INCLUDE

#include "guibase.hpp"
#include "guibutton.hpp"
#include "guitextbox.hpp"

#include "guiselectionservice.hpp"

#include "GameShared/vector2.hpp"

#include <iostream>

class GuiScreen
{
protected:
    GuiBase* base;
    std::list<GuiBase*> interaction_guis;

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
};

#endif // GUISCREEN_HPP_INCLUDE
