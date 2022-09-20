md .bin\x32
md .bin\x64-Lua51
md .bin\x64-Lua53
md .bin\x64-Lua54

copy .Build\Win32\Release\*.dll .bin\x32
copy .Build\x64\Release\*.dll .bin\x64-Lua51
copy .Build\x64\Release-Lua53\*.dll .bin\x64-Lua53
copy .Build\x64\Release-Lua54\*.dll .bin\x64-Lua54

del /Q simple-lua-c-dll.zip

"C:\Program Files\7-Zip\7z.exe" a -r -tZip simple-lua-c-dll.zip .bin\*.dll src\*.cpp src\*.h contrib\*.lib lua-sample\*.lua src\*.def luacdll.vcxproj luacdll.vcxproj.filters README.md 

rd /S /Q .bin