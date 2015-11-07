modeldk;


t10 = 30;
t20 = 40;
t30 = 30;
t40 = 30;

T10 = vpa(subs(T1,t1, t10));
T20 = vpa(subs(T2,t2, t20));
T30 = vpa(subs(T3,t3, t30));
T40 = vpa(subs(T4,t4, t40));

p1 = T10(1:2,4);

aux = (T10*T20);
p2 = aux(1:2,4);

aux = (T10*T20*T30);
p3 = aux(1:2,4);

aux = (T10*T20*T30*T40);
p4 = aux(1:2,4);

X = [0,p1(1), p2(1), p3(1), p4(1)];
Y = [0,p1(2), p2(2), p3(2), p4(2)];

plot(X,Y);