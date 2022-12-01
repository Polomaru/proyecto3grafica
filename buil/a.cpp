#include <iostream>
#include <cmath>
#include <random>
using namespace std;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-10, 10); // define the range
struct tunel{
    // vector<vec3> rpoints;
    void cre()
    {
        int x1 = 0,y1 = 0,z1 = 0;
        for(int i=0;i<2;i++)
        {
            float r1;int x,y,z;
            do{
                x = distr(gen),y=distr(gen),z=distr(gen);
                r1 = pow((pow((x - x1),2) +pow((y - y1),2)+pow((z - z1),2)),0.5);
                std::cout<<r1<<" ";
            }while(r1<6 or r1>10);
            x1=x;y1=y;z1=z;
            std::cout<<x<<y<<z<<" ";
            // rpoints.emplace_back(vec3(distr(gen), distr(gen), distr(gen)));
        }
    }
};
int main()
{
    tunel a;
    a.cre();
}