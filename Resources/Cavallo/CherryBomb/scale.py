# scale up bitmap by nearest neighbor
import os
import cv2
filename = "Cherry.bmp"
img = cv2.imread(filename, cv2.IMREAD_UNCHANGED)
height, width = img.shape[:2]
res = cv2.resize(img, (24, 24), interpolation=cv2.INTER_NEAREST)
# let transparent pixels be white

cv2.imwrite(filename, res)
print('Scaled up ')
