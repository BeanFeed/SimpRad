# ----------------------------
# Makefile Options
# ----------------------------

NAME = SIMPRAD
ICON = icon.png
DESCRIPTION = "Simplify Radicals"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
