#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Angel.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT
};


void Angel::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/spriteAngel600x100Idle&run.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(99, 55), glm::vec2(0.2, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(STAND_RIGHT, 6);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f * 2, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f * 3, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f * 4, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 6);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.2f * 2, 0.5f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.2f * 3, 0.5f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.2f * 4, 0.5f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f * 2, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f * 3, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f * 4, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f * 2, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f * 3, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f * 4, 0.5f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 6);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f, 0.f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f * 2, 0.f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f * 3, 0.f));
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.2f * 4, 0.f));

	sprite->setAnimationSpeed(JUMP_LEFT, 6);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.2f, 0.5f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.2f * 2, 0.5f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.2f * 3, 0.5f));
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.2f * 4, 0.5f));

	

	

	

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//sprite->setPosition(glm::vec2(float(1000), float(100)));


}

void Angel::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(39, 39)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{

		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(39, 39)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT /* || sprite->animation() == JUMP_LEFT*/)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT /* || sprite->animation() == JUMP_RIGHT*/)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{

		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(39, 39), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(39, 39), &posPlayer.y))
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				/*if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
				else if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
					sprite->changeAnimation(JUMP_LEFT);*/
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}

	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Angel::render()
{
	sprite->render();
}

void Angel::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Angel::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




