#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <thread>

#include "../Dependecies/curl/curl.h"
#pragma comment(lib, "LibCurl.lib")

enum class CloudActions_t : int {
	Initialization = -1,
	None = 0,
	GetConfigList = 1,
	GetConfigData = 2,
	CreateConfig = 3,
	SaveConfig = 4
};

struct CloudConfig_t
{
	int ID;
	int UpdatedAt;
	std::string Name;
	std::string Owner;
	std::string Author;
	std::string SecureID;
	bool Market;
};

class C_CloudConfigs
{
public:
};

inline C_CloudConfigs* g_CloudConfigs = new C_CloudConfigs( );
static VOID WINAPI HandleConfigs( )
{

}