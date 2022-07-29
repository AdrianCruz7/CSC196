#pragma once
#include <cstdint>
#include <istream>
#include <string>

namespace neu
{
	//typedef unsigned char u8_t;
	//using u8_t = unsigned char;

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		
		friend std::istream& operator >> (std::istream& stream, Color& color);
		//inline
	};

	
	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		getline(stream, line);
		//line = { r, g, b }

		std::string str;

		//red
		str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		color.r = (uint8_t)(stof(str) * 255);
		//line = g, b }

		//setting line to another sub section of the string to read green and blue 
		line = line.substr(line.find(",") + 1);
		
		//green
		str = line.substr(0, line.find(","));
		color.g = (uint8_t)(stof(str) * 255);
		
		//blue
		str = line.substr(line.find(",") + 1, line.find("}") - line.find(",") + 1);
		color.b = (uint8_t)(stof(str) * 255);
		
		//default alpha
		color.a = 255;
		
		return stream;
	}

}

//friend inline std::istream& operator >> (std::istream& stream, Vector2& v, Color& color)