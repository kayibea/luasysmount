package = "luasysmount"
version = "dev-1"
source = {
  url = "git+ssh://git@github.com/kayibea/luasysmount.git"
}
description = {
  detailed = "Lua bindings for Linux mount-related syscalls and constants from `<sys/mount.h>`.",
  homepage = "*** please enter a project homepage ***",
  license = "*** please specify a license ***"
}
build = {
  type = "builtin",
  modules = {
    sysmount = "sysmount.c"
  }
}
