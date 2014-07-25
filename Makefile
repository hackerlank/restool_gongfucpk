TARGET := test

SRCS :=	 $(wildcard src/*.cpp) \
		 $(wildcard src/*/*.cpp) \
		 $(wildcard src/*/*/*.cpp) \
		 $(wildcard src/*/*/*/*.cpp) \
		 $(wildcard src/*/*/*/*/*.cpp)

OBJS := $(SRCS:%.cpp=obj/%.o)

all:$(OBJS)
	@echo [M]Link...
	g++ $(OBJS) -o bin/$(TARGET)


obj/%.o:%.cpp
	@echo [M]Compile...
	@mkdir -p $(@D)
	g++ -c $< -o $@

run:
	./bin/$(TARGET)

clean:
	rm -rf bin/*
	rm -rf obj/*















