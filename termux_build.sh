



aarch64-linux-gnu-g++ \
  apps/classes/source/*.cpp \
  apps/public/source/*.cpp \
  apps/tools/source/*.cpp \
  ccao/source/*.cpp \
  toml/source/*.cpp \
   -I./apps/classes/headers \
   -I./apps/public/headers \
   -I./apps/tools/headers \
   -I./toml/headers \
   -I./ccao/headers \
   -o ./bin/ccao_for_termux -static -std=c++11

