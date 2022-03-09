/// <summary>
/// Leon Nolte
/// 17 January 2022
/// </summary>

#include "MyVector2.h"

// name


/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(const sf::Vector2f t_vectorA)
{
	float sumOfSquares = (t_vectorA.x * t_vectorA.x ) + (t_vectorA.y * t_vectorA.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

/// <summary>
/// ||v||^2 = x^2 + y^2
/// Gets squared version of vector length
/// </summary>
/// <param name="t_vectorA"> vector that calculation is applied to </param>
/// <returns> square of vector length </returns>
float vectorLengthSquared(const sf::Vector2f t_vectorA)
{
	float solution = 0.0f;
	solution = t_vectorA.x * t_vectorA.x + t_vectorA.y * t_vectorA.y;
	return solution;
}

/// <summary>
/// u x v = x of u * y of v - y of u * x of y
/// gets cross product of two vectors
/// </summary>
/// <param name="t_vectorA"> first vector (u) </param>
/// <param name="t_VectorB"> second vector (v) </param>
/// <returns> cross product of u x v </returns>
float vectorCrossProduct(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float solution = 0.0f;

	solution = t_vectorA.x * t_VectorB.y - t_vectorA.y * t_VectorB.x;

	return solution;
}

/// <summary>
/// u.v = x of u * x of v + y of u * y of v
/// gets dot-product of two vectors
/// </summary>
/// <param name="t_vectorA"> first vector (u) </param>
/// <param name="t_VectorB"> second vector (v) </param>
/// <returns> dot-product value </returns>
float vectorDotProduct(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float solution = 0.0f;

	solution = t_vectorA.x * t_VectorB.x + t_vectorA.y * t_VectorB.y;

	return solution;
}

/// <summary>
/// alpha = acos (u.v / ||u|| * ||v||)
/// calculates angle between two vectors
/// </summary>
/// <param name="t_vectorA"> vector u </param>
/// <param name="t_VectorB"> vector v </param>
/// <returns> angle between vectors </returns>
float vectorAngleBetween(const sf::Vector2f t_vectorA, const sf::Vector2f t_VectorB)
{
	float solution = 0.0f;

	solution = acos(vectorDotProduct(t_vectorA, t_VectorB) / (vectorLength(t_vectorA) * vectorLength(t_VectorB)));

	return solution;
}

/// <summary>
/// v rotated = ( cos alpha		-sin alpha ) x v
///				( sin alpha		cos alpha  )
/// rotates vector by input angle (in radians)
/// </summary>
/// <param name="t_vectorA"> vector that is being rotated </param>
/// <param name="t_angleRadians"> angle by which vector is rotated </param>
/// <returns></returns>
sf::Vector2f vectorRotateBy(const sf::Vector2f t_vectorA, const  float t_angleRadians)
{
	sf::Vector2f solution;

	solution.x = cos(t_angleRadians) * t_vectorA.x + -sin(t_angleRadians) * t_vectorA.y;
	solution.y = sin(t_angleRadians) * t_vectorA.x + cos(t_angleRadians) * t_vectorA.y;

	return solution;
}

/// <summary>
/// u projected = (u.v / (||v||^2)) x v
/// projects one vector onto another
/// </summary>
/// <param name="t_vectorA"> vector that is being projected </param>
/// <param name="t_onto"> vector that is being projected onto </param>
/// <returns> projection vector </returns>
sf::Vector2f vectorProjection(const sf::Vector2f t_vectorA, const  sf::Vector2f t_onto)
{
	sf::Vector2f solution;

	solution.x = (vectorDotProduct(t_vectorA, t_onto) / vectorLengthSquared(t_onto)) * t_onto.x;
	solution.y = (vectorDotProduct(t_vectorA, t_onto) / vectorLengthSquared(t_onto)) * t_onto.y;

	return solution;
}

/// <summary>
/// u rejected = u - (u.v / (||v||^2)) x v
/// gets vector rejection of two vectors
/// </summary>
/// <param name="t_vectorA"> vector being rejected </param>
/// <param name="t_onto"> vectors that rejection is projected onto </param>
/// <returns> rejection vector </returns>
sf::Vector2f vectorRejection(const sf::Vector2f t_vectorA, const  sf::Vector2f t_onto)
{
	sf::Vector2f solution;
	const sf::Vector2f projection = vectorProjection(t_vectorA, t_onto);	// projection vector used for quicker calculation

	solution.x = t_vectorA.x - projection.x;
	solution.y = t_vectorA.y - projection.y;

	return solution;
}

/// <summary>
/// scalar projection = ||v|| * sin(alpha), whereby alpha = angle between u and v
/// gets scalar projection of one vector onto another
/// </summary>
/// <param name="t_vector"> vector being scalar projected </param>
/// <param name="t_onto"> vector being scalar projected onto </param>
/// <returns> scalar projection </returns>
float vectorScalarProjection(const sf::Vector2f t_vector, const  sf::Vector2f t_onto)
{
	float solution = 0.0f;

	solution = vectorLength(t_vector) * sin(vectorAngleBetween(t_vector, t_onto));

	return solution;
}

/// <summary>
/// v unit = v/||v||
/// </summary>
/// <param name="t_vectorA"> vector who is turned into its unit </param>
/// <returns> unit vector with direction of input vector </returns>
sf::Vector2f vectorUnitVector(const sf::Vector2f t_vectorA)
{
	sf::Vector2f solution{ 0.0f, 0.0f };

	solution.x = t_vectorA.x / vectorLength(t_vectorA);
	solution.y = t_vectorA.y / vectorLength(t_vectorA);

	return solution;
}
