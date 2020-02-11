import pickle
import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg


# Read in the saved camera matrix and distortion coefficients
# These are the arrays you calculated using cv2.calibrateCamera()
dist_pickle = pickle.load( open( "./calibration_wide/wide_dist_pickle2.p", "rb" ) )
mtx = dist_pickle["mtx"]
dist = dist_pickle["dist"]

# Read in an image
img = cv2.imread('./calibration_wide/test_image2.png')
nx = 8 # the number of inside corners in x
ny = 6 # the number of inside corners in y



# MODIFY THIS FUNCTION TO GENERATE OUTPUT
def corners_unwarp(img, nx, ny, mtx, dist):
    # Pass in your image into this function
    # Write code to do the following steps
    # 1) Undistort using mtx and dist
    undist=cv2.undistort(img,mtx,dist,None,mtx)
    # 2) Convert to grayscale
    gray = cv2.cvtColor(undist, cv2.COLOR_BGR2GRAY)
    # 3) Find the chessboard corners
    ret, corners=cv2.findChessboardCorners(gray,(nx,ny),None)

    # 4) If corners found:
    if ret ==True:
        # a) draw corners
        cv2.drawChessboardCorners(undist,(nx,ny),corners,ret)
        #plt.imshow(undist)
        #plt.show()
        # b) define 4 source points src = np.float32([[,],[,],[,],[,]])
        img_size=(gray.shape[1],gray.shape[0])

        # For Source points, Grab the outer 4 detected corners
        src=np.float32([corners[0],corners[nx-1],corners[-1],corners[-nx]])  # 0, nx-1: 2 horizontal, # -1: last one -nx:3rd one

        # c) define 4 destination points dst = np.float32([[,],[,],[,],[,]])
        offset=100
        # For Destination points, arbitrarily choosing some points to be
        # a nice fit for displaying our warped result
        # again, not exact, but close enough for our purposes
        dst = np.float32([[offset, offset], [img_size[0] - offset, offset],
                          [img_size[0] - offset, img_size[1] - offset],
                          [offset, img_size[1] - offset]])

        # d) use cv2.getPerspectiveTransform() to get M, the transform matrix
        M=cv2.getPerspectiveTransform(src,dst)
        # e) use cv2.warpPerspective() to warp your image to a top-down view
        warped=cv2.warpPerspective(undist,M,img_size)

    # Return the result images and Matrix
    return warped, M


warped_image,M=corners_unwarp(img, nx, ny, mtx, dist)
plt.imshow(warped_image)
plt.show()
#print(M)