function [] = plot1D(solExact,solSolve,dt,t)


fid = fopen(solExact,'rt');
U_exact = cell2mat(textscan(fid,'','delimiter',' '));
U_exact = U_exact(1,1:end-1);
m = length(U_exact);
fclose(fid);

fid = fopen(solSolve,'rt');
U_solve = cell2mat(textscan(fid,'','delimiter',' '));
U_solve = U_solve(1,1:end-1);
fclose(fid);


dx = 1/(m+1);
x = 0:dx:(m-1)*dx;

f = figure('visible', 'off','Position', [400 400 500 500]);

plot(x,U_exact,'-s','LineWidth',1.5,'color',[0.2 0.5 0.8])
hold on
plot(x,U_solve,'-o','LineWidth',1.5,'color',[1 0.5 0])
set(legend,'FontName','Helvetica','Location','Northeast','Interpreter','latex');
legend({'Exact','Numerical'});
set(gca,'xtick',[0:0.25:1])
xlabel('x [m]','Interpreter','latex');
ylabel(strcat('$u(x,t=',num2str(t),'s)$ [K]'),'Interpreter','latex','FontSize',20);

pos = get(legend, 'Pos') + [-0.57 0 0  0];
str = {['m =' ' ' num2str(m)];['dt = ' num2str(dt)]};

annotation('textbox',pos,'String',str,'FitBoxToText','on','BackgroundColor','w','Interpreter','latex');
set(findall(gcf,'-property','FontSize'),'FontSize',20)
grid on
grid minor

set(gcf,'renderer','Painters')
saveas(f, strcat('Plots\1D_m_',num2str(m)),'epsc')
end

