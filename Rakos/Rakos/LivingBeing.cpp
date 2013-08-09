#include "LivingBeing.h"
#include "globalFunctions.h"
#include "RPG.h"

void LivingBeing::Move() {
	// Skip this if trying to move player. Player has it's own move function.
	if (this->type == _Player)
		return;

	if (active) {
		switch (direction) {
		default:
		case DOWN:
			y++;
			if (y > p2_y) {
				y = p2_y;
				direction = RIGHT;
			}	
			break;
		case RIGHT:
			x++;
			if (x > p2_x) {
				x = p2_x;
				direction = UP;
			}				
			break;
		case UP:
			y--;
			if (y < p1_y) {
				y = p1_y;
				direction = LEFT;
			}
			break;
		case LEFT:
			x--;
			if (x < p1_x) {
				x = p1_x;
				direction = DOWN;
			}	
			break;
		}
	}
}

void LivingBeing::UpdateAnimationFrame() {
	if(active)
		bitmap_sourceX += al_get_bitmap_width(bitmap)/4.0;
	else
		bitmap_sourceX = 32;

	if(bitmap_sourceX >= al_get_bitmap_width(bitmap))
		bitmap_sourceX = 0;

	bitmap_sourceY = direction;
}

void LivingBeing::Draw() {
	switch (direction) {
	case DOWN:
	case RIGHT:
		DrawBeing();
		if (this->weapon->animationIsPlaying())
			weapon->DrawAttackAnim();
		else
			weapon->Draw();
		break;
	case UP:
	case LEFT:
		if (this->weapon->animationIsPlaying())
			weapon->DrawAttackAnim();
		else
			weapon->Draw();
		DrawBeing();
		break;
	}

	DrawName();
	DrawLifeBar();
}

void LivingBeing::DrawName() {
	int pos_x = x + al_get_bitmap_width(bitmap)/4/2;
	int pos_y = y - RPG::GetInstance()->small_font->height - 5;
	if (type == _NPC)
		pos_y = y - RPG::GetInstance()->small_font->height + 2;

	al_draw_text(RPG::GetInstance()->small_font, Black, pos_x-1, pos_y-1, ALLEGRO_ALIGN_CENTER, name.c_str());
	al_draw_text(RPG::GetInstance()->small_font, Black, pos_x+1, pos_y-1, ALLEGRO_ALIGN_CENTER, name.c_str());
	al_draw_text(RPG::GetInstance()->small_font, Black, pos_x+1, pos_y+1, ALLEGRO_ALIGN_CENTER, name.c_str());
	al_draw_text(RPG::GetInstance()->small_font, Black, pos_x-1, pos_y+1, ALLEGRO_ALIGN_CENTER, name.c_str());
	al_draw_text(RPG::GetInstance()->small_font, White, pos_x, pos_y, ALLEGRO_ALIGN_CENTER, name.c_str());
}

void LivingBeing::DrawLifeBar() {
	// skipping drawing life bar if living being is a npc
	if (type == _NPC)
		return;

	int bar_width = 40, bar_height = 5;
	int pos_x = x + al_get_bitmap_width(bitmap)/4/2 - bar_width/2;
	int pos_y = y - bar_height - 2;

	float percentage = (hp * 100.0) / maxHp;

	ALLEGRO_COLOR color;
	if (percentage >= 50) { color = Green; }
	else if (percentage >= 25) { color = Yellow; }
	else { color = Red; }

	int hp_width = bar_width * percentage / 100.0;

	al_draw_filled_rectangle(pos_x-1, pos_y-1, pos_x+bar_width+1, pos_y+bar_height+1, Black);
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+hp_width, pos_y+bar_height, color);
}

void LivingBeing::DrawBeing() {
	al_draw_bitmap_region(bitmap, bitmap_sourceX, bitmap_sourceY * al_get_bitmap_height(bitmap)/4.0, al_get_bitmap_width(bitmap)/4.0, al_get_bitmap_height(bitmap)/4.0, x, y, NULL);
}


void LivingBeing::Speak() {
	speaking = true;
	active = false;
}

void LivingBeing::StopSpeaking() {
	speaking = false;
	if (!alwaysInactive)
		active = true;
}

int LivingBeing::getCurrentFrame() {
	return bitmap_sourceX / (al_get_bitmap_height(bitmap)/4.0);
}