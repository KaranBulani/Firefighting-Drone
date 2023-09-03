from imutils import paths
import numpy as np
import argparse
import imutils
import cv2
import os, re, os.path

def cap_key_frames(videofile, x):
    mypath = "key_frames"
    for root, dirs, files in os.walk(mypath):
        for file in files:
            os.remove(os.path.join(root, file))
            
    print("Folder cleared")
    vid_cap = cv2.VideoCapture(videofile)
    sift = cv2.xfeatures2d.SIFT_create()

    success, last = vid_cap.read()
    cv2.imwrite('key_frames/frame0.jpg', last)
    print("Captured frame0.jpg")
    count = 1
    frame_num = 1

    w = int(last.shape[1] * 2 / 3)
    stride = x         
    min_match_num = 50 
    max_match_num = 800

    while success:
        if count % stride == 0:
            kp1, des1 = sift.detectAndCompute(last[:, -w:], None)
            kp2, des2 = sift.detectAndCompute(image[:, :w], None)

            bf = cv2.BFMatcher(normType=cv2.NORM_L2) 
            matches = bf.knnMatch(des1, des2, k=2)

            match_ratio = 0.6

            valid_matches = []
            for m1, m2 in matches:
                if m1.distance < match_ratio * m2.distance:
                    valid_matches.append(m1)

            if len(valid_matches) > 4:
                img1_pts = []
                img2_pts = []
                for match in valid_matches:
                    img1_pts.append(kp1[match.queryIdx].pt)
                    img2_pts.append(kp2[match.trainIdx].pt)

                img1_pts = np.float32(img1_pts).reshape(-1, 1, 2)
                img2_pts = np.float32(img2_pts).reshape(-1, 1, 2)

                _, mask = cv2.findHomography(img1_pts, img2_pts,
                                             cv2.RANSAC, 5.0)

                if min_match_num < np.count_nonzero(mask) < max_match_num:
                    last = image
                    print("Captured frame{}.jpg".format(frame_num))
                    cv2.imwrite('key_frames/frame%d.jpg' % frame_num, last)
                    frame_num += 1
        success, image = vid_cap.read()
        count += 1

def generate_panorama():
        print("[INFO] loading images...")
        imagePaths = sorted(list(paths.list_images("key_frames")))
        images = []

        for imagePath in imagePaths:
                image = cv2.imread(imagePath)
                images.append(image)

        print("[INFO] stitching images...")
        stitcher = cv2.createStitcher() if imutils.is_cv3() else cv2.Stitcher_create()
        (status, stitched) = stitcher.stitch(images)
        print("[INFO] cropping...")
        stitched = cv2.copyMakeBorder(stitched, 5, 5, 5, 5,
        cv2.BORDER_CONSTANT, (0, 0, 0))
        cv2.imwrite('panoramic_test.jpg', stitched)
        if status != 0:
            print("[INFO] image stitching failed ({})".format(status))

if __name__ == "__main__":
    x = 30
    videofile  = 't1.mp4'
    cap_key_frames(videofile, x)
    imagePaths = sorted(list(paths.list_images("key_frames")))
    j = len(imagePaths)
    print(j)
    while(j>12 or j<7):
        if j > 9:
            if j >= 30:
                x = x + 35 
            elif j < 30 and j >= 20:
                x = x + 20
            elif j < 20 and j >= 15:
                x = x + 10
            elif j < 15 and j > 12:
                x = x + 5
            print(x)
            cap_key_frames(videofile, x)
            imagePaths = sorted(list(paths.list_images("key_frames")))
            j = len(imagePaths)
            print(j)
        elif j < 7 :
            x = x-5
            print(x)
            cap_key_frames(videofile, x)
            imagePaths = sorted(list(paths.list_images("key_frames")))
            j = len(imagePaths)
            print(j)
    generate_panorama()
