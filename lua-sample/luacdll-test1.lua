package.cpath =  package.cpath .. ";" .. getWorkingFolder() .. "\\lib5" .. _VERSION:sub(_VERSION:len()) .. "\\?.dll"

luacdll = require("luacdll")

OutText = ""

OutText = OutText .. "GetCurrentThreadId() = " .. tostring(luacdll.GetCurrentThreadId()) .. "\n"

r = luacdll.MultTwoNumbers(5.6, 2.17)
OutText = OutText .. "MultTwoNumbers(5.6, 2.17) = " .. tostring(r) .. "\n"

r = luacdll.MultAllNumbers(6, 3, "23423", {2.17}, 1.1)
OutText = OutText .. 'MultAllNumbers(6, 3, "23423", {2.17}, 1.1) = ' .. tostring(r) .. "\n"

message (OutText, 1)
