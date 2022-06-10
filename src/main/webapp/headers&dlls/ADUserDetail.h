#include <objbase.h>
#include <wchar.h>
#include <activeds.h>
#include <Windows.h>
#include "atltime.h"
#include <sddl.h>
#include <iostream>
#include <string>
#include <string>
#include <comutil.h>
#include<vector>
#include<algorithm>
using namespace std;

#ifdef ACTIVE_DIRECTORY_API
#define ACTIVE_DIRECTORY_API __declspec(dllexport)
#else
#define ACTIVE_DIRECTORY_API __declspec(dllimport)
#endif
#pragma once

ACTIVE_DIRECTORY_API vector<string> GetActiveDirectoryUsersData();