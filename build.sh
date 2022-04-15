



g++ \
  apps/classes/source/*.cpp \
  apps/public/source/*.cpp \
  apps/tools/source/*.cpp \
  ccao/source/*.cpp \
   -I./apps/classes/headers \
   -I./apps/public/headers \
   -I./apps/tools/headers \
   -I/home/bash/.ccao/stars/toml/0 \
   -I./ccao/headers \
   -L/home/bash/.ccao/stars/toml/0 \
   -ltoml \
   -o ./bin/ccao -static -std=c++11

