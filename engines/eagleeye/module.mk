MODULE := engines/eagleeyecopy

MODULE_OBJS := \
	detection.o

# This module can be built as a plugin
ifeq ($(ENABLE_EAGLEEYE), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk