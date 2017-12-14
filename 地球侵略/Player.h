#pragma once
#include "Creature.h"
#include <vector>
class Player :
	public Creature
{
public:
	Player(const std::vector<std::vector <int>>  &vmap);
	Player(int x, int y);
	~Player();
	void Update();
	void Draw(int, int);
	int getX();
	int getY();
	int getHp();
private:
	std::vector<std::vector <int>> vmap;
	int clock = 0;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
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
	char xyCheck = 'N';
	char plState = 'N';
	int wait[5];
	int move[5];
	int attack[10];
	int jump[20];
	int liquid[10];
	int die[20];
};