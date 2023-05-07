#include "Bullet.h"

Bullet::Bullet() {
	BVelx = 0;
	BVely = 0;
	is_move = false;
	bPosX = 0;
	bPosY = 0;
}

Bullet ::~Bullet() {

}

void Bullet::HandleMove(const int& x1_border, const int& y_border, const int& x2_border) {
	bPosX += BVelx;
	bPosY += BVely;
	if (bPosX > x1_border || bPosY > y_border || bPosX <= x2_border) is_move = false;
}
