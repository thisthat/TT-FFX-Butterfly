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

        string path_open;
        List<DirectionPoint> points;

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
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                Vector pos = (Vector)(e.GetPosition(this));
                draw(pos);
            }
        }

        private void draw(Vector pos)
        {
            Rectangle rectangle = new Rectangle();
            rectangle.Width = dimRect;
            rectangle.Height = dimRect;
            rectangle.Fill = new SolidColorBrush(System.Windows.Media.Colors.Black);
            rectangle.Stroke = new SolidColorBrush(System.Windows.Media.Colors.White);
            tela.Children.Add(rectangle);
            Canvas.SetLeft(rectangle, pos.X);
            Canvas.SetTop(rectangle, pos.Y);
        }
    }
}
