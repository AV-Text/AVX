#pragma once
#include <avxgen.h>
#include <vector>
#include <string>

#include <ryml.hpp>

class AVXFound;

class AVXFind
{
public:
    std::vector<AVXFound*> founds;
    std::string find;

    AVXFind()
    {
        this->find = "";
        this->current = nullptr;
    }
    AVXFind(const char* search)
    {
        this->find = search;
        this->current = nullptr;
    }
    ~AVXFind()
    {
        ;
    }
    bool add(AVXFound* found);
 //   void build(ryml::ConstNodeRef& parentCollection);

private:
    AVXFound* current;
public:
    inline AVXFound* getCurrent()
    {
        return this->current;
    }
};
    