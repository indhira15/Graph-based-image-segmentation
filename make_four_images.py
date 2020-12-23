import cv2
import numpy as np
import matplotlib.pyplot as plt

n_file1 = "images_files/seg_img_8_1.out"
n_file2 = "images_files/seg_img_8_2.out"
n_file3 = "images_files/seg_img_8_3.out"
n_file3 = "images_files/seg_img_8_4.out"


n_img1 = "images_output/seg_img_1.png"
n_img2 = "images_output/seg_img_2.png"
n_img3 = "images_output/seg_img_3.png"
n_img4 = "images_output/seg_img_4.png"


f = open(n_file1, 'r')
f2 = open(n_file2, 'r')
f3 = open(n_file3, 'r')
f4 = open(n_file3, 'r')

# leer parametros
altura = 0
ancho = 0
n_clusteres1 = 0
n_clusteres2 = 0
n_clusteres3 = 0
n_clusteres4 = 0

if f.mode == 'r':
	line = f.readline()
	a, b, c = line.split()
	altura  = int(a)
	ancho = int(b)
	n_clusteres1 = int(c);


if f2.mode == 'r':
	line = f2.readline()
	a, b, c = line.split()
	altura  = int(a)
	ancho = int(b)
	n_clusteres2 = int(c);

if f3.mode == 'r':
	line = f3.readline()
	a, b, c = line.split()
	altura  = int(a)
	ancho = int(b)
	n_clusteres3 = int(c);

if f4.mode == 'r':
	line = f4.readline()
	a, b, c = line.split()
	altura  = int(a)
	ancho = int(b)
	n_clusteres4 = int(c);

# crear los colores random

total_color = max(n_clusteres1, n_clusteres2, n_clusteres3, n_clusteres4)
dicc = {}
for i in range(total_color+1):
	dicc[i] = np.random.rand(3,)


img = np.empty((altura, ancho, 3))
a = ""
b = ""
c = ""




# Asignar los colores segun su cluster
if f.mode == 'r':
	for i in range(altura):
		for j in range(ancho):
			line = f.readline()
			img[i][j][0] = dicc[int(line)][0]
			img[i][j][1] = dicc[int(line)][1]
			img[i][j][2] = dicc[int(line)][2]

img *= 255.0
img = np.uint8(img)

f.close()
cv2.imwrite(n_img1, img)

img = np.empty((altura, ancho, 3))


# Asignar los colores segun su cluster
if f2.mode == 'r':
	for i in range(altura):
		for j in range(ancho):
			line = f2.readline()
			img[i][j][0] = dicc[int(line)][0]
			img[i][j][1] = dicc[int(line)][1]
			img[i][j][2] = dicc[int(line)][2]

img *= 255.0
img = np.uint8(img)

f2.close()

cv2.imwrite(n_img2, img)


img = np.empty((altura, ancho, 3))


# Asignar los colores segun su cluster
if f3.mode == 'r':
	for i in range(altura):
		for j in range(ancho):
			line = f3.readline()
			img[i][j][0] = dicc[int(line)][0]
			img[i][j][1] = dicc[int(line)][1]
			img[i][j][2] = dicc[int(line)][2]

img *= 255.0
img = np.uint8(img)

f3.close()

cv2.imwrite(n_img3, img)


img = np.empty((altura, ancho, 3))


# Asignar los colores segun su cluster
if f4.mode == 'r':
	for i in range(altura):
		for j in range(ancho):
			line = f4.readline()
			img[i][j][0] = dicc[int(line)][0]
			img[i][j][1] = dicc[int(line)][1]
			img[i][j][2] = dicc[int(line)][2]

img *= 255.0
img = np.uint8(img)

f3.close()

cv2.imwrite(n_img4, img)