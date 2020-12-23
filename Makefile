

all:
	python3 process_image_input.py
	g++ main.cpp
	./a.out
	python3 make_four_images.py
