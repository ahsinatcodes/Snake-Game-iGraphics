#include "iGraphics.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SNAKE_SIZE 20

int homepage = 1;
int start = 0;
int score = 0;
int scoreReset = 0;
char point[10000];

int easyScore, mediumScore, hardScore;
int easyHighscore = 0, mediumHighscore = 0, hardHighscore = 0;

int snakeX[100] = {0};
int snakeY[100] = {0};
int headX = 100;
int headY = 300;
int snake_l = 3;

int foodX = 200;
int foodY = 200;
int foodtype = 1;
int fc = 0;
int vf;

int gameover = 0;
int dir;
int gamestart = 0;
int aboutpg = 0;
int scorepg = 0;
int settings = 0;
int level = 0;
int speed = 97;
int paused = 0;

bool musicOn = true;
int bgm = 1;
int color = 1;

FILE *easy, *medium, *hard, *hs;

Image bh, bm, apple, orange, hp, lvl, abt, over;
Image pause, back, replay;
Image highscore;
Image musicon, musicoff, color1, color2, color3;

void loadresources()
{
	iLoadImage(&hp, "images/homepage.jpg");
	iLoadImage(&lvl, "images/level.jpg");
	iLoadImage(&abt, "images/about.jpg");
	iLoadImage(&over, "images/gameover.jpg");
	iLoadImage(&bh, "images/bh.png");
	iLoadImage(&bm, "images/bm.png");
	iLoadImage(&apple, "images/apple.jpg");
	iLoadImage(&orange, "images/orange.jpg");
	iLoadImage(&pause, "images/paused.png");
	iLoadImage(&back, "images/back.png");
	iLoadImage(&replay, "images/replay.png");
	iLoadImage(&highscore, "images/highscore.png");
	iLoadImage(&musicon, "images/mon.jpg");
	iLoadImage(&musicoff, "images/moff.jpg");
	iLoadImage(&color1, "images/color1.png");
	iLoadImage(&color2, "images/color2.png");
	iLoadImage(&color3, "images/color3.png");
}

void drawhomepage()
{
	iShowImage(0, 0, &hp);
}

void playclicked()
{
	iShowImage(0, 0, &lvl);
}

void aboutpage()
{
	iShowImage(0, 0, &abt);
}

void settingsPage()
{
	iSetColor(230, 226, 121);
	iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iShowImage(70, 520, &back);

	iSetColor(78, 57, 5);
	iText(70, 372, "Music", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 332, "Snake appearance", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(70, 292, "Reset Score", GLUT_BITMAP_TIMES_ROMAN_24);

	if (musicOn)
	{
		iShowImage(453, 364, &musicon);
	}
	else
	{
		iShowImage(453, 364, &musicoff);
	}

	if (color == 1)
	{
		iShowImage(370, 330, &color1);
	}
	else if (color == 2)
	{
		iShowImage(370, 330, &color2);
	}
	else if (color == 3)
	{
		iShowImage(370, 330, &color3);
	}

	if(scoreReset==1)
	{
		iSetColor(230, 226, 121);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(78, 57, 5);
		iText(160, 370, "Are you sure you want to reset?", GLUT_BITMAP_HELVETICA_18);
		iText(200, 310, "Yes                        No", GLUT_BITMAP_HELVETICA_18);
	}
}

void resetScore()
{
	easy = fopen("scores/easyHscore.txt", "w");
	if(easy!=NULL)
	{
		fprintf(easy, "%d", 0);
		fclose(easy);
	}
	medium = fopen("scores/mediumHscore.txt", "w");
	if (medium != NULL)
	{
		fprintf(medium, "%d", 0);
		fclose(medium);
	}
	hard = fopen("scores/hardHscore.txt", "w");
	if (hard != NULL)
	{
		fprintf(hard, "%d", 0);
		fclose(hard);
	}
	scoreReset = 0;
}

void gamepage()
{
	iSetColor(230, 226, 121);
	iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void gameoverpage()
{
	if (gameover == 1)
	{
		iShowImage(0, 0, &over);
		iSetColor(78, 57, 5);
		iText(212, 332, "Your score : ", GLUT_BITMAP_HELVETICA_18);
		iText(357, 331, point, GLUT_BITMAP_HELVETICA_18);

		// Get the high score for the current level
		int highScore = 0;

		if (level == 1)
		{
			hs = fopen("scores/easyHscore.txt", "r");
		}
		else if (level == 2)
		{
			hs = fopen("scores/mediumHscore.txt", "r");
		}
		else if (level == 3)
		{
			hs = fopen("scores/hardHscore.txt", "r");
		}

		if (hs != NULL)
		{
			fscanf(hs, "%d", &highScore);
			fclose(hs);
		}

		char highScoreText[1000];
		sprintf(highScoreText, "%d", highScore);
		iText(212, 275, "High score : ", GLUT_BITMAP_HELVETICA_18);
		iText(357, 275, highScoreText, GLUT_BITMAP_HELVETICA_18);
	}
}


void scorePage()
{
	iSetColor(230, 226, 121);
	iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	iShowImage(50, 520, &back);
	iShowImage(190, 386, &highscore);
	iSetColor(78, 57, 5);
	iText(208, 310, "EASY         : ", GLUT_BITMAP_HELVETICA_18);
	iText(208, 270, "MEDIUM    : ", GLUT_BITMAP_HELVETICA_18);
	iText(208, 230, "HARD         :", GLUT_BITMAP_HELVETICA_18);

	easy = fopen("scores/easyHscore.txt", "r");
	char ehs[10000];
	fscanf(easy, "%d", &easyHighscore);
	sprintf(ehs, "%d", easyHighscore);
	iText(360, 310, ehs, GLUT_BITMAP_HELVETICA_18);
	fclose(easy);

	medium = fopen("scores/mediumHscore.txt", "r");
	char mhs[10000];
	fscanf(medium, "%d", &mediumHighscore);
	sprintf(mhs, "%d", mediumHighscore);
	iText(360, 270, mhs, GLUT_BITMAP_HELVETICA_18);
	fclose(medium);

	hard = fopen("scores/hardHscore.txt", "r");
	char hhs[10000];
	fscanf(hard, "%d", &hardHighscore);
	sprintf(hhs, "%d", hardHighscore);
	iText(360, 230, hhs, GLUT_BITMAP_HELVETICA_18);
	fclose(hard);
}

void snake()
{
	for (int i = 0; i < snake_l; i++)
	{
		if (color == 1)
			iSetColor(69, 113, 228);
		else if (color == 2)
			iSetColor(255, 127, 80);
		else if (color == 3)
			iSetColor(44, 130, 91);

		iFilledRectangle(snakeX[i], snakeY[i], SNAKE_SIZE, SNAKE_SIZE);
		if (i == 0)
		{
			iSetColor(0, 0, 0);
			if ((snakeX[i] > snakeX[i + 1]) && (snakeY[i] == snakeY[i + 1])) // right
			{
				iFilledCircle(snakeX[i] + 5, snakeY[i] + 15, 2);
				iFilledCircle(snakeX[i] + 5, snakeY[i] + 5, 2);
			}
			if ((snakeX[i] < snakeX[i + 1]) && (snakeY[i] == snakeY[i + 1])) // left
			{
				iFilledCircle(snakeX[i] + 15, snakeY[i] + 15, 2);
				iFilledCircle(snakeX[i] + 15, snakeY[i] + 5, 2);
			}
			if ((snakeX[i] == snakeX[i + 1]) && (snakeY[i] > snakeY[i + 1])) // up
			{
				iFilledCircle(snakeX[i] + 15, snakeY[i] + 5, 2);
				iFilledCircle(snakeX[i] + 5, snakeY[i] + 5, 2);
			}
			if ((snakeX[i] == snakeX[i + 1]) && (snakeY[i] < snakeY[i + 1])) // down
			{
				iFilledCircle(snakeX[i] + 5, snakeY[i] + 15, 2);
				iFilledCircle(snakeX[i] + 15, snakeY[i] + 15, 2);
			}
		}
	}
}

void movingsnake()
{
	if (gameover == 0)
	{
		for (int i = snake_l - 1; i > 0; i--)
		{
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		if (dir == 0)
		{
			snakeX[0] += SNAKE_SIZE;
			gamestart = 1;
		}
		else if (dir == 1) // UP
		{
			snakeY[0] += SNAKE_SIZE;
			gamestart = 1;
		}
		else if (dir == 3) // LEFT
		{
			snakeX[0] -= SNAKE_SIZE;
			gamestart = 1;
		}
		else if (dir == 2) // DOWN
		{
			snakeY[0] -= SNAKE_SIZE;
			gamestart = 1;
		}
	}
}

void randomfood()
{
	vf = 0;
	while (vf == 0)
	{
		foodX = (rand() % (SCREEN_WIDTH / 20)) * 20;
		foodY = (rand() % (SCREEN_HEIGHT / 20)) * 20;
		vf = 1;							  // food is valid
		for (int i = 0; i < snake_l; i++) // to make sure food doesn't appear on snake's body
		{
			if (snakeX[i] == foodX && snakeY[i] == foodY)
			{
				vf = 0;
				break;
			}
		}
		if (level == 2)
		{
			if (foodX < 20 || foodX >= SCREEN_WIDTH - 20 || foodY < 20 || foodY >= SCREEN_HEIGHT - 20)
			{
				vf = 0;
			}
		}
		if (level == 3)
		{
			if ((foodX >= 140 && foodX <= 300) && (foodY >= 420 && foodY <= 460)) // horizontal block 1
			{
				vf = 0;
			}
			if ((foodX >= 300 && foodX <= 460) && (foodY >= 140 && foodY <= 180)) // horizontal block 2
			{
				vf = 0;
			}
			if ((foodX >= 420 && foodX <= 460) && (foodY >= 300 && foodY <= 460)) // vertical block 1
			{
				vf = 0;
			}
			if ((foodX >= 140 && foodX <= 180) && (foodY >= 140 && foodY <= 300)) // vertical block 2
			{
				vf = 0;
			}

			if ((foodX >= 20 && foodX <= 140 || foodX >= 460 && foodX <= 580) &&
				(foodY >= 20 && foodY <= 140 || foodY >= 460 && foodY <= 580))
			{
				vf = 0;
			}

			if ((foodX < 20 || foodX >= 580) && (foodY >= 460 || foodY <= 140) ||
				(foodY < 20 || foodY >= 580) && (foodX <= 140 || foodX >= 460))
			{
				vf = 0;
			}
		}
		// Debugging information
		if (vf == 0)
		{
			printf("Invalid food position: (%d, %d)\n", foodX, foodY);
		}
	}
}

void food()
{
	if (vf == 1)
	{
		if (foodtype == 1)
		{
			iShowImage(foodX, foodY, &apple);
		}
		else if (foodtype == 2)
		{
			iShowImage(foodX, foodY, &orange);
		}
	}
}

void resetsnake()
{
	snake_l = 3;
	for (int i = 0; i < snake_l; i++)
	{
		snakeX[i] = headX - i * SNAKE_SIZE;
		snakeY[i] = headY;
	}
	dir = -1;
	gamestart = 0;
	score = 0;
	fc = 0;
	foodtype = 1;
	randomfood();
	// iSetTimer(speed, movingsnake);
}

void showscore()
{
	sprintf(point, "%d", score);
	iSetColor(0, 0, 0);
	iText(464, 548, "SCORE : ", GLUT_BITMAP_9_BY_15);
	iText(535, 548, point, GLUT_BITMAP_9_BY_15);
}

void savescore()
{
	if (level == 1)
	{
		easy = fopen("scores/easyHscore.txt", "r");
		if(easy!=NULL)
		{
			fscanf(easy, "%d", &easyHighscore);
			fclose(easy);
			if (easyScore > easyHighscore)
			{
				easyHighscore = easyScore;
				easy = fopen("scores/easyHscore.txt", "w");
				fprintf(easy, "%d", easyHighscore);
				fclose(easy);
			}
		}
	}
	if (level == 2)
	{
		medium = fopen("scores/mediumHscore.txt", "r");
		if(medium!=NULL)
		{
			fscanf(medium, "%d", &mediumHighscore);
			fclose(medium);
			if (mediumScore > mediumHighscore)
			{
				mediumHighscore = mediumScore;
				medium = fopen("scores/mediumHscore.txt", "w");
				fprintf(medium, "%d", mediumHighscore);
				fclose(medium);
			}
		}
	}
	if (level == 3)
	{
		hard = fopen("scores/hardHscore.txt", "r");
		if(hard!=NULL)
		{
			fscanf(hard, "%d", &hardHighscore);
			fclose(hard);
			if (hardScore > hardHighscore)
			{
				hardHighscore = hardScore;
				hard = fopen("scores/hardHscore.txt", "w");
				fprintf(hard, "%d", hardHighscore);
				fclose(hard);
			}
		}
	}
}

void wrapping()
{
	if (level == 1)
	{
		if (snakeX[0] >= SCREEN_WIDTH)
		{
			snakeX[0] = 0; // Wrap right to left
		}
		else if (snakeX[0] < 0)
		{
			snakeX[0] = SCREEN_WIDTH - SNAKE_SIZE; // Wrap left to right
		}

		if (snakeY[0] >= SCREEN_HEIGHT)
		{
			snakeY[0] = 0; // Wrap bottom to top
		}
		else if (snakeY[0] < 0)
		{
			snakeY[0] = SCREEN_HEIGHT - SNAKE_SIZE;
		}
	}
	if (level == 3)
	{
		if (snakeX[0] >= SCREEN_WIDTH && (snakeY[0] >= 140 && snakeY[0] <= 460))
		{
			snakeX[0] = 0; // Wrap right to left
		}
		else if (snakeX[0] < 0 && (snakeY[0] >= 140 && snakeY[0] <= 460))
		{
			snakeX[0] = SCREEN_WIDTH - SNAKE_SIZE; // Wrap left to right
		}

		if (snakeY[0] >= SCREEN_HEIGHT && (snakeX[0] >= 140 && snakeX[0] <= 460))
		{
			snakeY[0] = 0; // Wrap bottom to top
		}
		else if (snakeY[0] < 0 && (snakeX[0] >= 140 && snakeX[0] <= 460))
		{
			snakeY[0] = SCREEN_HEIGHT - SNAKE_SIZE;
		}
	}
}

void eatfood()
{
	if (snakeX[0] == foodX && snakeY[0] == foodY)
	{
		snake_l++;
		fc++;
		if (foodtype == 1)
		{
			score++;
		}
		else if (foodtype == 2)
		{
			score += 10;
			fc = 0;
			foodtype = 1;
		}
		if (fc == 5)
		{
			foodtype = 2;
		}
		snakeX[snake_l - 1] = snakeX[snake_l - 2];
		snakeY[snake_l - 1] = snakeY[snake_l - 2];
		// printf("Snake Head: (%d, %d), Food: (%d, %d)\n", snakeX[0], snakeY[0], foodX, foodY);

		randomfood();
	}
	if (level == 1)
	{
		easyScore = score;
	}
	if (level == 2)
	{
		mediumScore = score;
	}
	if (level == 3)
	{
		hardScore = score;
	}
}

void selfbite()
{
	if (gamestart == 1)
	{
		for (int i = 1; i < snake_l; i++)
		{
			if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
			{
				gameover = 1;
			}
		}
	}
}

void wall()
{
	if (level == 2)
	{
		iShowImage(0, 0, &bm);
	}
	else if (level == 3)
	{
		iShowImage(0, 0, &bh);
	}
}

void checkcollision()
{
	if (level == 2)
	{
		if (snakeX[0] >= (SCREEN_WIDTH - SNAKE_SIZE)) // right wall collision
		{
			gameover = 1;
		}
		else if (snakeX[0] < SNAKE_SIZE) // left wall collision
		{
			gameover = 1;
		}

		if (snakeY[0] >= SCREEN_HEIGHT - SNAKE_SIZE) // top collision
		{
			gameover = 1;
		}
		else if (snakeY[0] < SNAKE_SIZE) // bottom collision
		{
			gameover = 1;
		}
	}
	if (level == 3)
	{
		if ((snakeX[0] >= 140 && snakeX[0] < 300) && (snakeY[0] >= 420 && snakeY[0] < 460)) // horizontal obstacle 1
		{
			gameover = 1;
		}
		if ((snakeX[0] >= 300 && snakeX[0] < 460) && (snakeY[0] >= 140 && snakeY[0] < 180)) // horizontal obstacle 2
		{
			gameover = 1;
		}
		if ((snakeX[0] >= 420 && snakeX[0] < 460) && (snakeY[0] >= 300 && snakeY[0] < 460)) // vertical obstacle 1
		{
			gameover = 1;
		}
		if ((snakeX[0] >= 140 && snakeX[0] < 180) && (snakeY[0] >= 140 && snakeY[0] < 300)) // vertical obstacle 2
		{
			gameover = 1;
		}

		if ((snakeX[0] < 20 || snakeX[0] >= 580) && (snakeY[0] >= 460 || snakeY[0] < 140) ||
			(snakeY[0] < 20 || snakeY[0] >= 580) && (snakeX[0] < 140 || snakeX[0] >= 460)) // boundary
		{
			gameover = 1;
		}
	}
}
/*
	function iDraw() is called again and again by the system.

*/
void iDraw()
{
	// place your drawing codes here
	iClear();
	if (homepage == 1)
	{
		drawhomepage();
	}
	else if (start == 1)
	{
		playclicked();
	}
	else if (aboutpg == 1)
	{
		aboutpage();
	}
	else if (scorepg == 1)
	{
		scorePage();
	}
	else if (settings == 1)
	{
		settingsPage();
	}
	else if (level > 0)
	{
		gamepage();
		snake();
		food();
		eatfood();
		selfbite();
		if (level > 1)
		{
			wall();
			checkcollision();
		}
		if (level == 1 || level == 3)
		{
			wrapping();
		}
		showscore();
		if (paused == 1)
		{
			iShowImage(245, 348, &pause);
			iSetColor(0, 0, 0);
			iText(242, 308, "Press 'R' to resume", GLUT_BITMAP_HELVETICA_18);
			iShowImage(255, 260, &back);
			iShowImage(358, 260, &replay);
		}
	}
	if (gameover == 1)
	{
		gameoverpage();
		savescore();
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("x = %d, y= %d\n", mx, my);
		if (homepage == 1)
		{
			if ((mx >= 266 && mx <= 350) && (my >= 410 && my <= 435)) // PLAY BUTTON
			{
				homepage = 0;
				start = 1;
				aboutpg = 0;
				scorepg = 0;
				settings = 0;
			}

			if ((mx >= 257 && mx <= 357) && (my >= 325 && my <= 345)) // ABOUT PAGE
			{
				homepage = 0;
				start = 0;
				aboutpg = 1;
				scorepg = 0;
				settings = 0;
			}

			if ((mx >= 249 && mx <= 365) && (my >= 366 && my <= 388)) // Score PAGE
			{
				homepage = 0;
				start = 0;
				aboutpg = 0;
				scorepg = 1;
				settings = 0;
			}
			if ((mx >= 235 && mx <= 380) && (my >= 280 && my <= 300)) // Settings PAGE
			{
				homepage = 0;
				start = 0;
				aboutpg = 0;
				scorepg = 0;
				settings = 1;
			}
		}

		if (start == 1)
		{
			if ((mx >= 250 && mx <= 350) && (my >= 337 && my <= 364))
			{
				start = 0;
				bgm = 0;
				dir = 0;
				level = 1; // easy
			}
			if ((mx >= 227 && mx <= 375) && (my >= 286 && my <= 315))
			{
				start = 0;
				bgm = 0;
				dir = 0;
				level = 2; // medium
			}
			if ((mx >= 245 && mx <= 356) && (my >= 235 && my <= 265))
			{
				start = 0;
				bgm = 0;
				dir = 0;
				level = 3; // hard
			}
			if ((mx >= 54 && mx <= 94) && (my >= 517 && my <= 532)) // back
			{
				homepage = 1;
			}
		}
		if (aboutpg == 1)
		{
			if ((mx >= 35 && mx <= 70) && (my >= 529 && my <= 544))
			{
				homepage = 1;
			}
		}
		if (settings == 1)
		{
			if ((mx >= 452 && mx <= 488) && (my >= 372 && my <= 395))
			{
				if (musicOn)
				{
					musicOn = false;
					PlaySound(0, 0, 0);
				}
				else
				{
					musicOn = true;
					PlaySound("music/bgm.wav", NULL, SND_LOOP | SND_ASYNC);
				}
			}
			if ((mx >= 70 && mx <= 107) && (my >= 524 && my <= 540))
			{
				homepage = 1;
			}
			if ((mx >= 370 && mx <= 400) && (my >= 330 && my <= 355))
			{
				color = 1;
			}
			else if ((mx >= 415 && mx <= 445) && (my >= 330 && my <= 355))
			{
				color = 2;
			}
			else if ((mx >= 460 && mx <= 490) && (my >= 330 && my <= 355))
			{
				color = 3;
			}
			if((mx>=75 && mx<=187) && (my>=294 && my<=307))
			{
				scoreReset = 1;
			}
		}
		if(scoreReset==1)
		{
			if((mx>=350 && mx<=378) && (my>=310 && my<=325))
			{
				settings = 1;
				scoreReset = 0;
			}
			if ((mx >= 202 && mx <= 232) && (my >= 310 && my <= 325))
			{
				settings = 1;
				scoreReset = 0;
				resetScore();
			}
		}
		if (gameover == 1)
		{
			if ((mx >= 355 && mx <= 382) && (my >= 221 && my <= 246)) // replay button
			{
				start = 1;
				gameover = 0;
				resetsnake();
			}
			if ((mx >= 211 && mx <= 245) && (my >= 221 && my <= 246)) // back
			{
				homepage = 1;
				start = 0;
				gameover = 0;
				resetsnake();
			}
		}
		if (scorepg == 1)
		{
			if ((mx >= 50 && mx <= 89) && (my >= 520 && my <= 540))
			{
				homepage = 1;
				start = 0;
				gameover = 0;
				resetsnake();
			}
		}
		if (paused == 1)
		{
			if ((mx >= 358 && mx <= (358 + 22)) && (my >= 260 && my <= 280)) // replay
			{
				start = 1;
				gameover = 0;
				paused = 0;
				iResumeTimer(0);
				resetsnake();
			}
			if ((mx >= 253 && mx <= (253 + 39)) && (my >= 260 && my <= 280)) // back
			{
				homepage = 1;
				start = 0;
				gameover = 0;
				paused = 0;
				iResumeTimer(0);
				resetsnake();
			}
		}
	}
}

void iPassiveMouseMove(int mx, int my)
{
}

void iKeyboard(unsigned char key)
{
	if (key == 'q' || key == 'Q')
	{
		exit(0);
	}
	if (key == 'p' || key == 'P')
	{
		paused = 1;
		iPauseTimer(0);
	}
	if (key == 'r' || key == 'R')
	{
		if (paused == 1)
		{
			paused = 0;
			iResumeTimer(0);
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_UP && dir != 2)
	{
		dir = 1; // up
	}
	if (key == GLUT_KEY_DOWN && dir != 1)
	{
		dir = 2; // down
	}
	if (key == GLUT_KEY_LEFT && dir != 0)
	{
		dir = 3; // left
	}
	if (key == GLUT_KEY_RIGHT && dir != 3)
	{
		dir = 0; // right
	}
}

int main()
{
	// place your own initialization codes here.
	srand(time(0));
	loadresources();
	iSetTimer(speed, movingsnake);
	resetsnake();
	if (musicOn && bgm == 1)
	{
		PlaySound("music/bgm.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

	return 0;
}