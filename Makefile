TARGET := hlist_test

all: $(TARGET)

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

#DEPS := $(patsubst %.o,%.d,$(OBJS))
#
#MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
#
#MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.c,$(MISSING_DEPS)))

C_FLAGS := -Wall -g

INC_FLAGS :=

LD_FLAGS :=

%.o : %.c
	gcc $(C_FLAGS) -o $@ -g -c $< $(INC_FLAGS)

$(TARGET) : $(OBJS)
	gcc -o $@ $^ $(LD_FLAGS)

.PHONY: clean

clean:
	-@rm $(OBJS) $(TARGET) $(DEPS)

