#pragma once
#include <string>

template<typename T>
concept SomeString = std::convertible_to<T, std::string>;

