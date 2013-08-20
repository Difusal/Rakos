#include "SideBar.h"
#include "Editor.h"

SideBar::SideBar(ALLEGRO_BITMAP **tileSet, unsigned int numberOfTiles) {
	width = 110;
	height = 600;

	this->tileSet = new SideBarTileSet(tileSet, numberOfTiles, &x, &y);

	dragging = false;

	InitializeButtons();
}


void SideBar::InitializeButtons() {
	spaceBetweenButtons = 10;

	// tiles and creatures buttons
	unsigned int y1 = spaceBetweenButtons;

	Tiles = new Button("Tiles", y1, _Left, width);
	buttons.push_back(Tiles);

	Mobs = new Button("Mobs", y1, _Right, width);
	buttons.push_back(Mobs);


	// page navigation buttons
	unsigned int y2 = height - 5*(Tiles->Height() + spaceBetweenButtons);

	PreviousPage = new Button("<", y2, _Left, width);
	buttons.push_back(PreviousPage);

	NextPage = new Button(">", y2, _Right, width);
	buttons.push_back(NextPage);
	

	// edit map and drag map buttons
	unsigned int y3 = height - 4*(Tiles->Height() + spaceBetweenButtons);

	EditMap = new Button("Edit", y3, _Left, width);
	buttons.push_back(EditMap);

	DragMap = new Button("Drag", y3, _Right, width);
	buttons.push_back(DragMap);


	// increase map width button
	unsigned int y4 = height - 3*(Tiles->Height() + spaceBetweenButtons);

	IncreaseMapWidth = new Button("Add Column", y4, _Center, width);
	buttons.push_back(IncreaseMapWidth);


	// increase map height button
	unsigned int y5 = height - 2*(Tiles->Height() + spaceBetweenButtons);

	IncreaseMapHeight = new Button("Add Row", y5, _Center, width);
	buttons.push_back(IncreaseMapHeight);


	// save and quit buttons
	unsigned int y6 = height - 1*(Tiles->Height() + spaceBetweenButtons);
	
	Save = new Button("Save", y6, _Left, width);
	buttons.push_back(Save);

	Quit = new Button("Quit", y6, _Right, width);
	buttons.push_back(Quit);
}

void SideBar::Update() {
	// updating side bar coords
	x = Editor::GetInstance()->cameraPosition[0] + ScreenWidth - width;
	y = Editor::GetInstance()->cameraPosition[1] + ScreenHeight - height;

	// updating buttons
	for (Button *button: buttons)
		button->Update(x, y);

	// updating tile set
	tileSet->Update(width, 2*spaceBetweenButtons + buttons[0]->Height(), dragging);

	// checking if any button was pressed
	if (Tiles->wasPressed())
		displayingTilesNotMobs = true;
	else if (Mobs->wasPressed())
		displayingTilesNotMobs = false;

	if (EditMap->wasPressed())
		dragging = false;
	else if (DragMap->wasPressed()) {
		dragging = true;
		tileSet->UnlockAnySelectedTile();
	}

	if (Quit->wasPressed())
		Editor::GetInstance()->ChangeState(_Menu);
}

void SideBar::Draw() {
	// drawing side bar
	al_draw_filled_rectangle(x, y, x + width, y + height, LightGray);
	al_draw_line(x, y, x, y + height, Black, 1.0);

	// drawing tile set
	tileSet->Draw();

	// drawing buttons
	for (Button *button: buttons)
		button->Draw();

	// drawing locked buttons
	if (displayingTilesNotMobs)
		Tiles->DrawLockedButton();
	else
		Mobs->DrawLockedButton();

	if (dragging)
		DragMap->DrawLockedButton();
	else
		EditMap->DrawLockedButton();
}


SideBar::~SideBar(void) {
	// destroying buttons
	for (Button *button: buttons)
		delete button;
}