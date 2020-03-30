function [] = plot3D(solExact,solSolve,dt,t)


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
[X,Y] = meshgrid(x);

f = figure('visible', 'off','Position', [400 400 500 500]);
surf(X,Y,U_exact,'FaceColor','r', 'FaceAlpha',0.91);
hold on
surf(X,Y,U_solve,'FaceColor',[0.1 0.6 0.8], 'FaceAlpha',0.5,'EdgeColor',[0.5 0.5 0.5]);
set(legend,'FontName','Helvetica','Location','Northeast','Interpreter','latex');
legend({'Exact','Numerical'});
if m==20
zlim([0 2.6e-3]);
end 
ylabel('y [m]','Interpreter','latex');
set(gca,'xtick',[0:0.25:1])
set(gca,'ytick',[0:0.25:1])
xlabel('x [m]','Interpreter','latex');
zlabel(strcat('$u(\mathbf{x},t=',num2str(t),'s)$ [K]'),'Interpreter','latex','FontSize',20);
pos = get(legend, 'Pos') + [-0.55 0 0  0];

str = {['m =' ' ' num2str(m)];['dt = ' num2str(dt)]};
annotation('textbox',pos,'String',str,'FitBoxToText','on','BackgroundColor','w','Interpreter','latex');
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf,'renderer','Painters','Color', 'w');
name = strcat('3D_plot_m_',num2str(m),'_dt_',num2str(dt*1000),'.eps');
%saveas(f, strcat('Plots\3D_plot_m_',num2str(m),'_dt_',num2str(dt*1000)),'pdf')
export_fig(name)

movefile(name, 'Plots')

end

