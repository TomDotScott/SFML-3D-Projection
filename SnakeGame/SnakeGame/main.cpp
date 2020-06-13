#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"

struct Matrix {
public:
	explicit Matrix(int _rows, int _cols, const std::vector<std::vector<float>>& _values = std::vector<std::vector<float>>()) {
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

	int m_rows;
	int m_columns;
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
				sum += a.m_values[i][k] * b.m_values[k][j];
			}
			c.SetValue(sum, i, j);
		}
	}

	return c;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : U0018197");

	std::vector<Vector3> points
	{
		{-50, -50},
		{50, -50},
		{50, 50},
		{-50, 50}
	};

	// Projection Matrix
	float projection[2][3]
	{
		{1, 0, 0},
		{0, 1, 0}
	};

	Matrix m1(3, 3, { { 1, 2, 1 },{0, 1, 0}, {2, 3, 4} });
	Matrix m2(3, 2, { { 2, 5 },{6, 7 }, {1, 8} });

	Matrix m3 = matmul(m1, m2);
	for (const auto& row : m3.m_values) {
		for (auto column : row) {
			std::cout << column << " ";
		}
		std::cout << std::endl;
	}

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

		//this is where the fun stuff is
		for (auto& point : points) {
			sf::CircleShape c(5);
			// draw circle relative to the centre of the screen
			c.setPosition(point.m_x + static_cast<float>(window.getSize().x) / 2, point.m_y + static_cast<float>(window.getSize().y) / 2);

			window.draw(c);
		}

		window.display();
	}
	return 0;
}
