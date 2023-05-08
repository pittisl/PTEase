function output = align_ave(x_raw, x_ref, name)
    fs = 48000;
    output = zeros(length(x_ref),2);
    x_raw = [zeros(0.15*fs,1); x_raw];
    [~,locs] = findpeaks(x_raw,"MinPeakDistance",0.15*fs,"MinPeakHeight",0.1);
    if isempty(locs)
        output = []; return;
    end
    x = x_raw(locs(1)-0.15*fs+1:locs(1)+0.2*fs);
    d = mFindDelay(x_ref,x);
    for i = 1:11
        if round(locs(1)+(i*0.4+0.05)*fs+length(x_ref)+d) <= length(x_raw)
            x = x_raw(round(locs(1)+(i*0.4-0.15)*fs+1+d) : round(locs(1)+(i*0.4-0.15)*fs+length(x_ref)+d));
            x_low = x_raw(round(locs(1)+(i*0.4+0.05)*fs+1+d) : round(locs(1)+(i*0.4+0.05)*fs+length(x_ref)+d));
            output(:,1) = output(:,1) + x;
            output(:,2) = output(:,2) + x_low;
%             plot(x);hold on;
        else
            break;
        end
    end
%     hold off;
    output(:,1) = output(:,1) / (i+1);
    output(:,2) = output(:,2) / (i+1);
end
