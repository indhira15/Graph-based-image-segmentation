import cv2
import numpy
import matplotlib.pyplot as plt

# n_img = "data/image/input.png"
n_img = "images_input/input.png"

print("Enter name of photo (has to be inside images_input file): ")
print("if empty, default will be input.png")
photo_name = input()
if photo_name != "":
	n_img = "images_input/" + photo_name

print("Process ", n_img)


img = cv2.imread(n_img);
img = cv2.cvtColor(img, cv2.BORDER_DEFAULT)
img = cv2.GaussianBlur(img, (5,5),0.8)
cv2.imwrite('images_input/gray_input.png', img)

altura  = img.shape[0]
ancho = img.shape[1]
img = cv2.imread("images_input/gray_input.png")


altura  = img.shape[0]
ancho = img.shape[1]

f = open("images_files/test.in", 'w')
f.write(str(altura))
f.write(" ")
f.write(str(ancho) + "\n")

for i in range(altura):
  for j in range(ancho):
  	f.write(str(img[i][j][0]));
  	f.write(" ")
  f.write('\n')

f.close()
