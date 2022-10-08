#include "class.h"

#define print(x) std::cout << x << std::endl

LandOwner::LandOwner()
{
	SetNickName("default owner");
	SetSex("crypto");
	SetExp(0);
	SetGold(1000);
	print("LandOwner()");
}

// : behind the method is telling that the "m_NickName" attribute will be
// modified by the input parameter nickName.
LandOwner::LandOwner(std::string nickName)//: m_NickName(nickName)
{
	SetSex("crypto");
	SetExp(0);
	SetGold(1000);
	print("param1: " << m_NickName);
	m_NickName = nickName;
	print("LandOwner(std::string nickName)");
}

LandOwner::LandOwner(std::string nickName, std::string sex, int gold, long exp)
	: m_NickName(nickName), m_Sex(sex), m_Gold(gold), m_Exp(exp)
{
	print("LandOwner(std::string nickName, std::string sex, int gold, long exp)");
}

void LandOwner::ShowInfo()
{
	print("nick name: " << GetNickName());
	print("sex: " << GetSex());
	print("gold: " << GetGold());
	print("exp: " << GetExp());
}

LandOwner::~LandOwner()
{
	print(GetNickName() << " is released!");
}

