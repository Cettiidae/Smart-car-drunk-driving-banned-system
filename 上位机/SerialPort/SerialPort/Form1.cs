using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;




namespace SerialPort
{
    public partial class Form1 : Form
    {
         MYDATA[] mydata = new MYDATA[100];
        uint index=0;
        uint show_index;
        public Form1()
        {
            InitializeComponent();
            Form.CheckForIllegalCrossThreadCalls = false;
            // InitializeComponent();
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = "COM4";
                serialPort1.Open();
                this.NAME.Text = "Start";
                this.Licenseplate.Text = "Start";
                serialPort1.NewLine = "~";
            }
            catch(System.Exception ex)
            {
                NAME.Text = ex.Message;
            }
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string c;
            c = year.Text.Substring(2, 2);
            if ((!receiving)&&(serialPort1.IsOpen))
            {
                serialPort1.WriteLine("dY" + c);
                serialPort1.WriteLine("dM" + month.Text);
                serialPort1.WriteLine("dD" + day.Text);
                serialPort1.WriteLine("tH" + hour.Text);
                serialPort1.WriteLine("tM" + minute.Text);
            }
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox8_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox9_TextChanged(object sender, EventArgs e)
        {

        }

        private void close_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.Close();
                this.NAME.Text = "Closed";
                this.Licenseplate.Text = "Closed";
                Refresh();
            }

            catch (System.Exception ex)
            {
                NAME.Text = ex.Message;
            }
        }
        
        class MYDATA
        {
            public string NoData { get; set; }
            public string ConData { get; set; }
            public string BASData { get; set; }
            public string TempData { get; set; }
            public string HumiData { get; set; }
            public string YearData { get;set;}
            public string MonthData { get; set; }
            public string DayData { get; set; }
            public string HourData { get; set;}
            public string MinuteData { get; set; }
            public string SecondData { get; set; }
            public MYDATA()
            {
                NoData = "000";
                ConData = "000.00";
                BASData = "0.00";
                TempData = "00";
                HumiData = "00";
            }
            public MYDATA(string nd,string cs,string bs,string ts,string hs,string yea,string mon,string day,string min,string sec)
            {
                this.NoData = nd;
                this.ConData = cs;
                this.BASData = bs;
                this.TempData = ts;
                this.HumiData = hs;
                this.YearData = yea;
                this.MonthData = mon;
                this.DayData = day;
                this.MinuteData = min;
                this.SecondData = sec;
            }
            public void ShowData(TextBox nd, TextBox cs, TextBox bs, TextBox ts, TextBox hs,TextBox yea,TextBox mon,TextBox day,TextBox min,TextBox sec)
            {
                nd.Text = this.NoData;
                cs.Text = this.ConData;
                bs.Text = this.BASData;
                ts.Text = this.TempData;
                hs.Text = this.HumiData;
                yea.Text = this.YearData;
                mon.Text = this.MonthData;
                day.Text = this.DayData;
                min.Text = this.MinuteData;
                sec.Text = this.SecondData;
            }

        }
        
        private void serialPort1_DataReceived(object sender,System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string c = serialPort1.ReadLine();
            System.Diagnostics.Debug.WriteLine("RECEIVE " +c);//可以在调试里看到串口收到的数据
    
            if (c.Length < 2) return;
            ReceiveMessage(new MESSAGE(c));

            if(page)
            {
                No.Text = index.ToString();
                show_index = index;
                mydata[index++] = new MYDATA(NAME.Text, Concentration.Text, BAC.Text, Temperature.Text, Humidity.Text,year.Text,month.Text,day.Text,minute.Text,second.Text);
                if (index > 99) index = 0;
                page = false;
                Form1_Load(sender, e);
            }
            
             float BAC1, Num1, BAC2, Num2,data1,data2;
             if (show_index > 1)
             {
                 data1 = float.Parse(mydata[show_index - 1].BASData);
                 // data1 = TestData[index-1];
                 BAC1 = 220 - data1 * 200;
                 Num1 = show_index  * 10;

                 data2 = float.Parse(mydata[show_index].BASData);
                 //  data2 = TestData[index];
                 BAC2 = 220 - data2 * 200;
                 Num2 =( show_index+1) * 10;
                 wava.points.Add(new RectangleF(Num1, BAC1, Num2, BAC2));
                 // InitializeComponent();

                 // wava1.wava_DrawPoint(BAC1, Num1, BAC2, Num2);.

                 this.Refresh();
             }
        }

    

        struct MESSAGE
        {
            public string Type { get; set; }
            public double? Parameter { get; set; }
            public MESSAGE(string str)
                : this()
            {
                Type = str.Substring(0, 2);
                double num = 0;
                string para_string = str.Substring(2);
                if (double.TryParse(para_string, out num))
                    Parameter = num;
                else Parameter = null;
                
            }

            public string Text
            {
                get { return ""; }
                set { }
            }
        }

        double? BacData;

        bool receiving = false;
        bool page = false;
        void ReceiveMessage(MESSAGE mes)
        {
            receiving = true;
            if (mes.Type == "pN")        //No  
                // NO.Text = mes.Parameter.ToString();
            {
              //  if(mes.Parameter == 1)
               // {
                    NAME.Text = "周涛";
                    Licenseplate.Text = "苏A000000";
               // }
                //else if(mes.Parameter == 2)
               // {
               //     NO.Text = "余涛";
                //    Licenseplate.Text = "苏A666666";
               /// }
            }
                
            else if (mes.Type == "pC")   //concentration  
            {
                Concentration.Text = mes.Parameter.ToString();
                BacData = mes.Parameter * 0.00420947;
                string t = BacData.ToString();
                if (mes.Parameter == 0.0)
                    BAC.Text = "0.00";
                else
                    BAC.Text = t.Substring(0, 5);
            }

            else if (mes.Type == "pT")   //temperature
                Temperature.Text = mes.Parameter.ToString();
            else if (mes.Type == "pH")   //humidity
            {
                Humidity.Text = mes.Parameter.ToString();
                page = true;
            }
                
          /*    else if (mes.Type == "dY")   //year
            {
                year.Text = mes.Parameter.ToString().Substring(0,2);
                month.Text = mes.Parameter.ToString().Substring(2,2);
                day.Text = mes.Parameter.ToString().Substring(4,2);
            }
              year.Text = mes.Parameter.ToString();
            else if (mes.Type == "dM")   //month
                month.Text = mes.Parameter.ToString();
            else if (mes.Type == "dD")   //day
                day.Text = mes.Parameter.ToString();*/
          /*   else if (mes.Type == "tH")   //hour
            {
                hour.Text = mes.Parameter.ToString().Substring(0,2);
                minute.Text = mes.Parameter.ToString().Substring(2,2);
                page = true;
            }
             
            else if (mes.Type == "tM")   //minute
            {
                
            }*/
            receiving = false;
        }

        private void down_Click(object sender, EventArgs e)
        {
            
            if (show_index >= (index-1)) show_index = index-2;
            show_index++;
            No.Text = show_index.ToString();
            mydata[show_index].ShowData(NAME, Concentration, BAC, Temperature, Humidity,year ,month,day,minute,second);
            
        }

        private void up_Click(object sender, EventArgs e)
        {
            
            if(show_index<2) show_index = 1;
            show_index--;
            No.Text = show_index.ToString();
            mydata[show_index].ShowData(NAME, Concentration, BAC, Temperature, Humidity, year, month, day, minute, second);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void BAC_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            var time = DateTime.Now;
            /*
            mydata[show_index].YearData = year.Text = time.Year.ToString();
            mydata[show_index].MonthData = month.Text = time.Month.ToString();
            mydata[show_index].DayData = day.Text = time.Day.ToString();
            mydata[show_index].HourData = hour.Text = time.Hour.ToString();
            mydata[show_index].MinuteData = minute.Text = time.Minute.ToString();
            mydata[show_index].SecondData = second.Text = time.Second.ToString();
             * */
            year.Text = time.Year.ToString();
            month.Text = time.Month.ToString();
            day.Text = time.Day.ToString();
            hour.Text = time.Hour.ToString();
            minute.Text = time.Minute.ToString();
            second.Text = time.Second.ToString();
      //      this.reportViewer1.RefreshReport();
       //     this.reportViewer1.RefreshReport();
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
           
        }


        public float[] TestData = new float[] { 0.4f, 0.384f, 0.651f, 0.368f, 0.264f, 0.984f, 0.456f, 0.784f, 0.126f };
        private void button1_Click_1(object sender, EventArgs e)
        {
            
            float BAC1, Num1, BAC2, Num2,data1,data2;
            if(index >1)
            {
                data1 = float.Parse(mydata[show_index-1].BASData);
                data1 = TestData[index-1];
                BAC1=200- data1  * 200;
                Num1= (index - 1) * 10;

                data2 = float.Parse(mydata[show_index].BASData);
                data2 = TestData[index];
                BAC2=200- data2  * 200;
                Num2= index * 10;
                wava.points.Add(new RectangleF(Num1, BAC1, Num2, BAC2));
               // InitializeComponent();

                // wava1.wava_DrawPoint(BAC1, Num1, BAC2, Num2);.

                this.Refresh();
/*
                NAME.Text = "周涛";
                Licenseplate.Text = "苏A000000";
                No.Text = show_index.ToString();
                Concentration.Text = mydata[show_index].ConData;
                BAC.Text = mydata[show_index].BASData;
                Temperature.Text = mydata[show_index].TempData;
                Humidity.Text = mydata[show_index].HumiData;
                hour.Text = mydata[show_index].HourData;
                minute.Text = mydata[show_index].MinuteData;
                year.Text = mydata[show_index].YearData;
                month.Text = mydata[show_index].MonthData;
                day.Text = mydata[show_index].DayData;
                second.Text = mydata[show_index].SecondData;
  */
            }
           // if (index > 99) index = 1;
           // index ++;

           // Form1_Load(sender, e);
        }

  
       

        private void button2_Click_1(object sender, EventArgs e)
        {
           // a = 0;
            //Invalidate();
        }

        private void groupBox4_Paint(object sender, PaintEventArgs e)
        {
           /* if (a == 1)
            {
                Graphics g = this.CreateGraphics();
                Pen pen1 = new Pen(Color.Blue, 2);
                float y = 150, y1, x1, x2;
                for (int x = 10; x < 1100; x++)
                {
                    x1 = (float)x;
                    x2 = (float)(x + 1);
                    y1 = (float)(150 - 50 * Math.Sin((3.14159 / 180.0) * (x - 9)));
                    g.DrawLine(pen1, x1, y, x2, y1);
                    y = y1;
                }
                System.Drawing.Drawing2D.AdjustableArrowCap linecap = new System.Drawing.Drawing2D.AdjustableArrowCap(6, 6, false);
                Pen pen2 = new Pen(Color.Blue, 3);

                pen2.CustomEndCap = linecap;
                g.DrawLine(pen2, 10, 300, 10, 0);
                g.DrawLine(pen2, 10, 150, 1120, 150);
            }*/
        }

    }
}
