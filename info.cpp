#include "info.h"
#include <string.h>

info::info(){
	this->id = "";
	this->passwd = "";
}

info::info(std::string id, std::string passwd){
	this->id = id;
	this->passwd = passwd;
}