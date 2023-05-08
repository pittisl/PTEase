function acc = subjectAcc(Y, T, id)

Y = extractdata(Y);
T = extractdata(T);
id = extractdata(id);

subject = unique(id);
idx = (id'==subject);
idx = idx./sum(idx,1);
Y = Y*idx;
T = T*idx;

S = Y;

classes = {'1';'2'};
Y = onehotdecode(Y,classes,1)';
T = onehotdecode(T,classes,1)';
acc = sum(Y==T)/length(Y);

% classLabels = categorical(["Healthy" "Asthma"]);
% figure;
% plotconfusion(classLabels(T),classLabels(Y));
% 
% figure;
% labels = T;
% scores = S(2,:);
% [X,Y,T,AUC,OPTROCPT] = perfcurve(labels,scores,"2");
% plot(X,Y);
% xlabel('False positive rate (1-Specificity)');
% ylabel('True positive rate (Sensitvity)');
% title('Receiver-Operating Characteristic (ROC) Curve');
% text(0.65, 0.1, "AUC="+num2str(AUC));

end

