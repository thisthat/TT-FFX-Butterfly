using Microsoft.Win32;
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
using TT_FFX_Butterfly.classes;

namespace TT_FFX_Butterfly
{
    /// <summary>
    /// Logica di interazione per MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        const double dimRect = 5f;
        Vector lastPosition;
        Vector preDrawPosition;
        DirectionPoint.ARROW preDrawArrow = DirectionPoint.ARROW.NOPE;
        string path_open;
        List<DirectionPoint> points = new List<DirectionPoint>();
        Rectangle lastRectangle;
        bool activeDraw = false;
        Vector p;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnLoadFile_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog d = new OpenFileDialog();
            d.CheckFileExists = true;
            d.DefaultExt = "*.xml";
            d.Filter = "XML documents (.xml)|*.xml";
            var result = d.ShowDialog();
            if (result == true)
            {
                path_open = d.FileName;
                XMLManager xml = new XMLManager(path_open);
                points = xml.Reader();
                Vector o = new Vector(0,0);
                //Esiste una origine?
                var res = points.Find(ep => !o.Equals(ep.position));
                if (res != null)
                {
                    tela.Children.Clear();
                    p = res.position;
                    draw(p);
                    lastPosition = p;
                    foreach (var item in points)
                    {
                        lastPosition = generatePosition(item.point);
                        draw(lastPosition);
                    }
                }
            }
        }

        private Vector generatePosition(DirectionPoint.ARROW arrow)
        {
            double _x = 0, _y = 0;
            if((DirectionPoint.ARROW.UP & arrow) > 0){
                _y -= dimRect;
            }
            if((DirectionPoint.ARROW.DOWN & arrow) > 0){
                _y += dimRect;
            }
            if((DirectionPoint.ARROW.LEFT & arrow) > 0){
                _x -= dimRect;
            }
            if((DirectionPoint.ARROW.RIGHT & arrow) > 0){
                _x += dimRect;
            }
            //TODO : Middle
            return new Vector(lastPosition.X + _x, lastPosition.Y +_y);
        }

        private void img_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed && activeDraw)
            {
                DirectionPoint point = new DirectionPoint();
                if (tela.Children.Count > 1)
                {
                    lastPosition = preDrawPosition;
                    draw(preDrawPosition);
                    point.point = preDrawArrow;
                }
                else
                {
                    Vector pos = (Vector)(e.GetPosition(this));
                    lastPosition = pos;
                    draw(pos);
                    point.point = DirectionPoint.ARROW.NOPE;
                    point.position = pos;
                }
                points.Add(point);
            }
            if (e.RightButton == MouseButtonState.Pressed && activeDraw)
            {
                DirectionPoint point = new DirectionPoint();
                if (tela.Children.Count > 1)
                {
                    lastPosition = preDrawPosition;
                    draw(preDrawPosition,false);
                    point.point = preDrawArrow;
                    point.isButteFly = true;
                }
                else
                {
                    Vector pos = (Vector)(e.GetPosition(this));
                    lastPosition = pos;
                    draw(pos,false);
                    point.point = DirectionPoint.ARROW.NOPE;
                    point.position = pos;
                }
                points.Add(point);
            }
        }

        private void draw(Vector pos,bool black = true)
        {
            Rectangle rectangle = new Rectangle();
            rectangle.Width = dimRect;
            rectangle.Height = dimRect;
            if (black) { rectangle.Fill = new SolidColorBrush(System.Windows.Media.Colors.Black); }
            else { rectangle.Fill = new SolidColorBrush(System.Windows.Media.Colors.Red); }
            rectangle.Stroke = new SolidColorBrush(System.Windows.Media.Colors.White);
            tela.Children.Add(rectangle);
            Canvas.SetLeft(rectangle, pos.X);
            Canvas.SetTop(rectangle, pos.Y);
        }
        private void draw(Vector pos,Rectangle rectangle)
        {
            tela.Children.Add(rectangle);
            Canvas.SetLeft(rectangle, pos.X);
            Canvas.SetTop(rectangle, pos.Y);
        }
        private Rectangle preDraw(Vector pos, Rectangle r)
        {
            tela.Children.Remove(r);
            Rectangle rectangle = new Rectangle();
            rectangle.Width = dimRect;
            rectangle.Height = dimRect;
            rectangle.Fill = new SolidColorBrush(System.Windows.Media.Colors.Black);
            rectangle.Stroke = new SolidColorBrush(System.Windows.Media.Colors.White);
            tela.Children.Add(rectangle);
            Canvas.SetLeft(rectangle, pos.X);
            Canvas.SetTop(rectangle, pos.Y);
            return rectangle;
        }

        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            activeDraw = !activeDraw;
            if (activeDraw)
            {
                btnStart.Content = "Stop";
            }
            else
            {
                btnStart.Content = "Start";
            }
        }

        private void Window_MouseMove(object sender, MouseEventArgs e)
        {
            if (activeDraw)
            {
                Vector pos = (Vector)(e.GetPosition(this));
                double alpha = angleVector(lastPosition, pos);
                double _x = 0, _y = 0;
                if (alpha > 0 && alpha < 0.78f)
                {
                    _x = dimRect;
                }
                if (alpha > 0.78f && alpha < 2.53f)
                {
                    _y = dimRect;
                }
                if (alpha > 2.53f)
                {
                    _x -= dimRect;
                }
                if (alpha < 0f && alpha > -0.78f)
                {
                    _x = dimRect;
                }
                if (alpha < -0.78f && alpha > -2.53f)
                {
                    _y -= dimRect;
                }
                if (alpha < -2.53f)
                {
                    _x -= dimRect;
                }
                preDrawPosition = new Vector(lastPosition.X + _x, lastPosition.Y + _y);
                lastRectangle = preDraw(preDrawPosition, lastRectangle);

            }
        }

        private double angleVector(Vector a, Vector b)
        {
            return Math.Atan2(b.Y - a.Y, b.X - a.X);
        }

        private void btnSaveFile_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(points.Count + "");
        }
    }
}
