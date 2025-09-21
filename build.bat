@echo off
set compiler=C:\dev\tooling\zig-x86_64-windows-0.14.1\zig.exe cc
set debug_options= -std=c99 -g -Wall -Wextra -pedantic -Wshadow
:: set debug_options= -std=c99 -g -Wall -Wextra -pedantic -Wshadow -Werror -fPIC -fPIE
set release_options= -std=c99 -O2 -fPIC -fPIE
if not exist build mkdir build
call %compiler% .\src\dirfiles.c -o .\build\dirfiles.exe %debug_options%
:: call %compiler% .\src\dirfiles.c -o .\build\dirfiles.exe %release_options%