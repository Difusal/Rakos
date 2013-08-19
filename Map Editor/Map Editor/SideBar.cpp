#include "SideBar.h"
#include "Editor.h"

SideBar::SideBar(void) {
	width = 110;
	height = 600;

	// initializing buttons
	Save = new Button("Save", 10, _Left, width);
	buttons.push_back(Save);

	Quit = new Button("Quit", 10, _Right, width);
	buttons.push_back(Quit);
}


void SideBar::Update() {
	// updating side bar coords
	x = Editor::GetInstance()->cameraPosition[0] + ScreenWidth - width;
	y = Editor::GetInstance()->cameraPosition[1] + ScreenHeight - height;

	// updating buttons
	for (Button *button: buttons)
		button->Update(x, y);
}

void SideBar::Draw() {
	// drawing side bar
	al_draw_filled_rectangle(x, y, x + width, y + height, LightGray);
	al_draw_line(x, y, x, y + height, Black, 1.0);

	// drawing buttons
	for (Button *button: buttons)
		button->Draw();
}


SideBar::~SideBar(void) {
	// destroying buttons
	for (Button *button: buttons)
		delete button;
}