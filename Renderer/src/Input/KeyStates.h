#pragma once
#include <unordered_map>

class Key
{
public:
	static std::unordered_map<int, bool>m_Keys;
	static void Init();
};
