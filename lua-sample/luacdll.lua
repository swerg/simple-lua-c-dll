require("luacdll")

message(tostring(luacdll.GetCurrentThreadId()), 1)

r = luacdll.MultTwoNumbers(5.6, 2.17)
message (tostring(r), 1)

r = luacdll.MultAllNumbers(6, 3, "23423", {2.17}, 1.1)
message (tostring(r), 1)