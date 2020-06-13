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

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : U0018197");

	std::vector<Vector3> points
	{
		{-50, -50},
		{50, -50},
		{50, 50},
		{-50, 50}
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

		sf::CircleShape c(5);
		
		//this is where the fun stuff is
		for (auto& point : points) {
			Matrix matrixFromPoint{ 3, 1, {{point.m_x}, {point.m_y}, {point.m_z}} };

			//2 x 1 projected2D matrix
			Matrix projectedMatrix = matmul(projectionMatrix, matrixFromPoint);

			auto x = projectedMatrix.GetValue(0, 0);
			auto y = projectedMatrix.GetValue(1, 0);

			
			// draw circle relative to the centre of the screen
			c.setPosition(x + static_cast<float>(window.getSize().x) / 2, y + static_cast<float>(window.getSize().y) / 2);

			window.draw(c);
		}

		window.display();
		angle += 0.01f;
	}
	return 0;
}
