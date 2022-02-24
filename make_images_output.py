import cv2
import numpy as np
import matplotlib.pyplot as plt
import os


path_temporal = "images_temporal"
path_output = "images_output"


photo_list = os.listdir(path_temporal)
for image in photo_list:
	if image[-1] == 't':
		f = open( path_temporal + "/" + image, 'r')
		# leer parametros
		altura = 0
		ancho = 0
		n_clusteres = 0
		if f.mode == 'r':
			line = f.readline()
			a, b, c = line.split()
			altura  = int(a)
			ancho = int(b)
			n_clusteres = int(c);

		# crear los colores random
		dicc = {}
		for i in range(n_clusteres+1):
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

		cv2.imwrite(path_output + "/" + image[:-4] + '.png', img)
