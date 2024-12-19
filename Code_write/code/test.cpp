#include<iostream>
#include<bitset>

int main()
{
    int a=5;    
    int b = a>>1;
    std::bitset<8> ain(a);
    std::bitset<8> bin(b);
    std::cout<< ain<<"\n"<<bin <<std::endl;
    return 0;
}