
t = [0:0.1:5]';
y_1 = [sin(t), cos(t)];
y_2 = [0.8*sin(t), 0.8*cos(t)];

f = figure('visible', 'on','Position', [400 400 500 400]);
subplot(2,1,1);
plot(t,y_1(:,1),'LineWidth',1.5,'Color',[0.2 1 0.8])
hold on
plot(t,y_2(:,1),'LineWidth',1.5,'Color',[0.2 0.5 0.8])
ylabel('$u(\mathbf{x_a},t)$ [K]','Interpreter','latex','FontSize',25);
set(legend,'FontName','Helvetica','Location','Northeast','Interpreter','latex');
legend({'Exact','Numerical'});
grid on
set(findall(gcf,'-property','FontSize'),'FontSize',15)

subplot(2,1,2);
plot(t,y_1(:,2),'LineWidth',1.5,'Color',[0.2 1 0.8])
hold on
plot(t,y_2(:,2),'LineWidth',1.5,'Color',[0.2 0.5 0.8])
ylabel('$u(\mathbf{x_b},t)$ [K]','Interpreter','latex','FontSize',25);
xlabel('time [s]','Interpreter','latex','FontSize',15);
grid on
set(findall(gcf,'-property','FontSize'),'FontSize',15)


saveas(f, strcat('Plots\one_node_time_series.png'))