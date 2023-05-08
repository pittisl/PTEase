inhale_data = [p1_inhale_data; p2_inhale_data];
exhale_data = [p1_exhale_data; p2_exhale_data];
inhale_outcome = [p1_inhale_outcome; p2_inhale_outcome];
exhale_outcome = [p1_exhale_outcome; p2_exhale_outcome];
inhale_outcome = array2table(inhale_outcome, ...
    'VariableNames',{'Diagnosis','FEV1','FEV1/FVC','FEF2575','FEV1_pred','FEV1/FVC_pred','FEF2575_pred',...
    'R5','R5_20','R20','X5','AX','TV','R5_z_score','R5_20_z_score','R20_z_score','X5_z_score','AX_z_score'});
exhale_outcome = array2table(exhale_outcome, ...
    'VariableNames',{'Diagnosis','FEV1','FEV1/FVC','FEF2575','FEV1_pred','FEV1/FVC_pred','FEF2575_pred',...
    'R5','R5_20','R20','X5','AX','TV','R5_z_score','R5_20_z_score','R20_z_score','X5_z_score','AX_z_score'});
inhale_verbose = [p1_inhale_verbose; p2_inhale_verbose];
exhale_verbose = [p1_exhale_verbose; p2_exhale_verbose];
inhale_verbose = array2table(inhale_verbose, ...
    'VariableNames',{'ID','Trial','Age','Sex','Height','Weight'});
exhale_verbose = array2table(exhale_verbose, ...
    'VariableNames',{'ID','Trial','Age','Sex','Height','Weight'});

writematrix(inhale_data, "res\inhale_data_v7_ave.csv");
writematrix(exhale_data, "res\exhale_data_v7_ave.csv");
writetable(inhale_outcome, "res\inhale_outcome_v7_ave.csv");
writetable(exhale_outcome, "res\exhale_outcome_v7_ave.csv");
writetable(inhale_verbose, "res\inhale_verbose_v7_ave.csv");
writetable(exhale_verbose, "res\exhale_verbose_v7_ave.csv");

% writematrix(inhale_label_1, "inhale_label_1.csv");
% writematrix(exhale_label_1, "exhale_label_1.csv");
% writematrix(inhale_label_2, "inhale_label_2.csv");
% writematrix(exhale_label_2, "exhale_label_2.csv");

% inhale_pct_1 = [p1_inhale_pct_1; p2_inhale_pct_1];
% exhale_pct_1 = [p1_exhale_pct_1; p2_exhale_pct_1];
% inhale_pct_2 = [p1_inhale_pct_2; p2_inhale_pct_2];
% exhale_pct_2 = [p1_exhale_pct_2; p2_exhale_pct_2];
% 
% writematrix(inhale_pct_1, "inhale_pct_1.csv");
% writematrix(exhale_pct_1, "exhale_pct_1.csv");
% writematrix(inhale_pct_2, "inhale_pct_2.csv");
% writematrix(exhale_pct_2, "exhale_pct_2.csv");