import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Read in an image and grayscale it
image = mpimg.imread('yellowlane.jpg')
thresh=(180,255)
gray=cv2.cvtColor(image,cv2.COLOR_RGB2GRAY)
binary=np.zeros_like(gray)  # 720x1280 x1 channel
binary[(gray>=thresh[0]) & (gray<=thresh[1])]=1

# RGB color space
R,G,B=image[:,:,0],image[:,:,1],image[:,:,2] # B-chanel not good for yellow lane
thresh_R=(200,255)
r_binary=np.zeros_like(R)
r_binary[(R>thresh_R[0]) & (R<thresh_R[1])]=1

# HSV color space
hsv=cv2.cvtColor(image,cv2.COLOR_RGB2HSV)
H,S,V=hsv[:,:,0],hsv[:,:,1],hsv[:,:,2] # B-chanel not good for yellow lane
thresh_S=(90,255)
S_binary=np.zeros_like(S)
S_binary[(S>thresh_S[0]) & (S<thresh_S[1])]=1

plt.imshow(S_binary)
plt.show()