function fingers = parseTekscanData_newsensors(data)
    thumb1 = [];
    thumb2 = [];
    index1 = [];
    index2 = [];
    index3 = [];
    middle1 = [];
    middle2 = [];
    middle3 = [];
    ring1 = [];
    ring2 = [];
    ring3 = [];
    pinky1 = [];
    pinky2 = [];
    pinky3 = [];
    palm1 = [];
    palm2 = [];
    palm31 = [];
    palm32 = [];

    Sthumb1 = [];
    Sthumb2 = [];    
    Sindex1 = [];
    Sindex2 = [];
    Sindex3 = [];
    Smiddle1 = [];
    Smiddle2 = [];
    Smiddle3 = [];
    Sring1 = [];
    Sring2 = [];
    Sring3 = [];
    Spinky1 = [];
    Spinky2 = [];
    Spinky3 = [];
    Spalm1 = [];
    Spalm2 = [];
    Spalm31 = [];
    Spalm32 = [];

    n  = 1;
    thumb1 =  [thumb1; data(n+15:n+18, 1:4)] ; % 4x4


    thumb2 =  [thumb2; data(n+20:n+22, 1:4)] ; % 3x4

    index1 =  [index1;  data(n+0: n+3, 7:10)] ; % 4x4
    index2 =  [index2;  data(n+5: n+7, 7:10)] ; % 3x4
    index3 =  [index3;  data(n+9: n+11, 7:10)] ; % 3x4

    middle1 =  [middle1; data(n+0:n+3, 12:15)] ; % 4x4
    middle2 =  [middle2;  data(n+5:n+7, 12:15)] ; % 3x4
    middle3 =  [middle3; data(n+9:n+11, 12:15)] ; % 3x4

    ring1 =  [ring1; data(n+0:n+3, 17:20)] ; % 4x4
    ring2 =  [ring2;  data(n+5:n+7, 17:20)] ; % 3x4
    ring3 =  [ring3;  data(n+9:n+11, 17:20)] ; % 3x4

    pinky1 =  [pinky1;  data(n+0:n+3, 22:25)] ; % 4x4
    pinky2 =  [pinky2;  data(n+5:n+7, 22:25)] ; % 3x4
    pinky3 =  [pinky3;  data(n+9:n+11, 22:25)] ; % 3x4

    palm1 =  [palm1;  data(n+13:n+16, 7:25)] ; % 4x19
    palm2 =  [palm2;  data(n+24:n+28, 6:14)] ; % 5x9
    palm31 =  [palm31;  data(n+25:n+28, 18:25)] ; % 4x8
    palm32 =  [palm32;  data(n+20:n+24, 22:25)] ; % 5x4


    d = 25 + 1;

    Sthumb1 =  [Sthumb1; data(n+15:n+18, 1+d:4+d)] ; % 4x4
    Sthumb2 =  [Sthumb2;  data(n+20:n+22, 1+d:4+d)] ; % 3x4

    Sindex1 =  [Sindex1;  data(n+0: n+3, 7+d:10+d)] ; % 4x4
    Sindex2 =  [Sindex2;  data(n+5: n+7, 7+d:10+d)] ; % 3x4
    Sindex3 =  [Sindex3;  data(n+9: n+11, 7+d:10+d)] ; % 3x4

    Smiddle1 =  [Smiddle1; data(n+0:n+3, 12+d:15+d)] ; % 4x4
    Smiddle2 =  [Smiddle2; data(n+5:n+7, 12+d:15+d)] ; % 3x4
    Smiddle3 =  [Smiddle3; data(n+9:n+11, 12+d:15+d)] ; % 3x4

    Sring1 =  [Sring1;  data(n+0:n+3, 17+d:20+d)] ; % 4x4
    Sring2 =  [Sring2; data(n+5:n+7, 17+d:20+d)] ; % 3x4
    Sring3 =  [Sring3;  data(n+9:n+11, 17+d:20+d)] ; % 3x4

    Spinky1 =  [Spinky1; data(n+0:n+3, 22+d:25+d)] ; % 4x4
    Spinky2 =  [Spinky2;  data(n+5:n+7, 22+d:25+d)] ; % 3x4
    Spinky3 =  [Spinky3;  data(n+9:n+11, 22+d:25+d)] ; % 3x4

    Spalm1 =  [Spalm1;  data(n+13:n+16, 7+d:25+d)] ; % 4x19
    Spalm2 =  [Spalm2; data(n+24:n+28, 6+d:14+d)] ; % 5x9
    Spalm31 =  [Spalm31;  data(n+25:n+28, 18+d:25+d)] ; % 4x8
    Spalm32 =  [Spalm32; data(n+20:n+24, 22+d:25+d)] ; % 5x4

    fingers = cell(6,3,2);    
    fingers{1,1,1} = palm2;
    fingers{1,1,2} = [];
    fingers{1,2,1} = thumb2;
    fingers{1,2,2} = Sthumb2;
    fingers{1,3,1} = thumb1;
    fingers{1,3,2} = Sthumb1;    
 
    fingers{2,1,1} = index3;
    fingers{2,2,1} = index2;
    fingers{2,3,1} = index1;    
    fingers{2,1,2} = Sindex3;    
    fingers{2,2,2} = Sindex2;
    fingers{2,3,2} = Sindex1;
    
    fingers{3,1,1} = middle3;    
    fingers{3,2,1} = middle2;
    fingers{3,3,1} = middle1;    
    fingers{3,1,2} = Smiddle3;    
    fingers{3,2,2} = Smiddle2;
    fingers{3,3,2} = Smiddle1;    

    fingers{4,1,1} = ring3;    
    fingers{4,2,1} = ring2;
    fingers{4,3,1} = ring1;    
    fingers{4,1,2} = Sring3;
    fingers{4,2,2} = Sring2;
    fingers{4,3,2} = Sring1;    

    fingers{5,1,1} = pinky3;
    fingers{5,2,1} = pinky2;
    fingers{5,3,1} = pinky1;        
    fingers{5,1,2} = Spinky3;    
    fingers{5,2,2} = Spinky2;
    fingers{5,3,2} = Spinky1;    
    
    fingers{6,1,1} = Spalm31;
    fingers{6,2,1} = Spalm32;
    fingers{6,3,1} = [palm1(:,1:4) Spalm1(:,5:19)];    
    fingers{6,1,2} = palm31;    
    fingers{6,2,2} = palm32;
    fingers{6,3,2} = Spalm1(:,1:4);    
    
end