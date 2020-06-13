#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"

struct Matrix {
public:
	explicit Matrix(const int _rows, const int _cols, const std::vector<std::vector<float>>& _values = std::vector<std::vector<float>>()) {
		m_rows = _rows;
		m_columns = _cols;

		if (!_values.empty()) {
			for (int i = 0; i < m_rows; ++i) {
				std::vector<float> currentRow;
				for (int j = 0; j < m_columns; j++) {
					currentRow.push_back(_values[i][j]);
				}
				m_values.push_back(currentRow);
			}
		} else {
			for(int row = 0; row < m_rows; row++)
			{
				std::vector<float> currentRow;
				for(int column = 0; column < m_columns; column++)
				{
					currentRow.push_back(0.f);
				}
				m_values.push_back(currentRow);
			}
		}
	}

	void SetValue(float _val, int i, int j)
	{
		m_values[i][j] = _val;
	}

	float GetValue(int i, int j) const
	{
		return m_values[i][j];
	}

	int m_rows;
	int m_columns;
private:
	std::vector<std::vector<float>> m_values;
};


Matrix matmul(Matrix& a, Matrix& b) {
	const int n = a.m_rows;
	const int m = a.m_columns;
	const int p = b.m_columns;
	Matrix c(n, p);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			float sum{};
			for (int k = 0; k < m; k++) {
				sum += a.GetValue(i, k) * b.GetValue(k, j);
			}
			c.SetValue(sum, i, j);
		}
	}
	return c;
}

void Connect(Vector3 _a, Vector3 _b, sf::RenderWindow& _window)
{
	sf::VertexArray lines(sf::LineStrip, 2);
	lines[0].position = { _a.m_x + static_cast<float>(_window.getSize().x) / 2, _a.m_y + +static_cast<float>(_window.getSize().y) / 2};
	lines[1].position = { _b.m_x + static_cast<float>(_window.getSize().x) / 2, _b.m_y + +static_cast<float>(_window.getSize().y) / 2 };
	_window.draw(lines);
}


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : U0018197");

	float multiplier{ 200.f };
	
	std::vector<Vector3> points
	{
		{-0.5, -0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		{ 0.5,  0.5, -0.5},
		{-0.5,  0.5, -0.5},
		{-0.5, -0.5,  0.5},
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5,  0.5},
		{-0.5,  0.5,  0.5}
	};

	Matrix projectionMatrix(2, 3, { {1, 0, 0}, {0, 1, 0} });
	
	float angle = 0;
	
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		window.clear();

		Matrix rotateX(3, 3, { {          1,           0,           0},
											   {          0,  cos(angle), -sin(angle)},
											   {          0,  sin(angle),  cos(angle)}
			});

		Matrix rotateY(3, 3, { { cos(angle),           0,  sin(angle)},
											   {          0,           1,           0},
											   {-sin(angle),           0,  cos(angle)}
			});

		Matrix rotateZ(3, 3, { { cos(angle), -sin(angle),            0},
											   { sin(angle),  cos(angle),            0},
											   {          0,           0,            1}
			});

		std::vector<Vector3> projectedPoints{};

		//this is where the fun stuff is
		for (int i = 0; i < points.size(); i++) {
			Matrix v{ 3, 1, {{points[i].m_x}, {points[i].m_y}, {points[i].m_z}} };

			Matrix rotated = matmul(rotateY, v);
			rotated = matmul(rotateX, rotated);
			rotated = matmul(rotateZ, rotated);

			Matrix projected2DMatrix = matmul(projectionMatrix, rotated);

			projectedPoints.emplace_back(projected2DMatrix.GetValue(0, 0) * multiplier, projected2DMatrix.GetValue(1, 0) * multiplier);
		}
		/*sf::CircleShape c(10);

		for (auto point : projectedPoints) {
			c.setPosition(point.m_x + static_cast<float>(window.getSize().x) / 2, point.m_y + static_cast<float>(window.getSize().y) / 2);
			window.draw(c);
		}*/

		for (int i = 0; i < 4; i++)
		{
			Connect(projectedPoints[i], projectedPoints[(i + 1) % 4], window);
			Connect(projectedPoints[i + 4], projectedPoints[((i + 1) % 4) + 4], window);
			Connect(projectedPoints[i], projectedPoints[i + 4], window);
		}
		
		window.display();
		angle += 0.0005f;
	}
	return 0;
}
