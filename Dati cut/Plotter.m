%% Script per caricare e visualizzare i dati per sapere quando tagliare
% Script generato da matlab
% Alpha = 1
filename = 'C:\Users\Dante Slongo\Desktop\FRANCESCO\Università fisica\Terzo anno\PAF\VMC\Variational_MonteCarlo\Variational_MonteCarlo\CutData_alpha_1.000000_omega_1.000000.txt';
delimiter = '\t';
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string',  'ReturnOnError', false);
fclose(fileID);
Dataalpha1 = [dataArray{1:end-1}];
clearvars filename delimiter formatSpec fileID dataArray ans;
% Alpha = 2
filename = 'C:\Users\Dante Slongo\Desktop\FRANCESCO\Università fisica\Terzo anno\PAF\VMC\Variational_MonteCarlo\Variational_MonteCarlo\CutData_alpha_2.000000_omega_1.000000.txt';
delimiter = '\t';
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string',  'ReturnOnError', false);
fclose(fileID);
Dataalpha2 = [dataArray{1:end-1}];
clearvars filename delimiter formatSpec fileID dataArray ans;
% Alpha = 3
filename = 'C:\Users\Dante Slongo\Desktop\FRANCESCO\Università fisica\Terzo anno\PAF\VMC\Variational_MonteCarlo\Variational_MonteCarlo\CutData_alpha_3.000000_omega_1.000000.txt';
delimiter = '\t';
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string',  'ReturnOnError', false);
fclose(fileID);
Dataalpha3 = [dataArray{1:end-1}];
clearvars filename delimiter formatSpec fileID dataArray ans;
% Alpha = 4
filename = 'C:\Users\Dante Slongo\Desktop\FRANCESCO\Università fisica\Terzo anno\PAF\VMC\Variational_MonteCarlo\Variational_MonteCarlo\CutData_alpha_4.000000_omega_1.000000.txt';
delimiter = '\t';
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string',  'ReturnOnError', false);
fclose(fileID);
Dataalpha4 = [dataArray{1:end-1}];
clearvars filename delimiter formatSpec fileID dataArray ans;
% Alpha = 5
filename = 'C:\Users\Dante Slongo\Desktop\FRANCESCO\Università fisica\Terzo anno\PAF\VMC\Variational_MonteCarlo\Variational_MonteCarlo\CutData_alpha_5.000000_omega_1.000000.txt';
delimiter = '\t';
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string',  'ReturnOnError', false);
fclose(fileID);
Dataalpha5 = [dataArray{1:end-1}];
clearvars filename delimiter formatSpec fileID dataArray ans;

%% Plotto le figure
% alpha = 1
figure;
plot(Dataalpha1(:,1),Dataalpha1(:,2));
% alpha = 2
figure;
plot(Dataalpha2(:,1),Dataalpha2(:,2));
% alpha = 3
figure;
plot(Dataalpha3(:,1),Dataalpha3(:,2));
% alpha = 4
figure;
plot(Dataalpha4(:,1),Dataalpha4(:,2));
% alpha = 5
figure;
plot(Dataalpha5(:,1),Dataalpha5(:,2));