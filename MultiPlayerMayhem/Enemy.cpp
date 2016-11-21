#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	m_shape.setRadius(3.0f);
	m_shape.setFillColor(Color(255, 0, 0));
	m_shape.setOrigin(3.0f, 3.0f);

	m_lines.push_back(vector<Line>());
}

Enemy::~Enemy()
{
}

void Enemy::Render(RenderWindow & r)
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

void Enemy::Update(float deltaTime)
{
	//m_shape.setPosition(m_position);
}

void Enemy::SetPosition(Vector2f pos)
{
	m_position = pos;

	if (m_tail.size() > 0 && !stopDrawing)
	{
		m_lines.at(m_lines.size() - 1).push_back(Line(m_tail.at(m_tail.size() - 1), m_position, m_shape.getFillColor()));
	}

	if (!stopDrawing)
	{
		m_tail.push_back(pos);
	}
}

void Enemy::Deserialize(vector<string> token)
{
	if (token.size() >= 4)
	{
		float x = stof(token.at(1));
		float y = stof(token.at(2));

		bool tempDrawing = stoi(token.at(3));

		if (stopDrawing && !tempDrawing)
		{
			m_lines.push_back(vector<Line>());
		}


		if (currentTick % 10 == 0)
		{
			SetPosition(Vector2f(x, y));
		}

		if (stopDrawing && !tempDrawing)
		{
			m_tail.push_back(Vector2f(x, y));
		}

		stopDrawing = tempDrawing;

		m_shape.setPosition(Vector2f(x, y));
		currentTick++;
	}
}