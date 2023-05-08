function [A,ho] = single_compute(cali1, cali2, cali3, test, gamma, ls, fc)

fs = 48000;

%% Crop Raw Signal

x = cali1(:,1);
x_low = cali1(:,2);
y1 = cali2(:,1);
y1_low = cali2(:,2);
y2 = cali3(:,1);
y2_low = cali3(:,2);

% [cali1(:,1),~] = WienerNoiseReduction(cali1(:,1),fs,5000);
% [cali2(:,1),~] = WienerNoiseReduction(cali2(:,1),fs,5000);
% [cali3(:,1),~] = WienerNoiseReduction(cali3(:,1),fs,5000);
% for i = 1:size(test,2)
%     [test(:,i),~] = WienerNoiseReduction(test(:,i),fs,5000);
% end

%% Estimate source reflection Hs and attenuation Hc
N = length(x);
X = fft(x,N);
Y1 = fft(y1,N);
Y2 = fft(y2,N);

H1 = (conj(X).*Y1)./(abs(X).^2+gamma);
H2 = (conj(X).*Y2)./(abs(X).^2+gamma);
h1 = real(ifft(H1));
h2 = real(ifft(H2));
h1 = fftshift(mLowpass(fftshift(h1),fc,fs));
h2 = fftshift(mLowpass(fftshift(h2),fc,fs));

head = round((1*ls-10)*2/34600*fs)+1;
tail = round((2*ls-10)*2/34600*fs);
delta = mFindDelay(h1(head:tail),-h2(head:tail));

% gain = abs(fft(-h2(head+1*delta:tail+1*delta)))./abs(fft(h1(head:tail)));
% gain(1:2) = 1; 
% gain(end) = 1;
% gain(24:end-22) = 1;
% gain = smooth(gain,3);
% gain = interp1(1:length(gain), gain, (1:N)/N*length(gain), 'spline');

D = exp(-2i*pi*(1:N)'/N*delta);
num = (Y1+Y2.*D).*X-Y1.*Y2.*(1+D);
den = (Y1-Y2).*D.*X;
% Hc = (conj(den).*num)./(abs(den).^2+gamma);
Hc = num./den;
num = Y1.*D+Y2-X.*(1+D);
den = (Y1-Y2).*D;
% HcHs = (conj(den).*num)./(abs(den).^2+gamma);
HcHs = num./den;

hc = real(ifft(Hc));
hchs = real(ifft(HcHs));

%% Object Reconstruction
head = N/2+round((-10)*2/34600*fs)+1;
tail = N/2+round((60)*2/34600*fs);

ho_list = zeros(tail-head+1,size(test,2));
A_list = zeros(tail-head+1,size(test,2));

for m = 1:size(test,2)
    y = test(:,m);
    Y = fft(y,N);
    num = Y-X;
    den = X.*Hc+Y.*HcHs;
%     num = Y;
%     den = X;
    Ho = (conj(den).*num)./(abs(den).^2+gamma);
    ho = real(ifft(Ho));
%     ho(1:100) = 0;
%     ho(end-99:end) = 0;
    
    ho = fftshift(mLowpass(fftshift(ho),fc,fs));

    ho = fftshift(ho);
%     hh = ho(N/2-667:N/2+667);
%     [ho,~] = WienerNoiseReduction(ho,fs,8000);
%     hh = ho;
    
    ho = ho(head:tail);
%     ho = ho - 0.0025;
    ho = ho-mean(ho(1:1+20));
    
    ho_list(:,m) = ho;

    A0 = 1.2; %cm^2
    A = inverse(1,ho,A0);
    A_list(:,m) = A;

end
ho = ho_list;
A = A_list;

end
