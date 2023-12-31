CC=gcc
TEST_DIRS = $(shell find ** -type d -name "tests")
TEST_FILES = $(foreach dir, $(TEST_DIRS), $(shell find $(dir) ! -name ".*" -type f -name "*.c"))

ENTRY_POINTS = compiler/clasp.c
DEP_EXCLUDES = $(foreach file,$(ENTRY_POINTS),$(notdir $(file))) basic.c $(foreach file,$(TEST_FILES),$(notdir $(file)))

LIB_DIR =     lib/
DEPS = $(shell cd $(LIB_DIR) && find .. -type f -name "*.c" ! -name ".*" $(foreach entry,$(DEP_EXCLUDES),! -name $(entry)))

default:
	@echo "Make target 'test' or 'build'"
	@echo "Current line count: $$(find ./** -type f \( -name "*.c" -o -name "*.h" \) -exec cat {} \; | wc -l)"

LIBS=$(shell cd $(LIB_DIR) && find  . -type f -name "*.o")
LIB_ARGS=-L$(LIB_DIR) $(foreach lib,$(LIBS), -l:$(notdir $(lib)))

build: build_deps
	@$(foreach file, $(ENTRY_POINTS), \
	$(CC) -o build/$(basename $(notdir $(file))) $(file) $(LIB_ARGS); )

test: build_deps
	@$(foreach file, $(TEST_FILES), \
	$(CC) -g -o build/test/$(basename $(notdir $(file))) $(file) $(LIB_ARGS); )

	@$(foreach file, $(TEST_FILES), \
	echo "Running test $(file)"; \
	build/test/$(basename $(notdir $(file))); \
	)

build_deps: rm_deps
	@cd $(LIB_DIR) && $(CC) -c $(DEPS)

rm_deps:
	@cd $(LIB_DIR) $(foreach lib, $(LIBS), && rm $(lib))