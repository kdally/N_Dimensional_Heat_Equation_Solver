
%% PLOTS DONT APPEAR. THEY ARE SAVEC IN THE FOLDER 'PLOTS'


t_final = 1; %s
dt = 0.01; %s
plot3D('solExact2Dm20.txt','solSolve2Dm20.txt',dt,t_final);
plot3D_slice('solExact2Dm20.txt','solSolve2Dm20.txt',dt,t_final);

t_final = 1; %s
dt = 0.001; %s
plot3D('heat2DExactM20DT001.txt','heat2DSolveM20DT001.txt',dt,t_final);
plot3D_slice('heat2DExactM20DT001.txt','heat2DSolveM20DT001.txt',dt,t_final);

t_final = 0.5; %s
dt = 0.001; %s
plot3D('heat2DExact99.txt','heat2DSolve99.txt',dt,t_final);
plot3D_slice('heat2DExact99.txt','heat2DSolve99.txt',dt,t_final);


t_final = 1; %s
dt = 0.001; %s
plot1D('heat1DExact99.txt','heat1DSolve99.txt',dt,t_final);

%%
grid_refinement('Grid_Data.txt')

%%
