clear all, close all, clc;
modeldk;
addpath('rvctools');
startup_rvc;

L(1) = Link([0 0 a1 0 0]);
L(1).offset = t10;

L(2) = Link([0 0 a2 0 0]);
L(2).offset = t20;

L(3) = Link([0 0 a3 0 0]);
L(3).offset = t30;

L(4) = Link([0 0 a4 0 0]);
L(4).offset = t40;

robot = SerialLink(L, 'name', 'Planar');
%robot.plot([0,0,0,0]);

robot.fkine([0,0,0,0])