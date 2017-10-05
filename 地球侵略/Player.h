#pragma once
#include "Creature.h"
#include <vector>
class Player :
	public Creature
{
public:
	Player(std::vector<std::vector <int>> const &vmap);
	Player(int x, int y);
	~Player();
	void Update();
	void Draw(int, int);
private:
	const int MOVE = 1;
	void MapHitCheck();
	void EnemyHitCheck();
	double jumpPower = 10.0;
	double speed = 10.0;
	bool right = true;
	bool jump = false;
	bool liquid = false;
	bool deadFlag = false;
	char plState = 'N';
	int wait[5];
	int move[5];
	int attack[10];
	int die[20];
};