#include <set>
#include <iostream>


int main()
{
    std::set<int> set = {1, 2, 3, 5};
#if 1

    auto[iter, inserted] = set.insert(3);

    if(!inserted)
    {
        set.erase(iter);
        set.insert(6);
    }

    auto[iter2, inserted2] = set.insert(4);

    if(!inserted2)
    {
        set.erase(iter2);
        set.insert(4);
    }
#else

    auto iter = set.find(3);
    if (iter != set.end()) {
        set.erase(iter);
        set.insert(6);
    } else 
    {
        set.insert(3);
    }

    auto iter2 = set.find(4);
    if (iter2 != set.end()) {
        set.erase(iter);
        set.insert(4);
    } else 
    {
        set.insert(4);
    }

#endif
    for(const auto & elem : set)
    {
        std::cout << elem;
    }
}