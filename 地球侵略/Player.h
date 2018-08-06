#pragma once
#include "Creature.h"
#include "Bullet.h"
#include <vector>
#include "IStageBase.h"

class Player :
	public Creature
{
public:
	Player(const std::vector<std::vector <int>>  &vmap, IObjectManager* Iobj, IStageBase* stage);
	//Player(int x, int y)
	~Player();
	int update();
	void Draw(int, int);
	int getX();
	int getY();
	int getHp();
	void modHp(int mod, bool through = false) override;
private:
	IStageBase * Istage;
	std::vector<std::vector <int>> vmap;
	int clock = 0;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	const int MOVE = 3;
	int drawCount = 0;
	int cMove = 0;
	void PerDecision();
	void LoadImg();
	bool MapHitCheck(int, int, char);
	void MyDraw(int, int, int, bool);
	double jumpPower = 0;
	double speed = 10.0;
	bool right = true;
	bool isJumping = false;
	bool isLiquid = false;
	bool isAttack = false;
	bool isDead = false;
	char isMoving = 'N';
	char xyCheck = 'N';
	char plState = 'N';

	//‰æ‘œƒnƒ“ƒhƒ‹
	int wait[4];
	int enemyWait;
	int veteranWait;
	int robotWait;
	int move[4];
	int enemyMove[8];
	int veteranMove[8];
	int robotMove[8];
	int attack[8];
	int enemyAttack[8];
	int veteranAttack[8];
	int robotAttack[8];
	int jump[4];
	int enemyJump[4];
	int veteranJump[4];
	int robotJump[4];
	int liquid[10];
	int parasite[16];
	int die[16];
	int enemyDie[8];
	int veteranDie[8];
	int robotDie[8];
	int img_gauge;

	int invalidDamageTime = 120;
	int preParasite = 0;

	int updateCT = 51;
	//bulletŠÖ˜A‚Ì•Ï”
	std::vector<Bullet*> bullets;
	int bulletCT = 61;
	int bulletHandle = LoadGraph("data/img/bullet.png");
	int bulletindex = -1;
	Collision *eeyanCol;
	Collision *liquidCol;
	int removeCT = 0;
};