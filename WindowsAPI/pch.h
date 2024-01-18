#pragma once

#include "Types.h"
#include "Enums.h"
#include "Defines.h"
#include "Utils.h"
#include "Values.h"
#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

#include <format>//c++20 버전추가

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

//현재 실행되고있는 파일 이름과 몇번째 줄인지 출력가능
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif