img=rgb2gray(imread('filters.png'));

threshold=11;

blur(img,threshold,0);
figure;

blur(img,threshold,1);
figure;

blur(img,threshold,2);
