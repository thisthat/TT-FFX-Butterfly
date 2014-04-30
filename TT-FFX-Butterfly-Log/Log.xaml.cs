using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace TT_FFX_Butterfly
{
    /// <summary>
    /// Logica di interazione per Log.xaml
    /// </summary>
    public partial class Log : Window
    {
        private class LogMessage
        {
            public string Time { set; get; }
            public string Message
            {
                get { return this._Message; }
                set { this._Message = value.Substring(0,value.Length - 1); }
            }
            private string _Message;
        }
        ObservableCollection<LogMessage> list = new ObservableCollection<LogMessage>();
        private Thread t;
        public Log()
        {
            InitializeComponent();
            lstLog.ItemsSource = list;
            System.Threading.Thread.Sleep(1000);
            t = new Thread(StartListening);
            t.IsBackground = true;
            t.Start();
        }

        private readonly UdpClient udp = new UdpClient(15150);
        private void StartListening()
        {
            
            IPEndPoint ip = new IPEndPoint(IPAddress.Any, 15150);
            //handleHost(ip);
            Thread t = new Thread(new ParameterizedThreadStart(handleHost));
            t.IsBackground = true;
            t.Start(ip);
        }

        private void handleHost(object obj)
        {
            IPEndPoint ip = (IPEndPoint) obj;
            handleHost(ip);
        }

        private void handleHost(IPEndPoint ip)
        {
            LogMessage msg;
            while (true)
            {
                Thread.Sleep(10);
                byte[] bytes = udp.Receive(ref ip);
                string message = Encoding.ASCII.GetString(bytes);
                string[] exp = message.Split(new String[] { "::" }, StringSplitOptions.RemoveEmptyEntries);
                Dispatcher.BeginInvoke((Action)(() =>
                {
                    try
                    {
                        msg = new LogMessage();
                        msg.Time = exp[0];
                        msg.Message = exp[1];
                        list.Add(msg);
                    }
                    catch (Exception) { }
                }));

            }
        }

       

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.S && Keyboard.Modifiers == ModifierKeys.Control)
            {
             
                SaveFile();
            }
            else if (e.Key == Key.Delete)
            {
                list.Clear();
            }
        }

        private void SaveFile()
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Log File|*.log";
            saveFileDialog1.Title = "Save Log File";
            saveFileDialog1.FileName = DateTime.Now.ToString().Replace(":","-").Replace("/","-");
            var c = saveFileDialog1.ShowDialog();

            // If the file name is not an empty string open it for saving.
            if ((bool)c)
            {
                using (StreamWriter sw = new StreamWriter(saveFileDialog1.FileName))
                {
                    foreach (var item in list)
                    {
                        sw.WriteLine(item.Time + " " + item.Message);
                    }
                }
                    
                
            }
        }

        private void lstLog_KeyDown(object sender, KeyEventArgs e)
        {
            Window_KeyDown(sender, e);
        }


    }
}
