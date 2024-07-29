@RD /S /Q "build"

cmake -B build/sc2bot-x64-windows -G Ninja .
cd .\build\sc2bot-x64-windows\
ninja.exe

bin\Digamma.exe "D:\StarCraft II\Maps\Ladder2019Season3\AcropolisLE.SC2Map"