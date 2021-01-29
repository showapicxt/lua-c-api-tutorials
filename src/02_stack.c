#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "stackdump.h"




//cc -o first 02_stack.c -I /usr/local/openresty/luajit/include/luajit-2.1 -llua-5.1  -lm && ./first

int main(void)
{
	lua_State *L = luaL_newstate();
	lua_pushboolean(L, 1);
	lua_pushinteger(L, 100);
	lua_pushnumber(L, 10.011);
	lua_pushstring(L, "hello");
	lua_pushnil(L);
	printf("head    tail  \n\n" );
	printf("%d %d %d",  1,2,3);
	printf("\n\n");

	stackDump(L,"");

	lua_pushvalue(L, 1);	//将索引为1的元素压入栈顶
	printf("%s",  "将索引为1的元素压入栈顶 :");
	stackDump(L,"");


	lua_settop(L, 4);	//设置栈顶为4
	printf("%s",  "设置栈顶为4 :");
	stackDump(L,"");

	lua_insert(L, 3);	//移动栈顶元素到3
	printf("%s",  "移动栈顶元素到3 :");
	stackDump(L,"");

	lua_replace(L, 3);	//将栈顶元素移动到3位置，弹出栈顶元素
	printf("%s",  "将栈顶元素移动到3位置，弹出栈顶元素 :");
	stackDump(L,"");


	lua_pop(L, 1);	//从栈尾弹出几个
	printf("%s",  "栈尾弹出1个 :");
	stackDump(L,"");

	lua_close(L);
	return 0;
}