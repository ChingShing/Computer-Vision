% Make 3 kinds of blur and output images
function blur(img,threshold,type)

    % Gaussian Blur
    % Reference: GaussianMatrix is from http://blog.csdn.net/google0802/article/details/14102127
    function res=GaussianBlur(paded_img,padding)
        function h=GaussianMatrix(pad,sigma)
        [x,y]=meshgrid(-pad:pad,-pad:pad);
        arg=-(x.*x+y.*y)/(2*sigma*sigma);
        h=exp(arg);
        h(h<eps*max(h(:)))=0;
        sumh=sum(h(:));
            if sumh~=0
              h=h/sumh;
            end
        end
        g=GaussianMatrix(padding,0.849);
        blur=paded_img;
        for row=padding+1:im_height+padding
            for col=padding+1:im_width+padding
                row_begin=row-padding;
                row_end=row+padding;
                col_begin=col-padding;
                col_end=col+padding;
                kernel=single(paded_img(row_begin:row_end,col_begin:col_end));
                blur(row,col)=sum(sum(g.*kernel));
            end
        end
        res=blur(padding+1:padding+im_height,padding+1:padding+im_width);
    end

      % Mean Blur
      function res=MeanBlur(padded_img,padding)
            blur=padded_img;
            for row=padding+1:im_height+padding
                for col=padding+1:im_width+padding
                    row_begin=row-padding;
                    row_end=row+padding;
                    col_begin=col-padding;
                    col_end=col+padding;
                    kernel=padded_img(row_begin:row_end,col_begin:col_end);
                    blur(row,col)=mean(mean(kernel));
                end
            end
            res=blur(padding+1:padding+im_height,padding+1:padding+im_width);
      end


    % Median Blur
    function res=MedianBlur(paded_img,padding)
        blur=paded_img;
        for row=padding+1:im_height+padding
            for col=padding+1:im_width+padding
                row_begin=row-padding;
                row_end=row+padding;
                col_begin=col-padding;
                col_end=col+padding;
                kernel=paded_img(row_begin:row_end,col_begin:col_end);
                blur(row,col)=median(median(kernel));
            end
        end
        res=blur(padding+1:padding+im_height,padding+1:padding+im_width);
    end

% Show the original picture
subplot(211);
imshow(img,[]);
title('input');
[im_height,im_width]=size(img);

% Get the pad size of the image
padding=(threshold-1)/2;
% Extent the image acolording to pad
padded_img=padarray(img,[padding padding],'replicate','both');

if type==0
    res=GaussianBlur(padded_img,padding);
    subplot(212);
    imshow(res,[]);
    title('Output: Gaussian Blur');
elseif type==1
    res=MeanBlur(padded_img,padding);
    subplot(212);
    imshow(res,[]);
    title('Output: Mean Blur');
elseif type==2
    res=MedianBlur(padded_img,padding);
    subplot(212);
    imshow(res,[]);
    title('Output: Median Blur');
end
end
