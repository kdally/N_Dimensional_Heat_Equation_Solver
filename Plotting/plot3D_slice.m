function [] = plot3D_slice(solExact,solSolve,dt,t)


fid = fopen(solExact,'rt');
U_exact = cell2mat(textscan(fid,'','delimiter',' '));
U_exact = U_exact(1,1:end-1);
m = sqrt(length(U_exact));
U_exact = reshape(U_exact,[m,m]);
fclose(fid);

fid = fopen(solSolve,'rt');
U_solve = cell2mat(textscan(fid,'','delimiter',' '));
U_solve = U_solve(1,1:end-1);
U_solve = reshape(U_solve,[m,m]);
fclose(fid);


dx = 1/(m+1);
x = 0:dx:(m-1)*dx;
x_fix = x(round(m/2));
U_exact_slice = U_exact(x==x_fix,:);
U_solve_slice = U_solve(x==x_fix,:);

f = figure('visible', 'off','Position', [400 400 500 500]);

plot(x,U_exact_slice,'-o','LineWidth',1.5,'color',[0.2 0.5 0.8])
hold on
plot(x,U_solve_slice,'-o','LineWidth',1.5,'color',[1 0.5 0])
set(legend,'FontName','Helvetica','Location','Northeast','Interpreter','latex');
legend({'Exact','Numerical'});
set(gca,'xtick',[0:0.25:1])
xlabel('y [m]','Interpreter','latex');
if m==20
    ylim([0 2.6e-3]);
end 
ylabel(strcat('$u(\mathbf{x},t=',num2str(t),'s)$ [K]'),'Interpreter','latex','FontSize',20);
pos = get(legend, 'Pos') + [-0.1 -0.11 0  0];
str = strcat('x = ',num2str(x_fix,'%.3f'),' m');
annotation('textbox',pos,'String',str,'FitBoxToText','on','BackgroundColor','w','Interpreter','latex');

pos2 = get(legend, 'Pos') + [-0.57 0 0  0];
str2 = {['m =' ' ' num2str(m)];['dt = ' num2str(dt)]};

annotation('textbox',pos2,'String',str2,'FitBoxToText','on','BackgroundColor','w','Interpreter','latex');
set(findall(gcf,'-property','FontSize'),'FontSize',20)
grid on
grid minor
set(gcf,'renderer','Painters')
saveas(f, strcat('Plots\3D_slice_m_',num2str(m),'_dt_',num2str(dt*1000)),'epsc')

end

