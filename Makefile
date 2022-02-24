all:
	ls images_input > images_list.txt
	python3 process_image_input.py
	g++ main.cpp
	./a.out
	rm a.out
	rm images_list.txt
	python3 make_images_output.py
