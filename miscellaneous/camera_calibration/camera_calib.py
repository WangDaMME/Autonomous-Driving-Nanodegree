import cv2
import numpy as np
import glob
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import pickle

'''
# find internal corners of the chessbarods & draw corners on the images
#Read in and make a list of calibration Imags
images=glob.glob('./calibration_wide/GOPR00**.jpg')  # consistent file names
#plt.imshow(img)
#plt.show()

objpoints=[] # 3d points in real world space
imgpoints=[] # 2d points in image plane
objp=np.zeros((6*8,3),np.float32)  # 48*3column
objp[:,:2]=np.mgrid[0:8,0:6].T.reshape(-1,2)


# find internal corners of the chessbarods & draw corners on the images
for fname in images:
    img=mpimg.imread(fname)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #print(gray[::-1])
    ret, corners = cv2.findChessboardCorners(gray, (8, 6), None)
    if ret==True:
        imgpoints.append(corners)
        objpoints.append(objp)

        img=cv2.drawChessboardCorners(img,(8,6),corners,ret)
        plt.imshow(img)
        plt.show()

'''

# Camera Calibration & Undistort the Test Image


# Read in the saved objpoints and imgpoints
import os
dist_pickle = pickle.load( open( "./calibration_wide/wide_dist_pickle.p", "rb" ) )
objpoints = dist_pickle["objpoints"]
imgpoints = dist_pickle["imgpoints"]

# Read in an image
img = mpimg.imread('./calibration_wide/test_image.jpg')
plt.imshow(img)
plt.show()




# TODO: Write a function that takes an image, object points, and image points
# performs the camera calibration, image distortion correction and
# returns the undistorted image
def cal_undistort(img, objpoints, imgpoints):
    # Use cv2.calibrateCamera() and cv2.undistort()
    undist = np.copy(img)  # Delete this line
    #gray=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret,mtx,dist,rvecs,tvecs=cv2.calibrateCamera(objpoints,imgpoints,img.shape[1:],None,None)
    undist=cv2.undistort(img,mtx,dist,None,mtx)
    return undist

undistorted = cal_undistort(img, objpoints, imgpoints)

'''
f, (ax1, ax2) = plt.subplots(1, 2, figsize=(24, 9))
f.tight_layout()
ax1.imshow(img)
ax1.set_title('Original Image', fontsize=50)
ax2.imshow(undistorted)
ax2.show()
ax2.set_title('Undistorted Image', fontsize=50)
plt.subplots_adjust(left=0., right=1, top=0.9, bottom=0.)
'''

plt.imshow(undistorted)
plt.show()
