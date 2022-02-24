import cv2
import numpy
import os
import shutil
import matplotlib.pyplot as plt


# Pre processing
## collect all the photo names
path_in = "images_input"
path_out = "images_output"
path_temporal = "images_temporal"
photo_list = os.listdir(path_in)

if os.path.isdir(path_out) == True:
	shutil.rmtree(path_out)

if os.path.isdir(path_temporal) == True:
	shutil.rmtree(path_temporal)

os.mkdir(path_out)
os.mkdir(path_temporal)

for p in photo_list:
	n_img = path_in + "/" + p
	print("Processing ", n_img)

	img = cv2.imread(n_img);
	img = cv2.cvtColor(img, cv2.BORDER_DEFAULT)
	img = cv2.GaussianBlur(img, (5,5),0.8)

	height  = img.shape[0]
	width = img.shape[1]
	f = open(path_temporal + "/" + p + ".in", "w")
	f.write(str(height) + " " + str(width) + "\n")

	for i in range(height):
	  for j in range(width):
	  	f.write(str(img[i][j][0]));
	  	f.write(" ")
	  f.write('\n')

	f.close()
