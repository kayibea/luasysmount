#define _GNU_SOURCE

#include <errno.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <string.h>
#include <sys/mount.h>

#define MT "sysmount"

static int push_luaerror(lua_State *L) {
  lua_pushnil(L);
  lua_pushstring(L, strerror(errno));
  lua_pushinteger(L, errno);
  return 3;
}

int l_mount(lua_State *L) {
  const char *source = luaL_optstring(L, 2, NULL);
  const char *target = luaL_checkstring(L, 3);
  const char *fstype = luaL_optstring(L, 4, NULL);
  int mntflags = luaL_checkinteger(L, 5);
  const char *data = luaL_optstring(L, 6, NULL);

  if (mount(source, target, fstype, mntflags, data) != 0)
    return push_luaerror(L);

  lua_pushboolean(L, 1);
  return 1;
}

#define ADDCONST(L, name)   \
  lua_pushinteger(L, name); \
  lua_setfield(L, -2, #name);

int luaopen_sysmount_mount(lua_State *L) {
  lua_newtable(L);

  luaL_newmetatable(L, MT);
  lua_pushcfunction(L, l_mount);
  lua_setfield(L, -2, "__call");
  lua_setmetatable(L, -2);

  ADDCONST(L, MS_DIRSYNC);
  ADDCONST(L, MS_RDONLY);
  ADDCONST(L, MS_NOSUID);
  ADDCONST(L, MS_NODEV);
  ADDCONST(L, MS_NOEXEC);
  ADDCONST(L, MS_SYNCHRONOUS);
  ADDCONST(L, MS_REMOUNT);
  ADDCONST(L, MS_MANDLOCK);
  ADDCONST(L, MS_DIRSYNC);
  ADDCONST(L, MS_NOATIME);
  ADDCONST(L, MS_NODIRATIME);
  ADDCONST(L, MS_BIND);
  ADDCONST(L, MS_MOVE);
  ADDCONST(L, MS_REC);
  ADDCONST(L, MS_SILENT);
  ADDCONST(L, MS_POSIXACL);
  ADDCONST(L, MS_UNBINDABLE);
  ADDCONST(L, MS_PRIVATE);
  ADDCONST(L, MS_SLAVE);
  ADDCONST(L, MS_SHARED);
  ADDCONST(L, MS_RELATIME);
  ADDCONST(L, MS_KERNMOUNT);
  ADDCONST(L, MS_I_VERSION);
  ADDCONST(L, MS_STRICTATIME);
  ADDCONST(L, MS_LAZYTIME);

  return 1;
}
