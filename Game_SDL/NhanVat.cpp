#include "NhanVat.h"

NhanVat::NhanVat()
{
    mPosX = (SCREEN_WIDTH - NV_WIDTH) / 2;
    mPosY = (SCREEN_HEIGHT - NV_HEIGHT) * 5 / 6;

    mVelX = 0;
    frame = 0;
    mVelY = 0;
    hp = 2000;

    flipType = SDL_FLIP_NONE;

}

NhanVat::~NhanVat() {

}

bool NhanVat::checkHP(int x) {
    hp -= x;
    return hp <= 0;
}

void NhanVat::handleEvent(SDL_Event& e, SDL_Renderer* renderer, Mix_Chunk* bullet_sound)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY -= NV_VEL; break;
        case SDLK_s: mVelY += NV_VEL; break;
        case SDLK_a: { mVelX -= NV_VEL; flipType = SDL_FLIP_HORIZONTAL; break;  }
        case SDLK_d: { mVelX += NV_VEL;  flipType = SDL_FLIP_NONE;  break;  }
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w: mVelY += NV_VEL; break;
        case SDLK_s: mVelY -= NV_VEL; break;
        case SDLK_a: mVelX += NV_VEL; break;
        case SDLK_d: mVelX -= NV_VEL; break;
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_j) {
            Bullet* bullet_ = new Bullet();
            bullet_->loadFromFile("image/bullet.png", renderer);
            Mix_PlayChannel(-1, bullet_sound, 0);
            bullet_->SetPos(this->mPosX + NV_WIDTH - 35, this->mPosY + 37);
            if (flipType == NULL) bullet_->SetX_Vel(15);
            else bullet_->SetX_Vel(-15);
            bullet_->set_is_move(true);
            bullet_list.push_back(bullet_);
        }
    }
}

void NhanVat::HandleBullet(SDL_Renderer* renderer, double x) {
    for (int i = 0; i < bullet_list.size(); i++) {
        Bullet* bullet = bullet_list.at(i);

        if (bullet != NULL) {
            if (bullet->get_is_move() == true) {
                bullet->HandleMove(this->getPosX() + 900, LEVEL_HEIGHT, this->getPosX() - 900);
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

void NhanVat::RemoveBullet(const int& idx) {
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

bool NhanVat::CheckVatcan() {
    SDL_Rect r;
    r.x = mPosX + 20;
    r.y = mPosY + 60;
    r.w = 35;
    r.h = 9;
    for (int i = 0; i < 9; i++) {
        if (SDLCommonFunc::CheckCollision(r, Vatcan[i]) == true) return true;
    }
    return false;
}

bool NhanVat::move()
{
    mPosX += mVelX;

    if ((mPosX < 0) || (mPosX + NV_WIDTH > LEVEL_WIDTH) || CheckVatcan())
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + NV_HEIGHT > LEVEL_HEIGHT) || (mPosY + NV_HEIGHT < 430) || CheckVatcan())
    {
        mPosY -= mVelY;
    }

    return (mVelX != 0 || mVelY != 0);
}

void NhanVat::SetClips() {
    for (int i = 0; i < 11; i++) {
        NhanVatClips[i].x = 65 + i * 80;
        NhanVatClips[i].y = 0;
        NhanVatClips[i].w = 80;
        NhanVatClips[i].h = 69;
    }
}

void NhanVat::SetCamera() {
    camera.x = mPosX + NV_WIDTH / 2 - SCREEN_WIDTH * 2 / 5;
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
}

void NhanVat::LoadimageHP(SDL_Renderer* renderer) {
    HPTexture.loadFromFile("image/HP.png", renderer);
}

void NhanVat::renderHP(SDL_Renderer* renderer) {
    HPTexture.SetRect(100, 35);
    HPTexture.SetSize(hp / 20.0 * 3, 27);
    HPTexture.render(renderer);
}

void NhanVat::render(SDL_Renderer* renderer)
{
    SDL_Rect* currentClip;
    if (move()) {
        currentClip = &NhanVatClips[frame / 8];
        ++frame;

        if (frame / 8 >= 11 - 1)
        {
            frame = 0;
        }
    }
    else currentClip = &NhanVatClips[10];
    rect.x = mPosX - camera.x;
    rect.y = mPosY - camera.y;

    SDL_Rect renderQuad = { rect.x, rect.y, NV_WIDTH, NV_HEIGHT };

    SDL_RenderCopyEx(renderer, mTexture, currentClip, &renderQuad, 0, 0, this->flipType);
}

