#include "errors.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


#include "stackdump.h"
//cc -o first  05_call_lua_table.c -I /usr/local/openresty/luajit/include/luajit-2.1 -llua-5.1  -lm && ./first


int main(void)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if(luaL_dofile(L, "call_lua_table.lua"))
		err_exit(L, "luaL_loadfile failed.\n");

    printf("In C,  calling Lua->tablehandler()\n");
    lua_getglobal(L, "tablehandler");
    lua_newtable(L);					// Push empty table onto stack, table now at -1
    stackDump(L,"dump pos1");

    lua_pushliteral(L, "name");	// Puah a key onto stack, table now at -2
    stackDump(L,"dump pos2");


    lua_pushliteral(L, "cxt");		// Puash a value onto stack, table now at -3
    lua_settable(L, -3);				// Take key and value, put into table at -3, then pop key and value so table again at -1

    lua_pushliteral(L, "age");
    lua_pushliteral(L, "30");
    lua_settable(L, -3);

    if(lua_pcall(L, 1, 1, 0))			// Run function.
    	err_exit(L, "lua_pcall failed");

    printf("============ Back in C again, Iterating thru returned table ============\n");

    lua_pushnil(L);						// Make sure lua_next starts at beginning
    stackDump(L,"dump pos3");

//  lua_next() 这个函数的工作过程是：
//  1) 先从栈顶弹出一个 key
//  2) 从栈指定位置的 table 里取下一对 key-value，先将 key 入栈再将 value 入栈
//  3) 如果第 2 步成功则返回非 0 值，否则返回 0，并且不向栈中压入任何值

    const char *k, *v;
    while(lua_next(L, -2)) {			// Table location at -2 in stack
    	v = lua_tostring(L, -1);
    	k = lua_tostring(L, -2);

        //只弹出1个。还留有1个让lua_next去弹
    	lua_pop(L, 1);					// Remove value, leave in place to guide next lua_next().
    	printf("%s = %s\n", k, v);
    }

    lua_close(L);

    return 0;
}
