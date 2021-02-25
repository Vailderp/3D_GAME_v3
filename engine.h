#pragma once
#include "Sprite3D.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace math
{
	const float PI = static_cast<float>(acos(-1));
	const float PI_180 = static_cast<float>(acos(-1) / 180);
	float RAD(float DEG)
	{
		return DEG * PI_180;
	}
	float DEG(float RAD)
	{
		return  RAD / PI_180;
	}
	float scale(float min, float max)
	{
		return min / max;
	}
};
class ve
{
public:
	class point
	{
	public:
		float x;
		float y;
		float z;

		point() :
			x{ 0 },
			y{ 0 },
			z{ 0 }
		{}
		point(float X, float Y, float Z) :
			x{ X },
			y{ Y },
			z{ Z }
		{}
	};
	class size
	{
	public:
		float x;
		float y;
		size() :
			x{ 0 },
			y{ 0 }
		{}
		size(float X, float Y) :
			x{ X },
			y{ Y }
		{}
	};
	class rotation
	{
	public:
		float x;
		float y;
		float z;
		rotation() :
			x{ 0 },
			y{ 0 },
			z{ 0 }
		{}
		rotation(float X, float Y, float Z) :
			x{ X },
			y{ Y },
			z{ Z }
		{}
	};
private:
	class FOV
	{
	public:
		float x;
		float y;

		FOV() :
			x{ 60 },
			y{ 60 }
		{}

		FOV(float x, float y) :
			x{ x },
			y{ y }
		{}
	};
	class quad_point
	{
	public:
		float x1;
		float y1;
		float x2;
		float y2;
		float z1;
		float z2;
		quad_point() :
			x1{ 0 },
			y1{ 0 },
			x2{ 0 },
			y2{ 0 }
		{}
		quad_point(float X1, float Y1, float X2, float Y2) :
			x1{ X1 },
			y1{ Y1 },
			x2{ X2 },
			y2{ Y2 }
		{}
	};

public:
	class camera
	{
	private:
		point position_;
		rotation rotation_;
		FOV FOV_;
	public:
		camera() :
			position_{ point() },
			FOV_{ FOV() }
		{}
		camera(float x, float y, float z, float FOV_X, float FOV_Y) :
			position_{ point(x, y, z) },
			FOV_{ FOV(FOV_X, FOV_Y) }
		{}
		void setPosition(float x, float y, float z)
		{
			position_.x = x;
			position_.y = y;
			position_.z = z;
		}
		point getPosition() const
		{
			return position_;
		}
		void setRotation(float x, float y, float z)
		{
			rotation_.x = x;
			rotation_.y = y;
			rotation_.z = z;
		}
		rotation getRotation() const
		{
			return rotation_;
		}
		void setFOV(float x, float y)
		{
			FOV_.x = x;
			FOV_.y = y;
		}
		FOV getFOV() const
		{
			return FOV_;
		}
	};
	class rect_3d
	{
	private:
		quad_point quad_point_;
		point position_;
		size size_;
		rotation rotation_;
		sf::Texture front_texture_;
		sf::Texture back_texture_;
	public:
		sf::Sprite3d drawable;
		rect_3d(float x, float y, float z, float width, float height) :
			quad_point_{quad_point(x, y, x + width, y + height)},
			position_{point(x, y, z)},
			size_{size(width, height)},
			front_texture_{sf::Texture()},
			back_texture_{sf::Texture()},
			drawable{sf::Sprite3d()}
		{
			drawable.setPosition(position_.x, position_.y);
		}

		//TEXTURES
		void setFrontTexture(const std::string& path)
		{
			front_texture_.loadFromFile(path);
			drawable.setTexture(front_texture_);
			drawable.setScale(math::scale(size_.x, front_texture_.getSize().x), math::scale(size_.y, front_texture_.getSize().y));
			if (back_texture_.getSize().x != front_texture_.getSize().x || back_texture_.getSize().y != front_texture_.getSize().y)
			{
				drawable.setBackTexture(front_texture_);
			}
		}
		sf::Texture getFrontTexture() const
		{
			return front_texture_;
		}
		void setBackTexture(const std::string& path)
		{
			back_texture_.loadFromFile(path);
			if (back_texture_.getSize().x == front_texture_.getSize().x && back_texture_.getSize().y == front_texture_.getSize().y)
			{
				drawable.setBackTexture(back_texture_);
				drawable.setScale(math::scale(size_.x, static_cast<float>(back_texture_.getSize().x)), math::scale(size_.y, static_cast<float>(back_texture_.getSize().y)));
			}
		}
		sf::Texture getBackTexture() const
		{
			return back_texture_;
		}

		//POSITION
		void setPosition(float x, float y)
		{
			position_.x = x;
			position_.y = y;
			drawable.setPosition(x, y);
		}
		point getPosition() const
		{
			return position_;
		}

		//SIZE
		void setSize(float x, float y)
		{
			size_.x = x;
			size_.y = y;
			drawable.setScale(math::scale(size_.x, static_cast<float>(front_texture_.getSize().x)), math::scale(size_.y, static_cast<float>(front_texture_.getSize().y)));
		}
		size getSize() const
		{
			return size_;
		}

		//ROTATION
		void setRotation(float x, float y, float z)
		{
			rotation_.x = x;
			rotation_.y = y;
			rotation_.z = z;
			drawable.setRotation3d(sf::Vector3f(rotation_.x, rotation_.y, rotation_.z));
		}
		rotation getRotation() const
		{
			return rotation_;
		}

		//MOVE
		void move(float x, float y, float z) 
		{
			position_.x += x;
			position_.y += y;
			position_.z += z;
		}
	};
};
