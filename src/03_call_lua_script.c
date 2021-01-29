#include "errors.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "stackdump.h"

//cc -o first 03_call_lua_script.c -I /usr/local/openresty/luajit/include/luajit-2.1 -llua-5.1  -lm && ./first
int main(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	printf("In C, calling Lua\n");
	if(luaL_dofile(L, "call_lua_script.lua"))
		err_exit(L, "luaL_loadfile failed.\n");
    stackDump(L,"dump pos1");


	printf("Back in C again\n");

	lua_close(L);

	return 0;
}
