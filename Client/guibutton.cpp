#include "guibutton.hpp"

#include <iostream>

GuiButton::GuiButton() : GuiFrame()
{}

GuiButton::GuiButton(Vector2 size) : GuiFrame(size)
{}

GuiButton::GuiButton(Vector2 size, Vector2 position) : GuiFrame(size, position)
{}

GuiButton::~GuiButton()
{

}

void GuiButton::DoClick()
{
    GuiButtonArgs args;
    args.button = this;
    this->onClick.Fire(&args);
}

void GuiButton::DoMouseDown()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseDown.Fire(&args);
}

void GuiButton::DoMouseUp()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseUp.Fire(&args);
}

void GuiButton::DoMouseEnter()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseEnter.Fire(&args);
}

void GuiButton::DoMouseLeave()
{
    GuiButtonArgs args;
    args.button = this;
    this->onMouseLeave.Fire(&args);
}

void GuiButton::RegisterOnClick(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onClick.Connect(listener);
}

void GuiButton::RegisterOnMouseDown(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseDown.Connect(listener);
}

void GuiButton::RegisterOnMouseUp(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseUp.Connect(listener);
}

void GuiButton::RegisterOnMouseEnter(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseEnter.Connect(listener);
}

void GuiButton::RegisterOnMouseLeave(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseLeave.Connect(listener);
}

void GuiButton::UnregisterOnClick(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onClick.Disconnect(listener);
}

void GuiButton::UnregisterOnMouseDown(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseDown.Disconnect(listener);
}

void GuiButton::UnregisterOnMouseUp(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseUp.Disconnect(listener);
}

void GuiButton::UnregisterOnMouseEnter(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseEnter.Disconnect(listener);
}

void GuiButton::UnregisterOnMouseLeave(ListenerBase<GuiButtonArgs*>* listener)
{
    this->onMouseLeave.Disconnect(listener);
}
