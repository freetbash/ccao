



g++ \
  apps/classes/source/*.cpp \
  apps/public/source/*.cpp \
  apps/tools/source/*.cpp \
  ccao/source/*.cpp \
   -I./apps/classes/headers \
   -I./apps/public/headers \
   -I./apps/tools/headers \
   -I./ccao/headers \
   -o ./bin/ccao -static -std=c++11

