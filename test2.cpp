#include <iostream>
#include <set>

class a
{
private:
    /* data */
public:
    const std::set<int> getSet()
    {
        std::set<int> sets = {1, 2, 3, 4};
        return sets;
    }
};


int main()
{

    a a1;
    const std::set<int> nset = a1.getSet();

    std::cout << nset.size();

}