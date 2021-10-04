#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_RIGHT, JUMP_LEFT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	spritesheet.loadFromFile("images/Demonspritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(55, 55), glm::vec2(0.125, 0.16666666), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 2, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 3, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 4, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 5, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 6, 0.16666666f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f * 7, 0.16666666f));
		
		
		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 2, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 3, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 4, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 5, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 6, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.125f * 7, 0.f));

		
		sprite->setAnimationSpeed(MOVE_LEFT, 10);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.16666666f *5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 2, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 3, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 4, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 5, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 6, 0.16666666f * 5));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f * 7, 0.16666666f * 5));

	
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 10);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 2, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 3, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 4, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 5, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 6, 0.16666666f * 4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f * 7, 0.16666666f * 4));

		sprite->setAnimationSpeed(JUMP_RIGHT, 10);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 2, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 3, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 4, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 5, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 6, 0.16666666f * 2));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.125f * 7, 0.16666666f * 2));

		sprite->setAnimationSpeed(JUMP_LEFT, 10);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 2, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 3, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 4, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 5, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 6, 0.16666666f * 3));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f * 7, 0.16666666f * 3));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT /* || sprite->animation() == JUMP_LEFT*/)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT /* || sprite->animation() == JUMP_RIGHT*/)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
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

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




