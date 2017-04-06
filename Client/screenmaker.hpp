#ifndef SCREENMAKER_HPP_INCLUDE
#define SCREENMAKER_HPP_INCLUDE

#include "GameGui/guiscreen.hpp"
#include "GameGui/guiframe.hpp"
#include "GameGui/guitextbutton.hpp"
#include "GameGui/guitextbox.hpp"


#include "GameGui/guitextlabel.hpp"
#include "GameGui/guipasswordtextbox.hpp"
#include "GameGui/guiimagelabel.hpp"
#include "GameGui/guiimagebutton.hpp"


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

class SreenMakerCharacterCreation: public AbstractScreenMaker
{
public:
    SreenMakerCharacterCreation(Game * game) : AbstractScreenMaker(game) {}
    virtual ~SreenMakerCharacterCreation() {}
    virtual GuiScreen * MakeScreen();
};
#endif // SCREENMAKER_HPP_INCLUDE
