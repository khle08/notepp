#include <iostream>
#include <cctype>
#include <random>


int randint(int n1, int n2, int total, std::vector<int>& vec)
{
	std::random_device os_seed;
    const uint_least32_t seed = os_seed();
    
    std::mt19937 generator( seed );
    std::uniform_int_distribution< uint_least32_t > distribute( n1, n2 );

    for( int repetition = 0; repetition < total; ++repetition ) {
        int k = distribute( generator );
        vec.push_back(k);
    }
    return 0;
}


std::string idGenerator(int upsample, int length)
{
    std::string character = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz1234567890";

    std::vector<int> vec1;
    randint(0, character.size() - 1, upsample, vec1);

    std::string database = "";
    for (int i = 0; i < vec1.size(); i++) {
        database += character[vec1[i]];
    }

    std::vector<int> vec2;
    randint(0, upsample, length, vec2);

    std::string output = "";
    for (int i = 0; i < vec2.size(); i++) {
        output += database[vec2[i]];
    }

    return output;
}


int main( void )
{
    std::string id = idGenerator(800, 32);

	std::cout << id << std::endl;
    return 0;
}