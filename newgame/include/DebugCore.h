#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Object.h"
#include "Core.h"

using namespace fc;
using namespace sf;
class DebugCore {
public:
	RenderWindow* debugWindow;
	Core* gameCore;
	Image* image;
	Font* font;
	tgui::Gui* debugGui;
	DebugCore(Core* gameCore, Image* image, Font* fnt);
	void Render();
	void Update();
};
