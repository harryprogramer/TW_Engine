#include "game/engine/TheWall.h"
#include "game/engine/sounds/step.h"
#include "game/levels/Menu.h"
#include "game/engine/Events.h"
#include "game/engine/launcher/NetSock.h"
#include "game/engine/core/TitleEffect.h";
#include <windows.h>
#include <thread>

#include "game/engine/sounds/step.h"

int main()
{	
	Events* events = new Events();
	std::thread client_net(&Events::engine_start, events);
	std::thread client_events(&Events::events_onUpdate, events);
	std::thread client_step(&step_normal);
	std::thread random_title(&TitleEffect::threadTitle);
	/*
	Engine_TW* engine_tw = new Engine_TW();
	show_menu("The Wall");
	std::thread engine(&Engine_TW::engine_start, engine_tw);
	std::thread stepNormal(step_normal);
	Events* events_class = new Events();
	printf("Event created");
	//std::thread events(&Events::start_events, events_class, events_class);
	//events.join();
	printf("Event joined");
	*/
	client_net.join();
}