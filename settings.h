#pragma once
#include <vaibin.h>

map<string, string> conf = vb::ReadConfFile("settings.txt");
namespace settings
{
	namespace render
	{
		float FOV = stof(conf["FOV"]);
	}
}
