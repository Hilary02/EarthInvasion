#include "InfoArea.h"



//InfoArea::InfoArea() {
//}

InfoArea::InfoArea(Player* pl) {
	hpbar = LoadGraph("data/img/hpbar.png");
	hpbar_empty = LoadGraph("data/img/hpbar_empty.png");
	player = pl;
}


InfoArea::~InfoArea()
{
}

void InfoArea::update() {
	hp = player->getHp();
}

void InfoArea::draw() {
	DrawFormatString(0, 250, GetColor(255, 125, 255), "Info...");
	DrawBox(baseX, baseY, 800, 600, 0x878773, TRUE);
	DrawFormatString(baseX + 40, baseY + 40, col_black, "HP:");
	for (int i = 0; i < 15; i++) {

		int x = baseX + 65 + i*(hpbar_width + 2);
		if (i<hp) {
			DrawGraph(x, baseY + 40, hpbar, false);
		}
		else {
			DrawGraph(x, baseY + 40, hpbar_empty, false);
		}
	}

}
