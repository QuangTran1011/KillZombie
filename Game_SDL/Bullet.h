#ifndef BULLET_H
#define BULLET_H

#include "LTexture.h"
#include "Base.h"

class Bullet : public LTexture {
public:
	Bullet();
	~Bullet();

	void SetX_Vel(const int& xVel) { BVelx = xVel; }
	void SetY_Vel(const double& yVel) { BVely = yVel; }

	int getXVel() const { return BVelx; }

	void set_is_move(const bool& ismove) { is_move = ismove; }
	bool get_is_move() const { return is_move; }

	void HandleMove(const int& x_border, const int& y_border, const int& x2_border = 0);

	void SetPos(const int& x, const int& y) { bPosX = x; bPosY = y; }
	double GetPosX() const { return bPosX; }
	double GetPosY() const { return bPosY; }

protected:
	int BVelx;
	double BVely;
	double bPosX;
	double bPosY;
	bool is_move;

};

#endif // !BULLET_H

