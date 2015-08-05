#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() :
PlatformerObject(),
m_callback(0),
m_bReleased(true)
{

}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
	PlatformerObject::load(std::move(pParams));
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	PlatformerObject::draw();
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();


	//check if the mouse cursor is within the bounds of the button
	if (pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY())
	{
		//if the left mouse button is clicked change button state **REPLACE WITH COMMAND PATTERN**
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			if (m_callback != 0)
			{
				m_callback();
			}

			m_bReleased = false;
		}
		//if the action button has not been clicked, change state to mouse over
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	PlatformerObject::clean();
}