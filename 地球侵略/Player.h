#pragma once
#include "Creature.h"
#include "Bullet.h"
#include <vector>

class Player :
	public Creature
{
public:
	Player(const std::vector<std::vector <int>>  &vmap, IObjectManager* Iobj);
	//Player(int x, int y);
	~Player();
	int update();
	void Draw(int, int);
	int getX();
	int getY();
	int getHp();
	void modHp(int mod) override;
private:
	std::vector<std::vector <int>> vmap;
	int clock = 0;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int y1 = 0;
	int y2 = 0;
	int y3 = 0;
	const int MOVE = 2;
	int drawCount = 0;
	int cMove = 0;
	void PerDecision();
	void LoadImg();
	bool MapHitCheck(int , int , char);
	void MyDraw(int, int, int, bool);
	int jumpPower = 0;
	double speed = 10.0;
	bool right = true;
	bool isJumping = false;
	bool isLiquid = false;
	bool isAttack = false;
	bool isDead = false;
	char isMoving = 'N';
	char xyCheck = 'N';
	char plState = 'N';
	int wait[20];
	int move[20];
	int attack[20];
	int jump[20];
	int liquid[10];
	int parasite[20];
	int die[30];

	int invalidDamageTime=60;

	//bulletä÷òAÇÃïœêî
	std::vector<Bullet*> bullets;
	int bulletCT = 61;
	int bulletHundle = LoadGraph("data/img/bullet.png");
	int bulletindex = -1;
};