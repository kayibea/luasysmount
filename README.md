# luasysmount

Lua bindings for Linux mount-related syscalls and constants from `<sys/mount.h>`.

## Usage

```lua
local mnt = require "sysmount.mount"

-- Mount a tmpfs
local ok, err, errno = mnt("tmpfs", "/mnt/tmp", "tmpfs",
    mnt.MS_NOEXEC | mnt.MS_NOSUID, "")

if not ok then
    print("mount failed:", err, errno)
end
