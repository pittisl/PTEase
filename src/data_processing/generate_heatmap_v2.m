function [output, mask] = generate_heatmap_v2(input)

fs = 48000;
outlier_threshold = 0.15;
sigma = 1;

output = [];
upper_bound = [];
lower_bound = [];
% figure;
for i = 1:size(input,1)
%     hist = histcounts(input(i,:),0:0.1:10);
    hist = [];
    for j = 0:0.2:0.2
        hist = [hist; histcounts(input(i,:),j:0.4:19.2+j)];
    end
    hist = reshape(hist,[size(hist,1)*size(hist,2) 1])';
%     [~,idx] = findpeaks(hist);
%     if length(idx) >= 3
%         idx = [1:min(idx)-3 idx max(idx)+3:length(hist)];
%         hist = hist(idx);
%         hist = interp1(idx/20,hist,0.2:0.02:20);
%     else
%         hist = interp1((1:length(hist))/20,hist,0.2:0.02:20);
%     end
    if max(hist)~=0
        hist = hist/max(hist);
    end
%     hist = smooth(hist,10)';
    output = [output; hist];
end
output = (output > outlier_threshold).*output;
output = output';

% ksize = 2*ceil(2*sigma)+1;
% gauss_kernel = zeros(ksize,ksize);
% for n1 = 1:ksize
%     for n2 = 1:ksize
%         gauss_kernel(n1,n2) = exp(-((n1-(ksize+1)/2)^2+(n2-(ksize+1)/2)^2)/2/sigma^2)/(2*pi*sigma^2);
%     end
% end

% output = conv2(output',gauss_kernel);
% output = output((ksize+1)/2:end-(ksize-1)/2,(ksize+1)/2:end-(ksize-1)/2);

mask = zeros(size(output));
for i = 1:size(output,2)
    for n = 1:size(output,1)
        if sum(output(1:n,i)) > 0.2*sum(output(:,i))
            break;
        end
    end
    lower_bound = n;
    for n = length(hist):-1:1
        if sum(output(n:end,i)) > 0.2*sum(output(:,i))
            break;
        end
    end
    upper_bound = n;
    if lower_bound > upper_bound
        lower_bound = 1;
    end
    mask(lower_bound:upper_bound,i) = 1;
end


end

