//
// Пример простой библиотеки на C++ для вызова ее из LUA
// http://quik2dde.ru/viewtopic.php?id=18
//

#include <windows.h>
#include <process.h>

// в случае вызова функций из LUA-кода во внешней DLL
// необходимо определить эти константы до подключения заголовочных файлов LUA
#define LUA_LIB
#define LUA_BUILD_AS_DLL

// заголовочные файлы LUA из дистрибутива LUA
extern "C" {
#include "../contrib/lauxlib.h"
#include "../contrib/lua.h"
}

// стандартная точка входа для DLL
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

// реализация функций, вызываемых из LUA

static int forLua_GetCurrentThreadId(lua_State *L) {
	// возвращаем одно значение, полученное от Win API функции
    lua_pushinteger(L, GetCurrentThreadId());
	return(1);
}

static int forLua_MultTwoNumbers(lua_State *L) {
	// получаем первый и второй параметры вызова функции из стека с проверкой каждого на число
    double d1 = luaL_checknumber(L, 1);
    double d2 = luaL_checknumber(L, 2);

	// помещаем в стек результат умножения
    lua_pushnumber(L, d1 * d2);

    return(1);  // эта функция возвращает одно значение
}
	
static int forLua_MultAllNumbers(lua_State *L) {
	const int n = lua_gettop(L);  // количество переданных аргументов
	double res = 1;
	bool isNumberFound = false;
	for (int i = 1; i <= n; ++i)
		if (lua_type(L, i) == LUA_TNUMBER)
		{
			res *= lua_tonumber(L, i);
			isNumberFound = true;
		}

    if (isNumberFound)
		lua_pushnumber(L, res);
	else
		lua_pushnil(L);

    return(1);
}
	
// регистрация реализованных в dll функций, чтобы они стали "видимы" для LUA

static struct luaL_reg ls_lib[] = {
    {"GetCurrentThreadId", forLua_GetCurrentThreadId},
    {"MultTwoNumbers", forLua_MultTwoNumbers},
    {"MultAllNumbers", forLua_MultAllNumbers},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_luacdll(lua_State *L) {
    luaL_openlib(L, "luacdll", ls_lib, 0);
    return 0;
}

