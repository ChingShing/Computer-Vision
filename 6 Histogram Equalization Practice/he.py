#coding=utf-8
# he.py
# 5140219126
# Apply Histogram Equalization (HE) algorithm to
# process the attached under-exposed image as input image data
# to make it visually easier for human recognition

import cv2
import numpy as np
from matplotlib import pyplot as plt
import os

source = os.getcwd()
target = os.getcwd()
listpic_black = os.listdir(source)

#for picname in listpic_black:
fullpicname = os.path.join(source, 'underexposed.png')

# Load an color image in grayscale
image = cv2.imread(fullpicname, 0)

lut = np.zeros(256, dtype = image.dtype )#创建空的查找表
hist= cv2.calcHist([image], #计算图像的直方图
                   [0], #使用的通道
                   None, #没有使用mask
                   [256], #it is a 1D histogram
                   [0.0,255.0])

minBinNo, maxBinNo = 0, 255

#计算从左起第一个不为0的直方图柱的位置
for binNo, binValue in enumerate(hist):
    if binValue != 0:
        minBinNo = binNo
        break
#计算从右起第一个不为0的直方图柱的位置
for binNo, binValue in enumerate(reversed(hist)):
    if binValue != 0:
        maxBinNo = 255-binNo
        break

#生成查找表
for i,v in enumerate(lut):
    #  print i
    if i < minBinNo:
        lut[i] = 0.0
    elif i > maxBinNo:
        lut[i] = 255.0
    else:
        lut[i] = int(255.0*(i-minBinNo)/(maxBinNo-minBinNo)+0.5)

#计算
result = cv2.LUT(image, lut)

# Show the image's histogram
fig = plt.figure()
fig.add_subplot(211)
plt.hist(image.ravel(),256,[0,256])
plt.xlim((0,256))
plt.ylabel('Pixel Number')
plt.title(r'Histogram of Input Image(upper) and Output Image(lower)')

# Show the result's histogram
fig.add_subplot(212)
plt.hist(result.ravel(),256,[0,256])
plt.xlim((0,256))
plt.ylabel('Pixel Number')
plt.xlabel('Grayscale')
plt.show()

if os.path.exists(target)==0:
    os.mkdir(target)
newpicname=os.path.join(target,'exposed.png')
cv2.imwrite(newpicname, result)