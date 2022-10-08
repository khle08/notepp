#include <iostream>
#include <string>

#define print(x) std::cout << x << std::endl

class LandOwner
{
public:
	LandOwner();
	LandOwner(std::string);
	LandOwner(std::string, std::string, int, long);
	~LandOwner();

	std::string GetNickName() {return m_NickName;}
	std::string GetSex(){return m_Sex;}
	int GetGold() {return m_Gold;}
	long GetExp() {return m_Exp;}

	void SetNickName(std::string val){m_NickName = val;}
	void SetSex(std::string val){m_Sex = val;}
	void SetGold(int val) {m_Gold = val;}
	void SetExp(long val) {m_Exp = val;}

	void ShowInfo();

protected:

private:
	std::string m_NickName;
	std::string m_Sex;
	int m_Gold;
	long m_Exp;
};

