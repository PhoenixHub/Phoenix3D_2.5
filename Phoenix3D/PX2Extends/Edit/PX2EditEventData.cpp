// PX2EditEventData.cpp

#include "PX2EditEventData.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
EED_CreateWindow::EED_CreateWindow() :
IsMain(false),
ID(0)
{
}
//----------------------------------------------------------------------------
EED_CreateWindow::~EED_CreateWindow()
{

}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
EED_AddMenu::EED_AddMenu()
{
	TheItemType = IT_MAIN_MENU;
}
//----------------------------------------------------------------------------
EED_AddMenu::~EED_AddMenu()
{
}
//----------------------------------------------------------------------------