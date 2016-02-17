function grsp2mat(fdname_bin, fname_bin, fdname_m)
% This function reads the binary data file and covert them to .m file
% One .mat file per trail. 


%% Initialise 
fpath = fullfile(fdname_bin, [fname_bin '.grsp']);
disp(fpath)
fid = fopen(fpath);
allChar = fread(fid, '1*char');
allChar = allChar';

index_Tek = strfind(allChar, [116 101 107 115 99 97 110]); %tekscan
index_Glove = strfind(allChar, [103 108 111 118 101]); %glove
index_Opt = strfind(allChar, [111 112 116 105 116 114 97 99 107]); %optitrack
index_FT = strfind(allChar, [102 111 114 99 101 116 111 114 113 117 101]); %forcetorque
sizeTek = size(index_Tek,2); 
sizeGlove = size(index_Glove,2); 
sizeOpt = size(index_Opt,2); 
sizeFT = size(index_FT,2); 

numData = max([sizeTek sizeGlove sizeOpt sizeFT]);
%part of hand*phonlange*side*number of data
tactile =       cell(6,3,2,numData,1); % calibrated by force torque
tactile_r =   cell(6,3,2,numData,1); % raw data
tactile_c =  cell(6,3,2,numData,1); % calibrated by Tekscan
track =         cell(numData,1);  
forcetorque =   cell(numData,1);
glove =         cell(numData,1); 
time =          cell(numData,1);
time_ft =       cell(numData,1);
time_opt =      cell(numData,1);
time_glove =    cell(numData,1);

[tactile{:}]=deal(-1);[tactile_r{:}]=deal(-1);[tactile_c{:}]=deal(-1);
[track{:}]=deal(-1);[forcetorque{:}]=deal(-1);[glove{:}]=deal(-1);[time{:}]=deal(-1);


%% Tekscan
if (sizeTek > 0)
    disp(['Reading ' int2str(sizeTek) ' Tekscan ... ']);
    dimRaw = 1479; dimCal = 1479;
    raw_tex = zeros(1, dimRaw); cal_tex = zeros(1, dimCal);
    frewind(fid);
    for t = 1:sizeTek -1
        if (index_Tek(t) > 1) fseek(fid, index_Tek(t)-1, 'bof');end       
        buff = fread(fid, 7+1, '1*char'); % tekscan\0
        buff = fread(fid, 4, '1*int32'); % time stamp
        time{t,1} = buff';
        
        if or(or(buff(1)>24, buff(2)>60),or(buff(3)>60,buff(4)>1000))
           disp(['Tekscan time stamp over float at ' int2str(t) ' !/n']);
           pause;
        end
        
        % raw data
        buff = fread(fid, 1, '1*int32'); % size of raw data: (25*2+1)*29 = 1479 
        buff = fread(fid, dimRaw, '1*uint8'); % raw data
        raw_tex(1:dimRaw) = buff'; 
        raw_tex = reshape(raw_tex,51,29)';

        % calibrated data by Tekscan
        buff = fread(fid, 1, '1*int32'); % size of calculated data: 725
        buff = fread(fid, dimCal, '1*float'); % calibrated data
        cal_tex(1:dimCal) = buff';
        cal_tex = reshape(cal_tex,51,29)';
        
        % Convert to .mat format
        tactile_r(:,:,:,t,1) = parseTekscanData_newsensors(raw_tex);
        tactile_c(:,:,:,t,1) = parseTekscanData_newsensors(cal_tex);
    end
    tactile_r(1,1,1,sizeTek) = {-1};
    tactile_c(1,1,1,sizeTek) = {-1};
end

%% Optitrack
if (sizeOpt > 0)
    disp(['Reading ' int2str(sizeOpt) ' Optitrack...']);
    DIMOPT = 16; %homogeneous matrix
    wrist = zeros(DIMOPT); bottlecap = zeros(DIMOPT);
    frewind(fid);
    for o = 1:sizeOpt-1
        if (index_Opt(o)>1) fseek(fid, index_Opt(o)-1,'bof');end
        buff = fread(fid, 9+1, '1*char'); %optitrack\0
        buff = fread(fid, 4, '1*int32'); %time stamp
        time_opt{o, 1} = buff';
        
        if or(or(buff(1)>24, buff(2)>60),or(buff(3)>60,buff(4)>1000))
           error(['Optitrack time stamp over float ' int2str(o) ' !/n']);
        end

        %Object 1: ftsensor_root
%         buff = fread(fid, 13+1, '1*char');%ftsensor_root
%         buff = fread(fid, 1, '1*int32'); % 128
%         buff = fread(fid, DIMOPT, '1*double'); 
%         bottlecap = buff';   
        
        %Object 2: wrist
%         buff = fread(fid, 10+1, '1*char');%wrist_root
%         buff = fread(fid, 1, '1*int32'); %  128 
%         buff = fread(fid, DIMOPT, '1*double'); 
%         wrist = buff';
     
        %Object 1: obj1
        buff = fread(fid, 10+1, '1*char');%hand5_root
        buff = fread(fid, 1, '1*int32'); % 128
        buff = fread(fid, DIMOPT, '1*double'); 
        obj1 = buff';   
        
        %Object 2: obj2
        buff = fread(fid, 20+1, '1*char');%right_shoulder5_root
        buff = fread(fid, 1, '1*int32'); %  128 
        buff = fread(fid, DIMOPT, '1*double'); 
        obj2 = buff';
        
        %Object 1: obj1
        buff = fread(fid, 10+1, '1*char');%neck5_root
        buff = fread(fid, 1, '1*int32'); % 128
        buff = fread(fid, DIMOPT, '1*double'); 
        obj3 = buff';   



        % convert to mat format
%         wrist = reshape(wrist,4,4)'; wrist(1:3,4) = wrist(1:3,4) / 10;
%         bottlecap = reshape(bottlecap, 4,4)'; bottlecap(1:3,4) = bottlecap(1:3,4) / 10;
%         track{o,1} = [wrist; bottlecap];
        obj1 = reshape(obj1,4,4)'; obj1(1:3,4) = obj1(1:3,4) / 10;
        obj2 = reshape(obj2, 4,4)'; obj2(1:3,4) = obj2(1:3,4) / 10;
        obj3 = reshape(obj3, 4,4)'; obj3(1:3,4) = obj3(1:3,4) / 10;
        track{o,1} = [obj1; obj2; obj3];

    end
    track{sizeOpt} = -1;
end

%% ForceTorque
if (sizeFT > 0)
    disp(['Reading ' int2str(sizeFT) ' forcetorque...']);
    DIMFT = 6;
    data_ft = zeros(DIMFT);
    frewind(fid);
    for ft = 1:sizeFT
        if (index_FT(ft)>1) fseek(fid, index_FT(ft)-1,'bof');end
        buff = fread(fid, 11+1, '1*char'); %ForceTorque\0
        buff = fread(fid, 4, '1*int32'); %time stamp
        time_ft{ft,1} = buff';
        
        if or(or(buff(1)>24, buff(2)>60),or(buff(3)>60,buff(4)>1000))
           error(['Forcetorque time stamp over float ' int2str(o) ' !/n']);
        end 
        
        buff = fread(fid, 1, '1*int32'); % 48
        buff = fread(fid, DIMFT, '1*double'); 
        data_ft = buff';
        
        forcetorque{ft,1} = data_ft;
    end
    forcetorque{sizeFT} = -1;
end

%% Glove
if (sizeGlove > 0)
    dimGlove = 23;
    disp(['Reading ' int2str(sizeGlove) ' Glove...']);
    frewind(fid);  
    for g = 1:sizeGlove
        if (index_Glove(g) > 1) fseek(fid, index_Glove(g)-1, 'bof');end
        buff = fread(fid, 5+1, '1*char'); %glove\0
        buff = fread(fid, 4, '1*int32'); % time stamp
        time_glove{g,1} = buff';
        
        if or(or(buff(1)>24, buff(2)>60),or(buff(3)>60,buff(4)>1000))
           error(['Glove time stamp over float ' int2str(g) ' !/n']);
        end
       
        buff = fread(fid, 1, '1*int32'); % size of glove data: 23
        buff = fread(fid, dimGlove, '1*double');
        data_glove(1:dimGlove) = buff'; 
        glove{g,1} = data_glove;
    end
    glove{sizeGlove} = -1;
end

fpath = fullfile(fdname_m, [fname_bin, '.mat']);
save(fpath, 'tactile', 'tactile_r', 'tactile_c', 'track', 'forcetorque', 'glove', 'time', 'time_ft', 'time_opt', 'time_glove');

disp([int2str(length(tactile)) ' Tek ' int2str(length(forcetorque)) ' FT ' int2str(length(track)) ' Opt ' int2str(length(glove)) ' Glove -> ' fname_bin '.mat']);
fclose all;
end