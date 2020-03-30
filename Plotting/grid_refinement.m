function [] = grid_refinement(grid_file)


fid = fopen(grid_file,'rt');
grid2 =  cell2mat(textscan(fid,'','delimiter',' '));
fclose(fid);


f = figure('visible', 'off','Position', [400 400 600 400]);
plot(grid2(:,1),grid2(:,2),'LineWidth',1.5,'Color',[1 0.5 0])

ylabel('Absolute Error Vector Norm [K]');
grid on
grid minor
legend off



xlabel('Number of Nodes');


annotation('textbox',[0.7 0.9 0  0],'String','dt = 0.001','FitBoxToText','on','BackgroundColor','w','Interpreter','latex');
set(findall(gcf,'-property','FontSize'),'FontSize',20)
set(gcf,'renderer','Painters','Color', 'w');

saveas(f, strcat('Plots\grid_refine'),'epsc')

end

