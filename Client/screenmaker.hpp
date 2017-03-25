#ifndef SCREENMAKER_HPP_INCLUDE
#define SCREENMAKER_HPP_INCLUDE

#include "guiscreen.hpp"
#include "guiframe.hpp"
#include "guitextbutton.hpp"
#include "guitextbox.hpp"
#include "guitextlabel.hpp"
#include "guipasswordtextbox.hpp"
#include "guiimagelabel.hpp"
#include "guiimagebutton.hpp"

#include "game.hpp"
#include "observer.hpp"

class AbstractScreenMaker
{
protected:
    Game* game;

public:
    AbstractScreenMaker(Game* game) : game(game) {}
    virtual ~AbstractScreenMaker() {}
    virtual GuiScreen* MakeScreen() = 0;
};


class ScreenMakerEmpty : public AbstractScreenMaker
{
public:
    ScreenMakerEmpty(Game* game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerEmpty() {}
    virtual GuiScreen* MakeScreen();
};

class ScreenMakerTitle : public AbstractScreenMaker
{
public:
    ScreenMakerTitle(Game* game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerTitle() {}
    virtual GuiScreen* MakeScreen();
};


class ScreenMakerAccountCreation : public AbstractScreenMaker
{
public:
    ScreenMakerAccountCreation(Game* game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerAccountCreation() {}
    virtual GuiScreen* MakeScreen();
};

class ScreenMakerAccountCreationResponseWait : public AbstractScreenMaker
{
public :
    ScreenMakerAccountCreationResponseWait(Game * game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerAccountCreationResponseWait() {}
    virtual GuiScreen * MakeScreen();
};


class ScreenMakerLogin : public AbstractScreenMaker
{
public:
    ScreenMakerLogin(Game* game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerLogin() {}
    virtual GuiScreen* MakeScreen();
};


class ScreenMakerCharacterView : public AbstractScreenMaker
{
public:
    ScreenMakerCharacterView(Game* game) : AbstractScreenMaker(game) {}
    virtual ~ScreenMakerCharacterView() {}
    virtual GuiScreen* MakeScreen();
};
#endif // SCREENMAKER_HPP_INCLUDE
