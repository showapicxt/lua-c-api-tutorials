#include "errors.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


#include "stackdump.h"

//cc -o first 04_call_lua_func.c -I /usr/local/openresty/luajit/include/luajit-2.1 -llua-5.1  -lm && ./first

int main(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if(luaL_dofile(L, "call_lua_func.lua"))
		err_exit(L, "luaL_loadfile failed.\n");

	printf("In C, calling Lua->sayHello()\n");
    stackDump(L,"dump pos1");

	lua_getglobal(L, "sayHello");	//Tell it to run test2.lua -> sayHello()
	if(lua_pcall(L, 0, 0, 0))
		err_exit(L, "lua_pcall failed.\n");
    stackDump(L,"dump pos2");

	printf("Back in C again\n");
	printf("\nIn C, calling Lua->add()\n");

	lua_getglobal(L, "add");		//Tell it to run test2.lua -> add()
	lua_pushnumber(L, 1);
	lua_pushnumber(L, 5);
	stackDump(L,"dump pos3");
	if(lua_pcall(L, 2, 1, 0))
		err_exit(L, "lua_pcall failed.\n");
	stackDump(L,"dump pos4");

	printf("Back in C again\n");
	int returnNum = lua_tonumber(L, -1);
	stackDump(L,"dump pos5");

	printf("Returned number : %d\n", returnNum);

	lua_close(L);

	return 0;
}
