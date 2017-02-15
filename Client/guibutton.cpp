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
    SignalArgsGuiButton args;
    args.button = this;
    this->onClick.Fire(&args);
}

void GuiButton::DoMouseDown()
{
    SignalArgsGuiButton args;
    args.button = this;
    this->onMouseDown.Fire(&args);
}

void GuiButton::DoMouseUp()
{
    SignalArgsGuiButton args;
    args.button = this;
    this->onMouseUp.Fire(&args);
}

void GuiButton::DoMouseEnter()
{
    SignalArgsGuiButton args;
    args.button = this;
    this->onMouseEnter.Fire(&args);
}

void GuiButton::DoMouseLeave()
{
    SignalArgsGuiButton args;
    args.button = this;
    this->onMouseLeave.Fire(&args);
}

SignalListener GuiButton::RegisterOnClick(signal_callback callback)
{
    return this->onClick.Connect(callback);
}

SignalListener GuiButton::RegisterOnMouseDown(signal_callback callback)
{
    return this->onMouseDown.Connect(callback);
}

SignalListener GuiButton::RegisterOnMouseUp(signal_callback callback)
{
    return this->onMouseUp.Connect(callback);
}

SignalListener GuiButton::RegisterOnMouseEnter(signal_callback callback)
{
    return this->onMouseEnter.Connect(callback);
}

SignalListener GuiButton::RegisterOnMouseLeave(signal_callback callback)
{
    return this->onMouseLeave.Connect(callback);
}
