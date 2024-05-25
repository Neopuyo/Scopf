NAME := scop
CMDE := cmake
DEBUG_OPT := -DRUN_TESTS=ON
BUILD := build

# .obj
OBJECT_0 := 42
OBJECT_1 := teapot
OBJECT_2 := cube
OBJECT_3 := pyramid
OBJECT_4 := teapot2
OBJECT_5 := lego
OBJECT_SKULL := skull

#.bmp
TEXTURE_0 := poney
TEXTURE_1 := unikitty
TEXTURE_2 := uvtemplate
TEXTURE_SKULL := skull

.PHONY: all fclean clean build run run0 run1 run2 run3 run4 run5 run6 run7 run8 run9 run10 re print code debug

all: $(NAME)

$(NAME):
	$(MAKE) build
	$(MAKE) run

build:
	@if [ -d $(BUILD) ]; then \
		$(MAKE) -C ./$(BUILD); \
	else \
		$(CMDE) -S . -B $(BUILD); \
		$(CMDE) --build $(BUILD); \
	fi

debug:
	$(CMDE) $(DEBUG_OPT) -S . -B $(BUILD)
	$(MAKE) all

clean:
	@if [ -d $(BUILD) ]; then \
		$(CMDE) --build $(BUILD) --target clean; \
	fi

fclean:
	$(MAKE) clean
	@if [ -d $(BUILD) ]; then \
		rm -rf $(BUILD); \
	fi

re:
	$(MAKE) fclean
	$(MAKE) all

run run0 run1:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_0) $(TEXTURE_0)

run2:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_1) $(TEXTURE_1)

run3:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_2) $(TEXTURE_2)

run4:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_3) $(TEXTURE_1)

run5:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_4) $(TEXTURE_0)

run6:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_5) $(TEXTURE_1)

run7:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_SKULL) $(TEXTURE_SKULL)

code:
	code .

############################################

print:
	@echo "NAME = $(NAME)"
	@echo "MAKE = $(MAKE)"
	@echo "CMDE = $(CMDE)"
	@echo "BUILD = $(BUILD)"