function d = myfinddelay(x,y)
%MYFINDDELAY Summary of this function goes here
%   Detailed explanation goes here
c = xcorr(y,x);
[m,i] = max(c);
while max(c(1:i-50)) > 0.6*m
    [m,i] = max(c(1:i-50));
end

d = i - max(length(x),length(y));

end

