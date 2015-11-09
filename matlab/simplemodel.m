clear all, close all, clc;

%% Parameters
a1 = 177;
a2 = 95;

t10 = 0;%60/180*pi;
t20 = 0;%-120/180*pi;
t30 = 0;%150/180*pi;
t40 = 0;%-120/180*pi;

offsets = [t10,t20];

display('Calculus of forwards kinematics');

%% Variables
t1 = sym('t1', 'real');
t2 = sym('t2', 'real');
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


T = T1*T2;

addpath('rvctools');
startup_rvc;

L(1) = Link([0 0 a1 0 0]);
L(1).offset = t10;

L(2) = Link([0 0 a2 0 0]);
L(2).offset = t20;

robot = SerialLink(L, 'name', 'Planar');

x = 100;
y = 100;

st2 = atan2(sqrt(1-(x^2+y^2-a1^2 -a2^2)/(2*a1*a2)),(x^2+y^2-a1^2 -a2^2)/(2*a1*a2));
st1 = atan2(sqrt(1-(x*(a1+a2*cos(st2)+y*a2*sin(st2)))/(x^2+y^2)),(x*(a1+a2*cos(st2)+y*a2*sin(st2))));
% display('Calculus of jacobi');
% p = T(1:2,4);
% vars = [t1,t2,t3,t4];
% syms J;
% for i = 1:4
%    for j=1:2
%       J(j,i) = diff(p(j), vars(i)); 
%    end
% end
% display('Simplifying jacobi');
% J = simplify(J);
% display('Simplifying inverse of jacobi');
% Jpinv = simplify(pinv(J));


