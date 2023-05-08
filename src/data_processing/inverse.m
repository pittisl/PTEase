function A = inverse(Tx, Rx, A0)
%INVERSE is a function that solves the inverse problem of acoustic plane
%wave propagation in duct
%   Syntax: A=inverse(Rx) or A=inverse(Rx,A0) or A=inverse(Tx,Rx,A0)
%   Tx: Transmitted signal
%   Rx: Reflected signal
%   A: Cross-sectional area of duct, function of position
%   A0: Initial cross-sectional area of duct

if nargin < 3
    Tx = 1;
end
if nargin < 2
    A0 = 1;
end

if length(Tx) > length(Rx)
    error('Length of Tx should not be larger than length of Rx');
end

nsample = length(Rx);
x = zeros(nsample, nsample);
y = zeros(nsample, nsample);
r = zeros(1,nsample);

x(1:length(Tx),1) = Tx;
y(:,1) = Rx;

r(1) = -y(1,1)/x(1,1);
A = A0*ones(nsample,1);
for i = 2 : nsample
    for j = 1 : nsample-i+1
        x(j,i) = x(j,i-1)/(1-r(i-1)) + y(j,i-1)*r(i-1)/(1-r(i-1));
        y(j,i) = x(j+1,i-1)*r(i-1)/(1-r(i-1)) + y(j+1,i-1)/(1-r(i-1));
    end
    r(i) = -y(1,i)/x(1,i);
    if A(i-1) < 0.25
        A(i) = A(i-1);
    else
        A(i) = A(i-1)*(1+r(i))/(1-r(i));
    end
end
A(i+1:end) = A(i);

end

