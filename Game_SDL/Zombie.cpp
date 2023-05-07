#include "Zombie.h"

Zombie::Zombie() {
    zPosX = 100 + rand() % (LEVEL_WIDTH + 1 - 200);
    zPosY = 430 + rand() % (170);
    hp = 3;
    frame = 0;
    zVelY = 0;
    flipType = SDL_FLIP_NONE;
}

Zombie::~Zombie() {

}

bool Zombie::checkHP() {
    hp--;
    return  (hp == 0);
}

bool Zombie::CheckVatcan() {
    SDL_Rect r;
    r.x = zPosX + 5;
    r.y = zPosY + 65;
    r.w = 45;
    r.h = 15;
    for (int i = 0; i < 9; i++) {
        if (SDLCommonFunc::CheckCollision(r, Vatcan[i]) == true) return true;
    }
    return false;
}

void Zombie::move(double x, double y) {
    if (zPosX > x + 15) {
        zPosX -= ZB_VELX;
        flipType = SDL_FLIP_NONE;
        if (CheckVatcan()) {
            zPosX += ZB_VELX;
            zPosY -= 1;
        }
    }
    if (zPosX < x + 15) {
        zPosX += ZB_VELX;
        flipType = SDL_FLIP_HORIZONTAL;
        if (CheckVatcan()) {
            zPosX -= ZB_VELX;
            zPosY -= 1;
        }
    }

    if (x != zPosX) zVelY = abs((zPosY - y) * ZB_VELX / (zPosX - x));
    else zVelY = 1;

    if (zVelY > 1) zVelY = 1;

    if (zPosY > y) {
        zPosY -= zVelY;
        if (CheckVatcan()) zPosY += zVelY;
    }
    if (zPosY < y) {
        zPosY += zVelY;
        if (CheckVatcan()) zPosY -= zVelY;
    }
}


void Zombie::SetClips() {

    for (int i = 0; i < 8; i++) {
        ZBClips[i].x = 8 + i * 47;
        ZBClips[i].y = 0;
        ZBClips[i].w = 47;
        ZBClips[i].h = 74;
    }

}

void Zombie::render(SDL_Renderer* renderer, double x, double y, double z, double t)
{
    move(x, y);
    SDL_Rect* currentClip;
    currentClip = &ZBClips[frame / 16];
    ++frame;

    if (frame / 16 > 7)
    {
        frame = 0;
    }

    rect.x = zPosX - z;
    rect.y = zPosY - t;

    SDL_Rect renderQuad = { rect.x, rect.y, ZB_WIDTH, ZB_HEIGHT };

    SDL_RenderCopyEx(renderer, mTexture, currentClip, &renderQuad, 0, 0, this->flipType);
}

//____________________________________________________________________________________
//------------------------------------------------------------------------------------

Zombie1::Zombie1() {
    zPosX = 100 + rand() % (LEVEL_WIDTH + 1 - 200);
    zPosY = 430 + rand() % (170);
    hp = 2;
    frame = 0;
    zVelY = 0;
    flipType = SDL_FLIP_NONE;
}

Zombie1::~Zombie1() {

}

bool Zombie1::checkHP() {
    hp--;
    return  (hp == 0);
}

bool Zombie1::CheckVatcan() {
    SDL_Rect r;
    r.x = zPosX + 5;
    r.y = zPosY + 65;
    r.w = 45;
    r.h = 15;
    for (int i = 0; i < 9; i++) {
        if (SDLCommonFunc::CheckCollision(r, Vatcan[i]) == true) return true;
    }
    return false;
}

void Zombie1::move(double x, double y) {

    if (zPosX > x + 15) {
        zPosX -= ZB1_VELX;
        flipType = SDL_FLIP_NONE;
        if (CheckVatcan()) {
            zPosX += ZB1_VELX;
            zPosY -= 1;
        }
    }
    if (zPosX < x + 15) {
        zPosX += ZB1_VELX;
        flipType = SDL_FLIP_HORIZONTAL;
        if (CheckVatcan()) {
            zPosX -= ZB1_VELX;
            zPosY -= 1;
        }
    }

    if (x != zPosX) zVelY = abs((zPosY - y) * ZB1_VELX / (zPosX - x));
    else zVelY = 2;

    if (zVelY > 2) zVelY = 2;

    if (zPosY > y) {
        zPosY -= zVelY;
        if (CheckVatcan()) {
            zPosY += zVelY;
        }
    }
    if (zPosY < y) {
        zPosY += zVelY;
        if (CheckVatcan()) {
            zPosY -= zVelY;
        }
    }
}


void Zombie1::SetClips() {

    for (int i = 0; i < 8; i++) {
        ZBClips[i].x = 13 + i * 53;
        ZBClips[i].y = 0;
        ZBClips[i].w = 53;
        ZBClips[i].h = 74;
    }

}

void Zombie1::render(SDL_Renderer* renderer, double x, double y, double z, double t)
{
    move(x, y);
    SDL_Rect* currentClip;
    currentClip = &ZBClips[frame / 16];
    ++frame;

    if (frame / 16 > 7)
    {
        frame = 0;
    }

    rect.x = zPosX - z;
    rect.y = zPosY - t;

    SDL_Rect renderQuad = { rect.x, rect.y, ZB1_WIDTH, ZB1_HEIGHT };

    SDL_RenderCopyEx(renderer, mTexture, currentClip, &renderQuad, 0, 0, this->flipType);
}

//==========================================================
ZombieBoss::ZombieBoss() {
    zPosX = 100;
    zPosY = 430;
    hp = 300;
    frame = 0;
    zVelY = 0;
    flipType = SDL_FLIP_NONE;
}

ZombieBoss::~ZombieBoss() {

}

bool ZombieBoss::checkHP() {
    hp--;
    return  (hp <= 0);
}

void ZombieBoss::move(double x, double y) {
    if (zPosX > x + 15) {
        zPosX -= ZBBoss_VELX;
        flipType = SDL_FLIP_NONE;
    }
    if (zPosX < x + 15) {
        zPosX += ZBBoss_VELX;
        flipType = SDL_FLIP_HORIZONTAL;
    }

    if (x != zPosX) zVelY = abs((zPosY - y) * ZBBoss_VELX / (zPosX - x));
    else zVelY = 1;

    if (zVelY > 1) zVelY = 1;

    if (zPosY > y) zPosY -= zVelY;
    if (zPosY < y) zPosY += zVelY;
}


void ZombieBoss::SetClips() {

    for (int i = 0; i < 7; i++) {
        ZBBossClips[i].x = i * 200;
        ZBBossClips[i].y = 0;
        ZBBossClips[i].w = 200;
        ZBBossClips[i].h = 193;
    }

    for (int i = 7; i < 13; i++) {
        ZBBossClips[i].x = (i - 7) * 200;
        ZBBossClips[i].y = 193;
        ZBBossClips[i].w = 200;
        ZBBossClips[i].h = 193;
    }

    ZBBossClips[13].x = 0;
    ZBBossClips[13].y = 193 * 2;
    ZBBossClips[13].w = 200;
    ZBBossClips[13].h = 193;

    ZBBossClips[14].x = 0;
    ZBBossClips[14].y = 193 * 3;
    ZBBossClips[14].w = 200;
    ZBBossClips[14].h = 193;
}


void ZombieBoss::CreateBullet(SDL_Renderer* renderer, Mix_Chunk* b_sound) {
    Bullet* bullet_ = new Bullet();
    bullet_->loadFromFile("image/BossBullet.png", renderer);
    Mix_PlayChannel(7, b_sound, 0);
    bullet_->SetPos(this->zPosX + 50, this->zPosY + 37);
    if (flipType == NULL) bullet_->SetX_Vel(-8);
    else bullet_->SetX_Vel(8);
    bullet_->SetY_Vel(0.95);
    bullet_->set_is_move(true);
    bullet_list.push_back(bullet_);
}

void ZombieBoss::makeBullet(SDL_Renderer* renderer, int& x, Mix_Chunk* b_sound) {
    if (frame == 14) {
        CreateBullet(renderer, b_sound);
    }
    for (int i = 0; i < bullet_list.size(); i++) {
        Bullet* bullet = bullet_list.at(i);

        if (bullet != NULL) {
            if (bullet->get_is_move() == true) {
                bullet->HandleMove(LEVEL_WIDTH, LEVEL_HEIGHT);
                bullet->SetRect(bullet->GetPosX() - x, bullet->GetPosY());
                bullet->render(renderer);
            }
            else {
                bullet_list.erase(bullet_list.begin() + i);
                if (bullet != NULL) {
                    delete bullet;
                    bullet = NULL;
                }
            }
        }
    }
}

void ZombieBoss::RemoveBullet(const int& idx) {
    int size = bullet_list.size();
    if (size > 0 && idx < size) {
        Bullet* bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);

        if (bullet) {
            delete bullet;
            bullet = NULL;
        }
    }

}

void ZombieBoss::LoadimageHP(SDL_Renderer* renderer) {
    HPTexture.loadFromFile("image/HPBoss.png", renderer);
}

void ZombieBoss::renderHP(SDL_Renderer* renderer) {
    HPTexture.SetRect(790 + 300 - hp, 35);
    HPTexture.SetSize(hp, 27);
    HPTexture.render(renderer);
}


void ZombieBoss::render(SDL_Renderer* renderer, double x, double y, double z, double t)
{
    move(x, y);
    SDL_Rect* currentClip;
    currentClip = &ZBBossClips[frame / 16];
    ++frame;

    if (frame / 16 >= 15)
    {
        frame = 0;
    }

    rect.x = zPosX - z;
    rect.y = zPosY - t;

    SDL_Rect renderQuad = { rect.x, rect.y, ZBBOSS_WIDTH, ZBBOSS_HEIGHT };

    SDL_RenderCopyEx(renderer, mTexture, currentClip, &renderQuad, 0, 0, this->flipType);
}