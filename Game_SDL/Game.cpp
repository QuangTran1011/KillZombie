#include "Game.h"

void loadMedia()
{
	bool success = true;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		success = false;
	}
	else {
		m_sound[0] = Mix_LoadWAV("music/gunsound.wav");
		m_sound[1] = Mix_LoadWAV("music/zomhurt.wav");
		m_sound[2] = Mix_LoadWAV("music/zomattack.wav");
		m_sound[3] = Mix_LoadWAV("music/trungdan.wav");
		z_sound[0] = Mix_LoadWAV("music/zomdie.wav");
		B_sound[0] = Mix_LoadWAV("music/bossbullet.wav");
		B_sound[1] = Mix_LoadWAV("music/bossdie.wav");
	}
}


int play(SDL_Renderer* gRenderer, SDL_Event& e)
{
	Timer time;
	loadMedia();
	LTexture gBGTexture;
	NhanVat player;
	player.loadFromFile("image/nhanvat.png", gRenderer);
	player.SetClips();
	player.LoadimageHP(gRenderer);
	gBGTexture.loadFromFile("image/bgr.jpg", gRenderer);

	bool quit = false;

	int t = 2;

	//Font
	TTF_Init();
	TTF_Font* font_text = NULL;
	font_text = TTF_OpenFont("font/lazy.ttf", 25);

	TextObject time_game;
	time_game.SetColor(TextObject::BLACK_TEXT);

	//load logo
	LTexture logo;
	logo.loadFromFile("image/logo.png", gRenderer);
	logo.SetRect(15, 15);
	LTexture logoboss;
	logoboss.loadFromFile("image/logoboss.png", gRenderer);
	logoboss.SetRect(1100, 15);

	ZombieBoss Zboss;
	Zboss.loadFromFile("image/ZBBoss.png", gRenderer);
	Zboss.SetClips();
	Zboss.LoadimageHP(gRenderer);


	//khoi tao zombie
	std::vector<Zombie*> Z;
	std::vector<Zombie1*> Z1;
	Zombie* zombie = new Zombie[2];
	Zombie1* zombie1 = new Zombie1[2];
	
	zombie->loadFromFile("image/ZB.png", gRenderer);
	zombie->SetClips();
	zombie1->loadFromFile("image/ZB1.png", gRenderer);
	zombie1->SetClips();

	(zombie+1)->loadFromFile("image/ZB.png", gRenderer);
	(zombie+1)->SetClips();
	(zombie1+1)->loadFromFile("image/ZB1.png", gRenderer);
	(zombie1+1)->SetClips();
	
	Z.push_back(zombie);
	Z.push_back(zombie + 1);
	Z1.push_back(zombie1);
	Z1.push_back(zombie1 + 1);

	SDL_Rect borderHP = { 100,35,300,27 };
	SDL_Rect borderHPZ = { 790,35,300,27 };

	LTexture pum1;
	pum1.loadFromFile("image/pum.png", gRenderer);
	LTexture pum2;
	pum2.loadFromFile("image/Bul1.png", gRenderer);
	time.start();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				return -1;
			}
			player.handleEvent(e, gRenderer, m_sound[0]);
		}

		if (time.getTicks() / 1000 == t && t < 120) {
			Zombie* z = new Zombie;
			Zombie1* z1 = new Zombie1;

			z->loadFromFile("image/ZB.png", gRenderer);
			z->SetClips();
			z1->loadFromFile("image/ZB1.png", gRenderer);
			z1->SetClips();
			Z.push_back(z);
			Z1.push_back(z1);
			t += 1;
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gBGTexture.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		player.SetCamera();
		gBGTexture.render(gRenderer, &player.camera);
		player.HandleBullet(gRenderer, player.camera.x);
		player.render(gRenderer);
		logo.render(gRenderer);
		player.renderHP(gRenderer);
		SDL_RenderDrawRect(gRenderer, &borderHP);


		//render zombie
		for (int i = 0; i < Z.size(); ++i) {
			Z[i]->render(gRenderer, player.getPosX(), player.getPosY(), player.camera.x, player.camera.y);
			Zboss.SetPos(Z[0]->GetPosX() - 70, Z[0]->GetPosY() - 113);
		}
		for (int i = 0; i < Z1.size(); ++i) {
			Z1[i]->render(gRenderer, player.getPosX(), player.getPosY(), player.camera.x, player.camera.y);
			Zboss.SetPos(Z1[0]->GetPosX() - 70, Z1[0]->GetPosY() - 113);
		}


		//Boss xuat hien
		if (Z.size() == 0 && Z1.size() == 0) {
			Zboss.makeBullet(gRenderer, player.camera.x, B_sound[0]);
			Zboss.render(gRenderer, player.getPosX() - 70, player.getPosY() - 113, player.camera.x, player.camera.y);
			logoboss.render(gRenderer);
			Zboss.renderHP(gRenderer);
			SDL_RenderDrawRect(gRenderer, &borderHPZ);
			std::vector<Bullet*> BossBullet = Zboss.get_bullet_list();

			SDL_Rect mRect;
			mRect.x = player.GetRect().x + 45;
			mRect.y = player.GetRect().y + 10;
			mRect.w = 1;
			mRect.h = 45;


			//boss tan cong
			for (int i = 0; i < (int)BossBullet.size(); i++) {
				bool ZisCol = SDLCommonFunc::CheckCollision(BossBullet[i]->GetRect(), mRect);
				if (ZisCol) {
					Mix_PlayChannel(5, m_sound[3], 0);
					int xp = BossBullet[i]->GetRect().x - 8;
					int yp = BossBullet[i]->GetRect().y - 8;

					pum2.SetRect(xp, yp);
					pum2.render(gRenderer);
					Zboss.RemoveBullet(i);
					if (player.checkHP(200)) {
						LTexture end;
						end.loadFromFile("image/blood.png", gRenderer);
						end.SetRect(mRect.x - 15, mRect.y);
						end.render(gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_Delay(3000);
						player.free();
						return 0;
					}
				}
			}

			SDL_Rect bRect;
			bRect.x = Zboss.GetRect().x + 90;
			bRect.y = Zboss.GetRect().y + 140;
			bRect.w = 70;
			bRect.h = 40;

			bool B_iscol = SDLCommonFunc::CheckCollision(bRect, mRect);
			if (B_iscol) {
				Mix_PlayChannel(1, m_sound[2], 0);
				if (player.checkHP()) {
					LTexture end;
					end.loadFromFile("image/blood.png", gRenderer);
					end.SetRect(mRect.x - 25, mRect.y);
					end.render(gRenderer);
					SDL_RenderPresent(gRenderer);
					SDL_Delay(3000);
					player.free();
					return 0;
				}
			}
		}


		//check vacham
		SDL_Rect mRect;
		mRect.x = player.GetRect().x + 30;
		mRect.y = player.GetRect().y + 10;
		mRect.w = 15;
		mRect.h = 45;

		for (int j = 0; j < Z.size(); j++) {
			SDL_Rect zRect;
			zRect.x = Z[j]->GetRect().x + 8;
			zRect.y = Z[j]->GetRect().y + 5;
			zRect.w = 40;
			zRect.h = 58;

			bool MisCol = SDLCommonFunc::CheckCollision(mRect, zRect);
			if (MisCol) {
				Mix_PlayChannel(1, m_sound[2], 0);
				if (player.checkHP()) {
					LTexture end;
					end.loadFromFile("image/blood.png", gRenderer);
					end.SetRect(mRect.x - 15, mRect.y);
					end.render(gRenderer);
					SDL_RenderPresent(gRenderer);
					SDL_Delay(3000);
					player.free();
					return 0;
				}
			}
		}

		for (int j = 0; j < Z1.size(); j++) {
			SDL_Rect zRect;
			zRect.x = Z1[j]->GetRect().x + 8;
			zRect.y = Z1[j]->GetRect().y + 5;
			zRect.w = 45;
			zRect.h = 58;

			bool MisCol = SDLCommonFunc::CheckCollision(mRect, zRect);
			if (MisCol) {
				Mix_PlayChannel(1, m_sound[2], 0);
				if (player.checkHP()) {
					LTexture end;
					end.loadFromFile("image/blood.png", gRenderer);
					end.SetRect(mRect.x - 10, mRect.y);
					end.render(gRenderer);
					SDL_RenderPresent(gRenderer);
					SDL_Delay(3000);
					player.free();
					return 0;
				}
			}
		}

		//check zombie trung dan
		std::vector<Bullet*> bulletarr = player.get_bullet_list();
		for (int i = 0; i < bulletarr.size(); i++) {
			if (bulletarr[i] != NULL) {
				for (int j = 0; j < Z.size(); j++) {
					SDL_Rect zRect;
					zRect.x = Z[j]->GetRect().x + 8;
					zRect.y = Z[j]->GetRect().y + 5;
					zRect.w = 40;
					zRect.h = 58;
					bool ZisCol = SDLCommonFunc::CheckCollision(bulletarr[i]->GetRect(), zRect);

					if (ZisCol) {
						int xp = bulletarr[i]->GetRect().x - 19;
						int yp = bulletarr[i]->GetRect().y - 20;

						pum1.SetRect(xp, yp);
						pum1.render(gRenderer);

						player.RemoveBullet(i);
						if (Z[j]->checkHP()) {
							Mix_PlayChannel(6, z_sound[0], 0);
							Z[j]->free();
							Z.erase(Z.begin() + j);
						}
					}
				}

				for (int j = 0; j < Z1.size(); j++) {
					SDL_Rect zRect;
					zRect.x = Z1[j]->GetRect().x + 8;
					zRect.y = Z1[j]->GetRect().y + 5;
					zRect.w = 45;
					zRect.h = 58;
					bool isCol = SDLCommonFunc::CheckCollision(bulletarr[i]->GetRect(), zRect);

					if (isCol) {
						int xp = bulletarr[i]->GetRect().x - 19;
						int yp = bulletarr[i]->GetRect().y - 20;

						pum1.SetRect(xp, yp);
						pum1.render(gRenderer);

						player.RemoveBullet(i);
						if (Z1[j]->checkHP()) {
							Mix_PlayChannel(6, z_sound[0], 0);
							Z1[j]->free();
							Z1.erase(Z1.begin() + j);
						}
					}

				}
				SDL_Rect zRect;
				zRect.x = Zboss.GetRect().x + 95;
				zRect.y = Zboss.GetRect().y + 60;
				zRect.w = 30;
				zRect.h = 110;
				bool isCol = SDLCommonFunc::CheckCollision(bulletarr[i]->GetRect(), zRect);

				if (isCol) {
					Mix_PlayChannel(4, m_sound[1], 0);
					int xp = bulletarr[i]->GetRect().x - 19;
					int yp = bulletarr[i]->GetRect().y - 20;

					pum1.SetRect(xp, yp);
					pum1.render(gRenderer);

					player.RemoveBullet(i);
					if (Zboss.checkHP()) {
						LTexture end;
						end.loadFromFile("image/end1.png", gRenderer);
						end.SetRect(xp - 40, yp - 80);
						end.render(gRenderer);
						SDL_RenderPresent(gRenderer);
						Mix_PlayChannel(-1, B_sound[1], 0);
						SDL_Delay(3000);
						Zboss.free();
						return 1;
					}
				}
			}
		}

		std::string str_time = "Time : ";
		int time_val = time.getTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.LoadFromRenderText(font_text, gRenderer);
		time_game.RenderText(gRenderer, 500, 25);

		SDL_RenderPresent(gRenderer);
	}
	return true;
}
