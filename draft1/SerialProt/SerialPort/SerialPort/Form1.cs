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
        uint index;
        uint show_index;
        public Form1()
        {
            InitializeComponent();
            Form.CheckForIllegalCrossThreadCalls = false;
            
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = "COM4";
                serialPort1.Open();
                this.NO.Text = "Start";
                this.Licenseplate.Text = "Start";
                serialPort1.NewLine = "~";
            }
            catch(System.Exception ex)
            {
                NO.Text = ex.Message;
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
                this.NO.Text = "Closed";
                this.Licenseplate.Text = "Closed";
            }

            catch (System.Exception ex)
            {
                NO.Text = ex.Message;
            }
        }
        
        class MYDATA
        {
            public string NoData { get; set; }
            public string ConData { get; set; }
            public string BASData { get; set; }
            public string TempData { get; set; }
            public string HumiData { get; set; }
            public MYDATA()
            {
                NoData = "000";
                ConData = "000.00";
                BASData = "0.00";
                TempData = "00";
                HumiData = "00";
            }
            public MYDATA(string nd,string cs,string bs,string ts,string hs)
            {
                this.NoData = nd;
                this.ConData = cs;
                this.BASData = bs;
                this.TempData = ts;
                this.HumiData = hs;
            }
            public void ShowData(TextBox nd, TextBox cs, TextBox bs, TextBox ts, TextBox hs)
            {
                nd.Text = this.NoData;
                cs.Text = this.ConData;
                bs.Text = this.BASData;
                ts.Text = this.TempData;
                hs.Text = this.HumiData;
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
                show_index = index;
                mydata[index++] = new MYDATA(NO.Text, Concentration.Text, BAC.Text, Temperature.Text, Humidity.Text);
                if (index > 99) index = 0;
                page = false;
                Form1_Load(sender, e);
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
                    NO.Text = "周涛";
                    Licenseplate.Text = "苏A00000";
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
                BacData = mes.Parameter * 0.004209470989761;
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
            
            if (show_index > (index-1)) show_index = index-2;
            show_index++;
            mydata[show_index].ShowData(NO, Concentration, BAC, Temperature, Humidity);
            
        }

        private void up_Click(object sender, EventArgs e)
        {
            
            if(show_index<2) show_index = 1;
            show_index--;
            mydata[show_index].ShowData(NO, Concentration, BAC, Temperature, Humidity);
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
            year.Text = time.Year.ToString();
            month.Text = time.Month.ToString();
            day.Text = time.Day.ToString();
            hour.Text = time.Hour.ToString();
            minute.Text = time.Minute.ToString();


        }



        

    }
}
