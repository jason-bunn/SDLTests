#include "Player.h"
#include "InputHandler.h"
#include "Game.h"

Player::Player() : ShooterObject()
{

}


void Player::draw(SDL_Renderer* pRenderer)
{
	ShooterObject::draw();
}

void Player::update()
{
	//if the level is complete, fly off the screen
	if (TheGame::Instance()->getLevelComplete())
	{
		if (m_position.getX() >= TheGame::Instance()->getGameWidth())
		{
			TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
		}
		else
		{
			m_velocity.setY(0);
			m_velocity.setX(3);
			ShooterObject::update();
			handleAnimation();
		}
	}
	else
	{
		//if the player is not doing its death animation then update
		if (!m_bDying)
		{
			//reset velocity
			m_velocity.setX(0);
			m_velocity.setY(0);

			// get input
			handleInput();
			//do normal postion + velocity update
			ShooterObject::update();

			//update the animation
			handleAnimation();
		}
		else //if the player is doing the death animation
		{
			m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

			//if death animation has completed
			if (m_dyingCounter == m_dyingTime)
			{
				//ressurect the player
				ressurect();
			}

			m_dyingCounter++;
		}
	}
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->joysticksInitialized())
	{
		if (TheInputHandler::Instance()->xvalue(0, 1) > 0 ||
			TheInputHandler::Instance()->xvalue(0, 1) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
		}

		if (TheInputHandler::Instance()->yvalue(0, 1) > 0 ||
			TheInputHandler::Instance()->yvalue(0, 1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
		}

		if (TheInputHandler::Instance()->xvalue(0, 2) > 0 ||
			TheInputHandler::Instance()->xvalue(0, 2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
		}

		if (TheInputHandler::Instance()->yvalue(0, 2) > 0 ||
			TheInputHandler::Instance()->yvalue(0, 2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
		}

		//check if button3 pressed
		if (TheInputHandler::Instance()->getButtonState(0, 3))
		{
			m_velocity.setX(1);
		}
	}
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}

	//mouse follow
	//Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = (*vec - m_position) / 100;
}

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

	m_position.setX(10);
	m_position.setY(200);
	m_bDying = false;

	m_textureID = "player";

	m_currentFrame = 0;
	m_numFrames = 5;
	m_width = 101;
	m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleAnimation()
{
	//if the player is invulnerable we can flash its alpha to let people know
	if (m_invulnerable)
	{
		//invulnerability is finished set values back
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else //otherwise flash the alpha
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}
		}
	}

	//increment our counter
	m_invulnerableCounter++;

	//if the player is not dead then we can change the angle with the velocity to give the impression of a moving helicopter
	if (!m_bDead)
	{
		if (m_velocity.getX() < 0)
		{
			m_angle = -10.0;
		}
		else if (m_velocity.getX() > 0)
		{
			m_angle = 10.0;
		}
		else
		{
			m_angle = 0.0;
		}
	}

	//our standard animation code for helicopter propellors
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
}

void Player::clean()
{

}