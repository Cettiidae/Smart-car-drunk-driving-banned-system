using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SerialPort
{
    public partial class wava : UserControl
    {
       public static float  x1 = 0,y1 = 0;
       public static float  x2 = 0,y2 = 0;
       public static List<RectangleF> points = new List<RectangleF>();
       public  Pen pen1 = new Pen(Color.Red, 2);
       public  Pen pen2 = new Pen(Color.Blue, 3);
        public wava()
        {
            InitializeComponent();
            SetStyle(ControlStyles.UserPaint, true);
            
            
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);//防止闪烁

           
        }

        private void wava_Paint(object sender, PaintEventArgs e)
        {
           Graphics g = e.Graphics;

           foreach (var rect in points)
           {
               x1 = rect.X;
               y1 = rect.Y;
               x2 = rect.Width;
               y2 = rect.Height;
               g.DrawLine(pen1, (int)x1, (int)y1, (int)x2, (int)y2);
           }
           
           
              g.DrawLine(pen2, 30, 220, 30, 217);
              g.DrawLine(pen2, 40, 220, 40, 217);
              g.DrawLine(pen2, 50, 220, 50, 217);
              g.DrawLine(pen2, 60, 220, 60, 217);
              g.DrawLine(pen2, 70, 220, 70, 215);
              g.DrawLine(pen2, 80, 220, 80, 217);
              g.DrawLine(pen2, 90, 220, 90, 217);
              g.DrawLine(pen2, 100, 220, 100, 217);
              g.DrawLine(pen2, 110, 220, 110, 217);
              g.DrawLine(pen2, 120, 220, 120, 215);
              g.DrawLine(pen2, 130, 220, 130, 217);
              g.DrawLine(pen2, 140, 220, 140, 217);
              g.DrawLine(pen2, 150, 220, 150, 217);
              g.DrawLine(pen2, 160, 220, 160, 217);
              g.DrawLine(pen2, 170, 220, 170, 215);
              g.DrawLine(pen2, 180, 220, 180, 217);
              g.DrawLine(pen2, 190, 220, 190, 217);
              g.DrawLine(pen2, 200, 220, 200, 217);
              g.DrawLine(pen2, 210, 220, 210, 217);
              g.DrawLine(pen2, 220, 220, 220, 215);
              g.DrawLine(pen2, 230, 220, 230, 217);



              g.DrawLine(pen2, 20, 60, 25, 60);
              g.DrawLine(pen2, 20, 140, 25, 140);
              System.Drawing.Drawing2D.AdjustableArrowCap linecap = new System.Drawing.Drawing2D.AdjustableArrowCap(6, 6, false);
              // Pen pen2 = new Pen(Color.Blue, 3);
             // pen2.CustomEndCap = linecap;
              g.DrawLine(pen2, 20, 220, 20, 0);
              g.DrawLine(pen2, 20, 220, 250, 220);

              g.DrawLine(pen2, 20, 0, 10, 10);
              g.DrawLine(pen2, 20, 0, 30, 10);
              g.DrawLine(pen2, 250, 220, 240, 210);
              g.DrawLine(pen2, 250, 220, 240, 230);

              Font fnt = new Font("Verdana", 6);
              g.DrawString("0.8", fnt, new SolidBrush(Color.Black), 0, 60);
              g.DrawString("0.4", fnt, new SolidBrush(Color.Black), 0, 140);
              g.DrawString("5", fnt, new SolidBrush(Color.Black), 70, 230);
              g.DrawString("10", fnt, new SolidBrush(Color.Black), 120, 230);
              g.DrawString("15", fnt, new SolidBrush(Color.Black), 170, 230);
           
           
        }
        
    }
}
