#pragma once
#include <vector>
#include <memory>
#include <string>
/* Plot specification: 
*/

namespace Anim
{ 
struct Plot
{
    std::string name;
    std::vector<float> data;
};
}