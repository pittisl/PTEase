function output = align_dense(x_raw, x_ref, name)
    fs = 48000;
    output = zeros(length(x_ref),25);
    x_raw = [zeros(0.15*fs,1); x_raw];
    [~,locs] = findpeaks(x_raw,"MinPeakDistance",0.15*fs,"MinPeakHeight",0.25);
    if isempty(locs)
        output = []; return;
    end
    x = x_raw(locs(1)-0.15*fs+1:locs(1)+0.2*fs);
    d = mFindDelay(x_ref,x);
    if length(x_raw) > 10*fs
        num = 50;
    else
        num = 25;
    end
    for i = 0:num-1
        if round(locs(1)+(i*0.2-0.15)*fs+length(x_ref)+d) > length(x_raw)
            break;
        elseif round(locs(1)+(i*0.2-0.15)*fs+1+d) < 1
            continue;
        end
        x = x_raw(round(locs(1)+(i*0.2-0.15)*fs+1+d) : round(locs(1)+(i*0.2-0.15)*fs+length(x_ref)+d));
        output(:,i+1) = x;
    end
end
