%% Import spirometry data

load("res\id_map_v2.mat");
load("res\albuterol.mat")
% load("data.mat");
T = readtable('res\AWARE_DATA_LABELS_2022-12-09_1058.csv');
subject = table;
subject.covid = (T.PreviousCOVID19Diagnosis_=="Yes")+0;
subject.age = T.CalculatedAge_years__;
subject.sex = (T.Sex_=="Male")+0;
subject.height = T.Height_cm__;
subject.weight = T.Weight_kg__;

subject.fev1 = T.BaselineFEV1_liters__;
subject.fvc = T.BaselineFVC_liters__;
subject.ratio = T.BaselineFEV1_FVC_rawRatio__;
subject.fef2575 = T.BaselineFEF2575_liters__;
subject.fev1_pred = T.BaselineFEV1__pred__;
subject.fvc_pred = T.BaselineFVC__pred__;
subject.ratio_pred = T.BaselineFEV1_FVC__pred__;
subject.fef2575_pred = T.BaselineFEF2575__pred__;

subject.post_albuterol = (T.Post_bronchodilator_=="Yes")+0;
subject.post_fev1 = T.PostFEV1_liters__;
subject.post_fvc = T.PostFVC_liters__;
subject.post_ratio = T.PostFEV1_FVC_rawRatio__;
subject.post_fef2575 = T.PostFEF2575_liters__;
subject.post_fev1_pred = T.PostFEV1__pred__;
subject.post_fvc_pred = T.PostFVC__pred__;
subject.post_ratio_pred = T.PostFEV1_FVC__pred__;
subject.post_fef2575_pred = T.PostFEF2575__pred__;

subject.group = zeros(size(T,1),1);
for i = 1:size(T,1)
    if T.Participant_(i) == "Control / healthy / no pulmonary disease"
        subject.group(i) = 1;
    elseif T.Participant_(i) == "Asthma"
        subject.group(i) = 2;
    elseif T.Participant_(i) == "CF"
        subject.group(i) = 3;
    elseif T.Participant_(i) == "COPD"
        subject.group(i) = 4;
    else
        subject.group(i) = 5;
    end
end

% subject.label = zeros(size(T,1),1);
% for i = 1:size(T,1)
%     if isnan(subject.fev1_pred(i))
%         subject.label(i) = 0;
%     elseif subject.fev1_pred(i)>100
%         subject.label(i) = 1;
%     elseif subject.fev1_pred(i)>80
%         subject.label(i) = 2;
%     elseif subject.fev1_pred(i)>60
%         subject.label(i) = 3;
%     else
%         subject.label(i) = 4;
%     end
% end

%% Pick good curves

load('res\phone1_scores.mat');
s = 0;
n = 1;
t = 80;
best_inhale = [];
best_exhale = [];
id = 1;
trial = 1;
best_inhale_cali = [];
best_inhale_attempt = [];
best_inhale_score = 0;
best_exhale_cali = [];
best_exhale_attempt = [];
best_exhale_score = 0;
while n <= length(improved_scores)
    if improved_scores(n).id ~= id || improved_scores(n).trial ~= trial
        best_inhale(id,trial).cali = best_inhale_cali;
        best_inhale(id,trial).attempt = best_inhale_attempt;
        best_exhale(id,trial).cali = best_exhale_cali;
        best_exhale(id,trial).attempt = best_exhale_attempt;
        id = improved_scores(n).id;
        trial = improved_scores(n).trial;
        best_inhale_cali = [];
        best_inhale_attempt = [];
        best_inhale_score = 0;
        best_exhale_cali = [];
        best_exhale_attempt = [];
        best_exhale_score = 0;
    end
    scores = improved_scores(n).score;
    cat = improved_scores(n).category;
    for i = 1:2:5
        if cat(i)==2 && scores(i)>t && scores(i)>best_inhale_score
            best_inhale_cali = improved_scores(n).cali;
            best_inhale_attempt = i;
            best_inhale_score = scores(i);
        end
    end
    for i = 2:2:6
        if cat(i)==2 && scores(i)>t && scores(i)>best_exhale_score
            best_exhale_cali = improved_scores(n).cali;
            best_exhale_attempt = i;
            best_exhale_score = scores(i);
        end
    end
    n = n + 1;
end
best_inhale(id,trial).cali = best_inhale_cali;
best_inhale(id,trial).attempt = best_inhale_attempt;
best_exhale(id,trial).cali = best_exhale_cali;
best_exhale(id,trial).attempt = best_exhale_attempt;

%% Extract AWARE features

fs = 48000;
ls = 40;
gamma = 1e-3;
fc = 5000;

A_std = [2.6 2.7 2.8 3.0 3.7 4.8 4.7 3.9 3.0 2.4 1.9 1.7 ...
    1.9 2.5 3.2 3.4 3.6 4.0 3.4 2.7 2.4 2.6 2.9 3.15 ...
    3.1 3.0 3.1 3.5 4.0 4.7 5.5];
A_std = interp1(linspace(-5,25,31), ...
    A_std, linspace(-5,25,84), 'spline')';

%phone_id = '1cd7522b746c7faa';
phone_id = '407a392cfec6ce93';
folders = dir(['audiofiles', filesep, phone_id]);
inhale_data = [];
inhale_outcome = [];
inhale_verbose = [];
exhale_data = [];
exhale_outcome = [];
exhale_verbose = [];
for id = 1:length(folders)-3
    disp("No."+num2str(id));
    trials = dir([folders(id+2).folder, filesep, folders(id+2).name]);
    calis = dir([folders(id+2).folder, filesep, 'cali_lib']);
    
    aware_id(id) = str2num(folders(id+2).name);
    
    for trial = 1:5
        %% Extract features from INHALE
        if ~isempty(best_inhale(id,trial).cali)
            i = trial;
            j = best_inhale(id,trial).cali;
            k = best_inhale(id,trial).attempt;

            fileId = fopen([trials(i+2).folder, filesep, trials(i+2).name],'r');
            test_raw = fread(fileId,inf,'int16',0,'b');
            test_raw = test_raw / 2^15;

            fileId = fopen([calis(j+2).folder, filesep, 'precali.pcm'],'r');
            cali1 = fread(fileId,inf,'int16',0,'b');
            cali1 = cali1 / 2^15;

            fileId = fopen([calis(j+2).folder, filesep, calis(j+2).name],'r');
            cali2 = fread(fileId,inf,'int16',0,'b');
            cali2 = cali2 / 2^15;

            cali3 = cali2(6*fs+1:11.5*fs);
            cali2 = cali2(1:5.5*fs);

            fclose("all");

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

            [~,locs] = findpeaks(cali1,"MinPeakDistance",0.4*fs,"MinPeakHeight",0.1);
            x_ref = cali1(locs(1)-0.11*fs+1:locs(1)+0.19*fs);
            cali1 = align_ave(cali1, x_ref, 'cali1');
            cali2 = align_ave(cali2, x_ref, 'cali2');
            cali3 = align_ave(cali3, x_ref, 'cali3');

            field = fieldnames(test);
            test_aligned = align_dense(test.(field{k+1}), x_ref, 'test');
            [A,~] = single_compute(cali1, cali2, cali3, test_aligned, gamma, ls, fc);
            
            inhale_data = [inhale_data; reshape(A,1,[])];
            inhale_verbose = [inhale_verbose; ...
                [id_map(aware_id(id)), ...
                trial ...
                subject.age(id_map(aware_id(id))), ...
                subject.sex(id_map(aware_id(id))), ...
                subject.height(id_map(aware_id(id))), ...
                subject.weight(id_map(aware_id(id)))]];
            inhale_outcome = [inhale_outcome; ...
                [subject.group(id_map(aware_id(id))), ...
                subject.fev1(id_map(aware_id(id))), ...
                subject.ratio(id_map(aware_id(id))), ...
                subject.fef2575(id_map(aware_id(id))), ...
                subject.fev1_pred(id_map(aware_id(id))), ...
                subject.ratio_pred(id_map(aware_id(id))), ...
                subject.fef2575_pred(id_map(aware_id(id)))]];
        end
        
        %% Extract features from EXHALE
        if ~isempty(best_exhale(id,trial).cali)
            i = trial;
            j = best_exhale(id,trial).cali;
            k = best_exhale(id,trial).attempt;

            fileId = fopen([trials(i+2).folder, filesep, trials(i+2).name],'r');
            test_raw = fread(fileId,inf,'int16',0,'b');
            test_raw = test_raw / 2^15;

            fileId = fopen([calis(j+2).folder, filesep, 'precali.pcm'],'r');
            cali1 = fread(fileId,inf,'int16',0,'b');
            cali1 = cali1 / 2^15;

            fileId = fopen([calis(j+2).folder, filesep, calis(j+2).name],'r');
            cali2 = fread(fileId,inf,'int16',0,'b');
            cali2 = cali2 / 2^15;

            cali3 = cali2(6*fs+1:11.5*fs);
            cali2 = cali2(1:5.5*fs);

            fclose("all");

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

            [~,locs] = findpeaks(cali1,"MinPeakDistance",0.4*fs,"MinPeakHeight",0.1);
            x_ref = cali1(locs(1)-0.11*fs+1:locs(1)+0.19*fs);
            cali1 = align_ave(cali1, x_ref, 'cali1');
            cali2 = align_ave(cali2, x_ref, 'cali2');
            cali3 = align_ave(cali3, x_ref, 'cali3');

            field = fieldnames(test);
            test_aligned = align_dense(test.(field{k+1}), x_ref, 'test');            
            [A,~] = single_compute(cali1, cali2, cali3, test_aligned, gamma, ls, fc);
            
            exhale_data = [exhale_data; reshape(A,1,[])];
            exhale_verbose = [exhale_verbose; ...
                [id_map(aware_id(id)), ...
                trial ...
                subject.age(id_map(aware_id(id))), ...
                subject.sex(id_map(aware_id(id))), ...
                subject.height(id_map(aware_id(id))), ...
                subject.weight(id_map(aware_id(id)))]];
            exhale_outcome = [exhale_outcome; ...
                [subject.group(id_map(aware_id(id))), ...
                subject.fev1(id_map(aware_id(id))), ...
                subject.ratio(id_map(aware_id(id))), ...
                subject.fef2575(id_map(aware_id(id))), ...
                subject.fev1_pred(id_map(aware_id(id))), ...
                subject.ratio_pred(id_map(aware_id(id))), ...
                subject.fef2575_pred(id_map(aware_id(id)))]];
        end
    end
end
p1_inhale_data = inhale_data;
p1_inhale_outcome = inhale_outcome;
p1_inhale_verbose = inhale_verbose;

p1_exhale_data = exhale_data;
p1_exhale_outcome = exhale_outcome;
p1_exhale_verbose = exhale_verbose;

%     color = {'#D0D0D0','#0072BD','#D95319','#0072BD','#D95319','#0072BD','#D95319'};
%     style = {'-','-','-','--','--','-.','-.'};
