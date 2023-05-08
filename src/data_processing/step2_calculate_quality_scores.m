fs = 48000;
ls = 40;
gamma = 1e-3;
fc = 5700;

A_std = [2.6 2.7 2.8 3.0 3.7 4.8 4.7 3.9 3.0 2.4 1.9 1.7 ...
    1.9 2.5 3.2 3.4 3.6 4.0 3.4 2.7 2.4 2.6 2.9 3.15 ...
    3.1 3.0 3.1 3.5 4.0 4.7 5.5];
A_std = interp1(linspace(-5,25,31), ...
    A_std, linspace(-5,25,84), 'spline')';

load("res\quality_net_v2.mat");
improved_scores = [];
phone_id = '407a392cfec6ce93';
% phone_id = '1cd7522b746c7faa';
% phone_id = 'd0f28da57972bdb7';
folders = dir(['audiofiles', filesep, phone_id]);
for id = 1:length(folders)-3
    disp("No."+num2str(id));
    trials = dir([folders(id+2).folder, filesep, folders(id+2).name]);
    for i = 1:length(trials)-2
        disp("Trial_"+num2str(i));
        
        fileId = fopen([trials(i+2).folder, filesep, trials(i+2).name],'r');
        test_raw = fread(fileId,inf,'int16',0,'b');
        test_raw = test_raw / 2^15;
        
        if length(test_raw) < 42*fs
            if length(test_raw) < 6*5.9*fs+5.7*fs
                disp("BAD TRIAL");
                continue;
            end
            test.nasal = test_raw(1:round(5.7*fs));
            test.inhale1 = test_raw(round(1*5.9*fs+1):round(1*5.9*fs+5.7*fs));
            test.exhale1 = test_raw(round(2*5.9*fs+1):round(2*5.9*fs+5.7*fs));
            test.inhale2 = test_raw(round(3*5.9*fs+1):round(3*5.9*fs+5.7*fs));
            test.exhale2 = test_raw(round(4*5.9*fs+1):round(4*5.9*fs+5.7*fs));
            test.inhale3 = test_raw(round(5*5.9*fs+1):round(5*5.9*fs+5.7*fs));
            test.exhale3 = test_raw(round(6*5.9*fs+1):round(6*5.9*fs+5.7*fs));
        else
            if length(test_raw) < 5*5.9*fs+10.5*fs+5.7*fs
                disp("BAD TRIAL");
                continue;
            end
            test.nasal = test_raw(1:round(10.5*fs));
            test.inhale1 = test_raw(round(0*5.9*fs+10.5*fs+1):round(0*5.9*fs+10.5*fs+5.7*fs));
            test.exhale1 = test_raw(round(1*5.9*fs+10.5*fs+1):round(1*5.9*fs+10.5*fs+5.7*fs));
            test.inhale2 = test_raw(round(2*5.9*fs+10.5*fs+1):round(2*5.9*fs+10.5*fs+5.7*fs));
            test.exhale2 = test_raw(round(3*5.9*fs+10.5*fs+1):round(3*5.9*fs+10.5*fs+5.7*fs));
            test.inhale3 = test_raw(round(4*5.9*fs+10.5*fs+1):round(4*5.9*fs+10.5*fs+5.7*fs));
            test.exhale3 = test_raw(round(5*5.9*fs+10.5*fs+1):round(5*5.9*fs+10.5*fs+5.7*fs));
        end
        
        max_score = 0;
        calis = dir([folders(id+2).folder, filesep, 'cali_lib']);
        for j = max(1,id-19):id
            fileId = fopen([calis(j+2).folder, filesep, 'precali.pcm'],'r');
            cali1 = fread(fileId,inf,'int16',0,'b');
            cali1 = cali1 / 2^15;
            
            fileId = fopen([calis(j+2).folder, filesep, calis(j+2).name],'r');
            cali2 = fread(fileId,inf,'int16',0,'b');
            cali2 = cali2 / 2^15;
            
            cali3 = cali2(6*fs+1:11.5*fs);
            cali2 = cali2(1:5.5*fs);
            
            % [cali2, cali3] = ave_cali('audiofiles/cali_good/');
            
            [~,locs] = findpeaks(cali1,"MinPeakDistance",0.4*fs,"MinPeakHeight",0.1);
            x_ref = cali1(locs(1)-0.11*fs+1:locs(1)+0.19*fs);
            
%             color = {'#D0D0D0','#0072BD','#D95319','#0072BD','#D95319','#0072BD','#D95319'};
%             style = {'-','-','-','--','--','-.','-.'};
%             
            cali1 = align_ave(cali1, x_ref, calis(j+2).name);
            cali2 = align_ave(cali2, x_ref, calis(j+2).name);
            cali3 = align_ave(cali3, x_ref, calis(j+2).name);
            if isempty(cali1) || isempty(cali2) || isempty(cali3)
                disp("BAD CALI");
                continue;
            end
            field = fieldnames(test);
            score = [];
            cat = [];
            A_list = [];
            for k = 2:numel(field)
                test_aligned = align_dense(test.(field{k}), x_ref, 'test');            
                test_ref = trimmean(test_aligned,60,2);
                mse = mean((test_aligned - test_ref).^2,1);
                [~,idx_good] = mink(mse,20);
                [~,idx_bad] = maxk(mse,5);        
                test_aligned = mean(test_aligned(:,idx_good), 2);
                [A,~] = single_compute(cali1, cali2, cali3, test_aligned, gamma, ls, fc);
            %     plot(test.(field{k}),'Color',color{k},'LineStyle',style{k},'LineWidth',1);
                A_list = [A_list A];
                x = A_std; 
                x = x-min(x(21:end));
                y = A(34:118); 
                y = y-min(y(21:end));
                w = gausswin(length(x)+10,4);
                w = w(1:end-10);
                
                [~,ix,iy] = dtw(x,y,10);
                x = x(ix); y = y(iy); w = w(ix);
                d = sum(abs(x-y).*w);
                d = min(110/(1+0.037*d),100);
                
                [~,pred] = max(predict(net,A(34:118)'));
                cat = [cat, pred];
                score = [score, d];
%                 if d > 80 && pred == 1
%                     plot((1:length(A))/fs*34300/2-10,A,'k','LineWidth',1);
%                     ylim([0 20]);
%                     plot((34:118)/fs*34300/2-10,A(34:118),'k','LineWidth',1); xlim([0 35]); ylim([0 20]);
%                     title("S="+num2str(d)+", C="+num2str(pred));
%                     drawnow
%                 end
            end
%             score = score/6;
            
            entry.id = id;
            entry.trial = i;
            entry.cali = j;
            entry.score = score;
            entry.category = cat;

            improved_scores = [improved_scores; entry];
            
%             if score > max_score
%                 max_score = score;
%                 max_A = A_list;
%             end
%             
%             if id == j
%                 ori_score = score;
%                 ori_A = A_list;
%             end

%             figure;
%             plot((1:length(A))/fs*34300/2-10,A_list,'k');
%             % legend("Nasal", "Inhale1", "Hold1", ...
%             %     "Exhale2", "Inhale2", "Hold2", "Exhale2")
%             xlim([0 40]);
%             ylim([0 10]);
%             xlabel("Distance (cm)");
%             ylabel("Cross-sectional Area (cm^2)");
%             grid on;
        end
        
%         figure;
%         plot((1:length(A))/fs*34300/2-10,ori_A,'k');
%         % legend("Nasal", "Inhale1", "Hold1", ...
%         %     "Exhale2", "Inhale2", "Hold2", "Exhale2")
%         xlim([0 40]);
%         ylim([0 10]);
%         xlabel("Distance (cm)");
%         ylabel("Cross-sectional Area (cm^2)");
%         grid on;
%         
%         figure;
%         plot((1:length(A))/fs*34300/2-10,max_A,'k');
%         % legend("Nasal", "Inhale1", "Hold1", ...
%         %     "Exhale2", "Inhale2", "Hold2", "Exhale2")
%         xlim([0 40]);
%         ylim([0 10]);
%         xlabel("Distance (cm)");
%         ylabel("Cross-sectional Area (cm^2)");
%         grid on;
    end
    fclose("all");
    
end

save('res\phone1_scores_v3.mat','improved_scores');
