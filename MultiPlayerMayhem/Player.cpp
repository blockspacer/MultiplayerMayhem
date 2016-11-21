#include "Player.h"
#include <iostream>
#include <sstream> 

Player::Player()
{
	srand(time(NULL));

	m_shape.setRadius(3.0f);
	m_shape.setFillColor(Color(0, 0, 255));
	m_shape.setOrigin(3.0f, 3.0f);

	m_position.x = (rand() % 600) + 100;
	m_position.y = (rand() % 400) + 100;

	cout << "Start position: " << m_position.x << ", " << m_position.y << endl;

	// Random start direction calculation
	if (rand() % 2 == 0)
	{
		m_velocity.x = rand() % 2 ? MAX_VELOCITY : -MAX_VELOCITY;
		m_velocity.y = (rand() % (int)(MAX_VELOCITY * 2)) - MAX_VELOCITY;
	}
	else
	{
		m_velocity.x = (rand() % (int)(MAX_VELOCITY * 2)) - MAX_VELOCITY;
		m_velocity.y = rand() % 2 ? MAX_VELOCITY : -MAX_VELOCITY;
	}

	setNewStopDrawingValues();
}

Player::~Player()
{
}

void Player::Render(RenderWindow & r)
{
	CircleShape temp;

	for (auto& obj : m_tail)
	{
		temp = CircleShape(m_shape);
		temp.setPosition(obj);
		r.draw(temp);
	}

	for (auto& lines : m_lines)
	{
		for (auto & line : lines)
		{
			r.draw(line);
		}
	}

	if (m_tail.size() > 0 && !stopDrawing)
	{
		r.draw(Line(m_tail[m_tail.size() - 1], m_position, m_shape.getFillColor()));
	}

	r.draw(m_shape);
}

void Player::Update(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (m_velocity.x >= MAX_VELOCITY && m_velocity.y < MAX_VELOCITY) // go to down and right
		{
				m_velocity.y += TURN_RATE;
		} 
		else if (m_velocity.x > -MAX_VELOCITY && m_velocity.y >= MAX_VELOCITY) // go to down and left
		{
			m_velocity.x -= TURN_RATE;
		}
		else if (m_velocity.y > -MAX_VELOCITY && m_velocity.x <= -MAX_VELOCITY) // go to left and up
		{
			m_velocity.y -= TURN_RATE;
		}
		else if (m_velocity.y <= -MAX_VELOCITY && m_velocity.x < MAX_VELOCITY) // Right and Up
		{
			m_velocity.x += TURN_RATE;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (m_velocity.y <= -MAX_VELOCITY && m_velocity.x > -MAX_VELOCITY) // Left UP
		{
			m_velocity.x -= TURN_RATE;
		} 
		else if (m_velocity.y < MAX_VELOCITY && m_velocity.x <= -MAX_VELOCITY) // Left bottom
		{
			m_velocity.y += TURN_RATE;
		}
		else if (m_velocity.y >= MAX_VELOCITY && m_velocity.x < MAX_VELOCITY) // right bottom
		{
			m_velocity.x += TURN_RATE;
		}
		else if (m_velocity.y > -MAX_VELOCITY && m_velocity.x >= MAX_VELOCITY) // RIGHT TOP
		{
			m_velocity.y -= TURN_RATE;
		}
	}

	currentTime += deltaTime * 1000; // so its millisecs not seconds

	if (currentTime < nextStopDrawing)
	{	
		if (currentTick % 10 == 0)
		{
			if (m_tail.size() > 0 && !stopDrawing)
			{
				m_lines.at(m_lines.size() - 1).push_back(Line(m_tail.at(m_tail.size() - 1), m_position, m_shape.getFillColor()));
			}

			stopDrawing = false;

			m_tail.push_back(Vector2f(m_position));
		}
		currentTick++;
	}
	else if (currentTime > nextStopDrawing + stopDrawingAfter)
	{
		setNewStopDrawingValues();
		currentTick = 0;
	}
	else
	{
		stopDrawing = true;
	}
	m_position += m_velocity * deltaTime;
	m_shape.setPosition(GetPosition());
}

string Player::Serialize()
{
	ostringstream ss;

	ss << "ENEMY" << ";" << m_position.x << ";" << m_position.y << ";" << stopDrawing << ";";
	return ss.str();
}

Vector2f Player::normalize(const Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return Vector2f(source.x / length, source.y / length);
	else
		return source;
}

void Player::setNewStopDrawingValues()
{
	nextStopDrawing = currentTime + (rand() % 5000) + 3000;
	stopDrawingAfter = (rand() % 300) + 500;

	m_lines.push_back(vector<Line>());
}
