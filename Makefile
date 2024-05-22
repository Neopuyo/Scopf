NAME := scop

.PHONY: all clean run re print

all: $(NAME)


$(NAME):
	cmake -S . -B build
	cmake --build build
	$(MAKE) run

clean:
	cmake --build build --target clean

run:
	cd ./build && ./scop



############################################

print:
	@echo "NAME = $(NAME)"
	@echo "MAKE = $(MAKE)"