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
private:
	std::vector<std::vector <int>> vmap;
	const int MOVE = 2;
	int drawCount = 0;
	double cMove = 0;
	void LoadImg();
	bool MapHitCheck(int , int);
	double jumpPower = 0;
	double speed = 10.0;
	bool right = true;
	bool jumpFlag = false;
	bool liquidFlag = false;
	bool attackFlag = false;
	bool deadFlag = false;
	char plState = 'N';
	int wait[5];
	int move[5];
	int attack[10];
	int jump[20];
	int die[20];
};