#pragma once

#include <cstdio>
#include <iostream>
#include <string.h>
#include <msgpack.hpp>

class info {
public:
	std::string id;
	std::string passwd;

	info();
	info(std::string, std::string);
};