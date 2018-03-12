.PHONY: all

SRCS_DIR    = exercises
BUILD_PATH  = build
RESULT_PATH = $(BUILD_PATH)/exercises.pdf
SRCS_FILES  = $(SRCS_DIR)/*.md
IMAGE_FILES = $(SRCS_DIR)/images/*

all: $(BUILD_PATH) $(RESULT_PATH)

$(BUILD_PATH):
	@mkdir -p build

$(RESULT_PATH): $(SRCS_FILES) $(SRCS_DIR)/*.tex
	@mkdir -p build
	@pandoc -s -N --reference-links \
		--filter pandoc-fignos \
		--filter pandoc-eqnos \
		--listings -H $(SRCS_DIR)/setup.tex \
		--latex-engine=xelatex \
		$(SRCS_FILES) \
		-o $@
	@echo Document generated in $@

