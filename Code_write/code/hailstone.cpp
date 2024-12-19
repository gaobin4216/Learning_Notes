//有穷性
//HailStone序列，目前HailStone序列还未被证明是否有穷，所以它未必是一个算法。
//程序！=算法
#include<iostream>
#include<vector>
int hailstone(int n, std::vector<int> &hailstone_number);
int main()
{
    int n=15;
    std::vector<int> hailstone_number;
    std::cout<< hailstone(n,hailstone_number) <<std::endl;
    std::vector<int>::iterator ite=hailstone_number.begin();
    for(;ite!=hailstone_number.end();ite++)
        std::cout<<*ite<<" ";
    std::cout<<std::endl;
    return 0;
}
int hailstone(int n, std::vector<int> &hailstone_number)
{
   hailstone_number.push_back(n);
   int length=1;
   while(1<n)
   {
       n%2==0 ? n=n/2 : n=3*n+1;
       hailstone_number.push_back(n);
       length++;
   }
   return length;
} 