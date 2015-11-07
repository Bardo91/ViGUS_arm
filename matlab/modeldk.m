%% Parameters
a1 = 83;
a2 = 177;
a3 = 75;
a4 = 40;

t10 = -30/180*pi;
t20 = -120/180*pi;
t30 = 150/180*pi;
t40 = -120/180*pi;

offsets = [t10,t20,t30, t40];

%% Variables
t1 = sym('t1', 'real');
t2 = sym('t2', 'real');
t3 = sym('t3', 'real');
t4 = sym('t4', 'real');
%% tranformation 1
R1 = [  cos(t1), -sin(t1), 0, 0; ...
        sin(t1), cos(t1), 0, 0;...
        0, 0, 1, 0; ...
        0, 0, 0, 1];
D1 = [1,0,0,a1;0,1,0,0;0,0,1,0;0,0,0,1];

T1 = R1*D1;

%% tranformation 2
R2 = [  cos(t2), -sin(t2), 0, 0; ...
        sin(t2), cos(t2), 0, 0;...
        0, 0, 1, 0; ...
        0, 0, 0, 1];
D2 = [1,0,0,a2;0,1,0,0;0,0,1,0;0,0,0,1];

T2 = R2*D2;


%% tranformation 3
R3 = [  cos(t3), -sin(t3), 0, 0; ...
        sin(t3), cos(t3), 0, 0;...
        0, 0, 1, 0; ...
        0, 0, 0, 1];
D3 = [1,0,0,a3;0,1,0,0;0,0,1,0;0,0,0,1];

T3 = R3*D3;


%% tranformation 4
R4 = [  cos(t4), -sin(t4), 0, 0; ...
        sin(t4), cos(t4), 0, 0;...
        0, 0, 1, 0; ...
        0, 0, 0, 1];
D4 = [1,0,0,a4;0,1,0,0;0,0,0,0;0,0,0,1];

T4 = R4*D4;

T = T1*T2*T3*T4;

p = T(1:2,4);
vars = [t1,t2,t3,t4];
syms J;
for i = 1:4
   for j=1:2
      J(j,i) = diff(p(j), vars(i)); 
   end
end

Jpinv = pinv(J);
