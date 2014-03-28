using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml;
using System.Xml.Linq;

namespace TT_FFX_Butterfly.classes
{
    class XMLManager
    {
        public string Path { set; get;}

        public XMLManager() { this.Path = null; }
        public XMLManager(string path) { this.Path = path; }

        public List<DirectionPoint> Reader()
        {
            if (this.Path != null)
            {
                return Reader(this.Path);
            }
            else
            {
                MessageBox.Show("Error: select a valid path");
            }
            return null;
        }
        public List<DirectionPoint> Reader(string path)
        {
            List<DirectionPoint> list = new List<DirectionPoint>();
            DirectionPoint point;
            using (XmlReader reader = XmlReader.Create(path))
            {

                // Parse the file and display each of the nodes.
                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.EndElement) { continue; }
                    if(reader.LocalName == "position"){
                        XElement el = XNode.ReadFrom(reader) as XElement;
                        double x, y;
                        var tmp = el.Value.Split(';');
                        x = Convert.ToDouble(tmp.First());
                        y = Convert.ToDouble(tmp.Last());
                        point = new DirectionPoint();
                        point.isButteFly = false;
                        point.point = DirectionPoint.ARROW.NOPE;
                        point.position = new Vector(x,y);
                        list.Add(point);
                    }

                    if (reader.LocalName == "point")
                    {
                        XElement el = XNode.ReadFrom(reader) as XElement;
                        point = new DirectionPoint();
                        point.isButteFly = false;
                        if (el.HasAttributes)
                        {
                            if (el.FirstAttribute.Value == "true")
                            {
                                point.isButteFly = true;
                            }
                        }
                        point.point = getArrow(el.Value);
                        list.Add(point);
                    }
                    
                }
            }
            return list;
        }

        private DirectionPoint.ARROW getArrow(string p)
        {
            int xmlValue = Convert.ToInt32(p);
            DirectionPoint.ARROW o = DirectionPoint.ARROW.NOPE;
            if ((xmlValue & (int)DirectionPoint.ARROW.UP) > 0)
            {
                o |= DirectionPoint.ARROW.UP;
            }
            if ((xmlValue & (int)DirectionPoint.ARROW.DOWN) > 0)
            {
                o |= DirectionPoint.ARROW.DOWN;
            }
            if ((xmlValue & (int)DirectionPoint.ARROW.LEFT) > 0)
            {
                o |= DirectionPoint.ARROW.LEFT;
            }
            if ((xmlValue & (int)DirectionPoint.ARROW.RIGHT) > 0)
            {
                o |= DirectionPoint.ARROW.RIGHT;
            }
            return o;
        }

    }
}
