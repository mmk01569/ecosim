using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace WpfApplication1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ChildWindow _graphWindow;
        ChildWindow _simWindow;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void FileNew_Click(object sender, RoutedEventArgs e)
        {
            //Line line = new Line();
            //line.Stroke = Brushes.LightSteelBlue;

            //line.X1 = 1;
            //line.X2 = 50;
            //line.Y1 = 1;
            //line.Y2 = 50;

            //line.StrokeThickness = 2;
            //GraphCanvas.Children.Add(line);
        }
        private void FileOpen_Click(object sender, RoutedEventArgs e)
        {
            //Line line = new Line();
            //line.Stroke = Brushes.LightSteelBlue;

            //line.X1 = 1;
            //line.X2 = 50;
            //line.Y1 = 1;
            //line.Y2 = 50;

            //line.StrokeThickness = 2;
            //GraphCanvas.Children.Add(line);
        }

        private void ToggleView(ref ChildWindow win, bool visible)
        {
            if (win == null)
            {
                win = new ChildWindow();
                win.ShowInTaskbar = false;
                win.Owner = Application.Current.MainWindow;
                win.WindowStartupLocation = WindowStartupLocation.CenterOwner;
            }

            if (visible)
            {
                win.Show();
            }
            else
            {
                
                win.Close();
            }
        }
        private void FileExit_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ViewGraph_Click(object sender, RoutedEventArgs e)
        {
            ToggleView(ref _graphWindow, ((MenuItem)sender).IsChecked);
        }
        private void ViewMain_Click(object sender, RoutedEventArgs e)
        {
            //ToggleView(_graphWindow, ((MenuItem)sender).IsChecked);
        }
        private void ViewSim_Click(object sender, RoutedEventArgs e)
        {
            ToggleView(ref _simWindow, ((MenuItem)sender).IsChecked);
        }

        private void Run_Click(object sender, RoutedEventArgs e)
        {
            if (((MenuItem)sender).IsChecked == true)
            {
                _startTime = DateTimeOffset.Now;
                _lastTime = _startTime;
                _simulationTimer.Start();
            }
            else
            {
                _stopTime = DateTimeOffset.Now;
                _simulationTimer.Stop();
            }
        }

        void SimulationTimer_Tick(object sender, object e)
        {
            //DateTimeOffset time = DateTimeOffset.Now;
            //TimeSpan span = time - _lastTime;
            _lastTime = DateTimeOffset.Now;
            //timesTicked++;
            //if (timesTicked > timesToTick)
            //{
            //    _stopTime = time;
            //    _simulationTimer.Stop);
            //}
        }
        DispatcherTimer _simulationTimer;
        DateTimeOffset _startTime;
        DateTimeOffset _lastTime;
        DateTimeOffset _stopTime;
        int timesTicked = 1;
        int timesToTick = 10;
        private void DispatcherTimerSetup()
        {
            _simulationTimer = new DispatcherTimer();
            _simulationTimer.Tick += SimulationTimer_Tick;
            _simulationTimer.Interval = new TimeSpan(0, 0, 1);
        }
        private void PageLoaded(object sender, RoutedEventArgs e)
        {
            DispatcherTimerSetup();
        }
    }
}
