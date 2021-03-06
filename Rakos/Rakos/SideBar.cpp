#include "SideBar.h"
#include "RPG.h"

SideBar::SideBar(vector<LivingBeing*> *livingBeings) {
	beings = livingBeings;

	cameraX = &RPG::GetInstance()->cameraPosition[0];
	cameraY = &RPG::GetInstance()->cameraPosition[1];

	width = RPG::GetInstance()->SideBarWidth;
	height = RPG::GetInstance()->ScreenHeight;

	background = al_load_bitmap(SideBarPath);
	if (!background) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load side bar bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	InitializeWindows();
	Update();
	DistributeWindowsAlongSideBar();
}


void SideBar::InitializeWindows() {
	// Initializing side bar windows
	infoWindow = new InfoWindow("Info");
	windows.push_back(infoWindow);


	string equipmentLabel;
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		equipmentLabel = "Equipment";
		break;
	case _Portuguese:
		equipmentLabel = "Equipamento";
		break;
	}
	equipmentWindow = new EquipmentWindow(equipmentLabel);
	windows.push_back(equipmentWindow);


	string creaturesLabel;
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		creaturesLabel = "Creatures";
		break;
	case _Portuguese:
		creaturesLabel = "Criaturas";
		break;
	}
	creaturesWindow = new CreaturesWindow(creaturesLabel, beings);
	windows.push_back(creaturesWindow);
}

void SideBar::DistributeWindowsAlongSideBar() {
	// Updating windows Y positions
	unsigned int nextWindowPosition = 0;
	for (unsigned int i = 0; i < windows.size(); i++) {
		windows[i]->setDefaultWindowY(nextWindowPosition);
		windows[i]->Update();
		nextWindowPosition += windows[i]->getHeight();
	}
}

void SideBar::CheckIfAnywindowIsBeingMoved() {
	someWindowBeingMoved = false;
	for (unsigned int i = 0; i < windows.size(); i++)
		if (windows[i]->isBeingDragged()) {
			someWindowBeingMoved = true;
			movingWindowID = i;
		}
}

void SideBar::Update() {
	x = RPG::GetInstance()->ScreenWidth - width + *cameraX;
	y = *cameraY;

	CheckIfAnywindowIsBeingMoved();
	if (someWindowBeingMoved) {
		if (movingWindowID+1 < windows.size()) {
			// if window was moved down enough to swap with other window, swap them
			if (windows[movingWindowID]->currentBottomYPos() > windows[movingWindowID+1]->middleYPos()) {
				swap(windows[movingWindowID], windows[movingWindowID+1]);
				DistributeWindowsAlongSideBar();
			}
		}
		if (1 <= movingWindowID) {
			// if window was moved up enough to swap with other window, swap them
			if (windows[movingWindowID]->currentYPos() < windows[movingWindowID-1]->middleYPos()) {
				swap(windows[movingWindowID], windows[movingWindowID-1]);
				DistributeWindowsAlongSideBar();
			}
		}
	}

	for (SideBarWindow *obj: windows)
		obj->Update();
}

void SideBar::Draw() {
	// drawing side bar background
	// if screen height is greater than bitmap height, scale it
	if (RPG::GetInstance()->ScreenHeight > (unsigned int)al_get_bitmap_height(background))
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), x, y, RPG::GetInstance()->SideBarWidth, RPG::GetInstance()->ScreenHeight, NULL);
	// else draw the respective region
	else
		al_draw_bitmap_region(background, 0, 0, RPG::GetInstance()->SideBarWidth, RPG::GetInstance()->ScreenHeight, x, y, NULL);

	// drawing side bar windows
	for (SideBarWindow *obj: windows)
		obj->Draw();
}

SideBar::~SideBar() {
	for (SideBarWindow *obj: windows)
		delete obj;

	al_destroy_bitmap(background);
}