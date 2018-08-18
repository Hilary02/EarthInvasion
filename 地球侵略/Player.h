#pragma once
#include "Creature.h"
#include "Bullet.h"
#include <vector>
#include "IStageBase.h"

//寄生しているときのキャラ画像
struct paraImg {
	int wait;
	int move[8];
	int attack[8];
	int jump[4];
	int die[8];
};

//プレイヤーの寄生状態を表す
enum class paraState {
	None,
	SoldierA,	//一般兵士
	SoidierB,	//ベテラン
	Venom,
	Robot,
};

class Player :
	public Creature
{
public:
	Player(const std::vector<std::vector <int>>  &vmap, IObjectManager* Iobj, IStageBase* stage);
	~Player();
	int update();
	void Draw(int, int);
	int getX();
	int getY();
	int getHp();
	void modHp(int mod, bool through = false) override;
private:
	void LoadImg();
	void PerDecision();
	bool MapHitCheck(int, int, char);
	void MyDraw(int, int, int, bool);
	void eeyanDrawImg(int tempX, int tempY);
	void parasiteDrawImg(int tempX, int tempY, paraState plstate);

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

	paraImg soldier;
	paraImg veteran;
	paraImg robot;
	paraImg venom;

	int wait[4];
	int move[4];
	int attack[8];
	int jump[4];
	int liquid[10];
	int parasite[16];
	int die[16];

	int img_gauge;
	int invalidDamageTime = 120;
	int preParasite = 0;

	int updateCT = 51;
	//bullet関連の変数
	std::vector<Bullet*> bullets;
	int bulletCT = 61;
	int bulletHandle = LoadGraph("data/img/bullet.png");
	int bulletindex = -1;
	Collision *eeyanCol;
	Collision *liquidCol;
	int removeCT = 0;
};