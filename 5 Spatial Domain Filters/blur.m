% Make 3 kinds of blur and output images
function blur(img,threshold,type)

    % Gaussian Blur
    % Reference: GaussianMatrix is from http://blog.csdn.net/google0802/article/details/14102127
    function res=GaussianBlur(paded_img,pad)
        function h=GaussMatrix(pad,sigma)
        [x,y]=meshgrid(-pad:pad,-pad:pad);
        arg=-(x.*x+y.*y)/(2*sigma*sigma);
        h=exp(arg);
        h(h<eps*max(h(:)))=0;
        sumh=sum(h(:));
            if sumh~=0
              h=h/sumh;
            end
        end
        g=GaussianMatrix(pad,0.849);
        blur=paded_img;
        for row=pad+1:im_height+pad
            for col=pad+1:im_width+pad
                row_begin=row-pad;
                row_end=row+pad;
                col_begin=col-pad;
                col_end=col+pad;
                kernel=single(paded_img(row_begin:row_end,col_begin:col_end));
                blur(row,col)=sum(sum(g.*kernel));
            end
        end
        res=blur(pad+1:pad+im_height,pad+1:pad+im_width);
    end

      % Mean Blur
      function res=MeanBlur(padded_img,pad)
            blur=padded_img;
            for row=pad+1:im_height+pad
                for col=pad+1:im_width+pad
                    row_begin=row-pad;
                    row_end=row+pad;
                    col_begin=col-pad;
                    col_end=col+pad;
                    kernel=padded_img(row_begin:row_end,col_begin:col_end);
                    blur(row,col)=mean(mean(kernel));
                end
            end
            res=blur(pad+1:pad+im_height,pad+1:pad+im_width);
      end


    % Median Blur
    function res=MedianBlur(paded_img,pad)
        blur=paded_img;
        for row=pad+1:im_height+pad
            for col=pad+1:im_width+pad
                row_begin=row-pad;
                row_end=row+pad;
                col_begin=col-pad;
                col_end=col+pad;
                kernel=paded_img(row_begin:row_end,col_begin:col_end);
                blur(row,col)=median(median(kernel));
            end
        end
        res=blur(pad+1:pad+im_height,pad+1:pad+im_width);
    end

% Show the original picture
subplot(211);
imshow(img,[]);
title('input');
[im_height,im_width]=size(img);

% Get the pad size of the image
pad=(threshold-1)/2;

% Extent the image acolording to pad
padded_img=padarray(img,[pad pad],'replicate');

if type==0
    res=GaussianBlur(padded_img,pad);
    subplot(212);
    imshow(res,[]);
    title('Output: Gaussian Blur');
elseif type==1
    res=MeanBlur(padded_img,pad);
    subplot(212);
    imshow(res,[]);
    title('Output: Mean Blur');
elseif type==2
    res=MedianBlur(padded_img,pad);
    subplot(212);
    imshow(res,[]);
    title('Output: Median Blur');
end
end
