NAME := scop
CMDE := cmake
BUILD := build

# will be filtered [a-z][A-Z][0-9][_] only
# full path will and extension is handle by program
# .obj
OBJECT_0 := 42
OBJECT_1 := teapot
OBJECT_2 := cube
OBJECT_3 := pyramid
OBJECT_4 := teapot2

#.bmp
TEXTURE_0 := poney
TEXTURE_1 := unikitty
TEXTURE_2 := uvtemplate


.PHONY: all fclean clean build run run2 run3 run4 run5 re print

all: $(NAME)

$(NAME):
	$(MAKE) build
	$(MAKE) run

build:
	$(CMDE) -S . -B $(BUILD)
	$(CMDE) --build $(BUILD)

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

run:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_0) $(TEXTURE_0)

run2:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_1) $(TEXTURE_1)

run3:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_2) $(TEXTURE_2)

run4:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_3) $(TEXTURE_0)

run5:
	cd ./$(BUILD) && ./$(NAME) $(OBJECT_4) $(TEXTURE_1)

############################################

print:
	@echo "NAME = $(NAME)"
	@echo "MAKE = $(MAKE)"
	@echo "CMDE = $(CMDE)"
	@echo "BUILD = $(BUILD)"