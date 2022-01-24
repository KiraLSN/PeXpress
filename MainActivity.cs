using System;
using Android.App;
using Android.OS;
using Android.Runtime;
using Android.Views;
using AndroidX.AppCompat.Widget;
using AndroidX.AppCompat.App;
using Google.Android.Material.FloatingActionButton;
using Google.Android.Material.Snackbar;
using System.Collections.Generic;
using Java.Util;
using Android.Content;
using Environment = Android.OS.Environment;
using System.IO;
using Timer = System.Timers.Timer;
using MySql.Data.MySqlClient;
using System.Net;
using System.Net.NetworkInformation;
using System.Threading;
using System.Threading.Tasks;

namespace PeXPress
{
    [Activity(Label = "@string/app_name", Theme = "@style/AppTheme.NoActionBar", MainLauncher = true)]
    
    public class MainActivity : AppCompatActivity
    {

        

        string[] configuracoes;
        string ipAdress = "";
        string passos = "";
        string peso = "";
        public string sensor01;
        public string sensor02;
        public string sensor03;
        public string sensor04;
        public string sensor05;
        public string sensor06;
        public string sensor07;
        public string sensor08;
        public string sensor09;
        public string sensor10;
        public string sensor11;
        public string sensor12;
        public string sensor13;
        public string sensor14;
        public string sensor15;
        public string sensor16;
        public string sensor17;
        public string sensor18;
        public string erro = "";
        public bool trfunc = false;
        public bool feets = false;
        public int passadas = 0;
        Timer timer = null;
        int cont;
        Sensores sens = new Sensores();


        
        
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);
            Xamarin.Essentials.Platform.Init(this, savedInstanceState);
            SetContentView(Resource.Layout.activity_main);
            
            //SetContentView(Resource.Layout.content_main);

            Toolbar toolbar = FindViewById<Toolbar>(Resource.Id.toolbar);
            SetSupportActionBar(toolbar);

            

            AppCompatButton button = FindViewById<AppCompatButton>(Resource.Id.button1);
            button.Click += Button_Click;

            try
            {
                string pasta = Environment.ExternalStorageDirectory.AbsolutePath;
                string localizacao = Path.Combine(pasta, "Documents/config.txt");

                StreamReader arquivo = new StreamReader(localizacao);
                string config = arquivo.ReadLine();
                arquivo.Dispose();
                configuracoes = config.Split(";");
                ipAdress = configuracoes[0];
                passos = configuracoes[1];
                peso = configuracoes[2];
                
                Android.Widget.Toast.MakeText(this, "Lido no arquivo " + config, Android.Widget.ToastLength.Short).Show();
            } catch(Exception er)
            {
                Android.Widget.Toast.MakeText(this, "Necessário configurar o IP da ESP" + er, Android.Widget.ToastLength.Short).Show();
            }
            
        }

        protected override void OnRestart()
        {
            base.OnRestart();
            try
            {
                string pasta = Environment.ExternalStorageDirectory.AbsolutePath;
                string localizacao = Path.Combine(pasta, "Documents/config.txt");

                StreamReader arquivo = new StreamReader(localizacao);
                string config = arquivo.ReadLine();
                arquivo.Dispose();
                configuracoes = config.Split(";");
                ipAdress = configuracoes[0];
                passos = configuracoes[1];
                peso = configuracoes[2];

                Android.Widget.Toast.MakeText(this, "Lido no arquivo " + config, Android.Widget.ToastLength.Short).Show();
            }
            catch (Exception er)
            {
                Android.Widget.Toast.MakeText(this, "Necessário configurar o IP da ESP" + er, Android.Widget.ToastLength.Short).Show();
            }
        }

        private void Button_Click(object sender, EventArgs e)
        {
            bool problema = false;
            
            
            Thread t = new Thread(new ThreadStart(IniciaESP));
            Android.Widget.ImageView imagem = FindViewById<Android.Widget.ImageView>(Resource.Id.imageView1);
            Android.Widget.TextView pass = FindViewById<Android.Widget.TextView>(Resource.Id.Passos);
            Android.Widget.TextView titulo = FindViewById<Android.Widget.TextView>(Resource.Id.textView54);


            AppCompatButton button = FindViewById<AppCompatButton>(Resource.Id.button1);

            if (ipAdress.Length < 2 || passos.Length < 1 || peso.Length < 1)
            {
                var opcoes = new Intent(this, typeof(Opcoes));
                StartActivity(opcoes);
            }
            else
            {
                Ping ping = new Ping();
                PingReply r;
                try
                {
                    r = ping.Send(ipAdress);
                    if(r.Status == IPStatus.Success)
                    {
                        problema = false;
                    }
                    else
                    {
                        Android.Widget.Toast.MakeText(Application.Context, "Falha na comunicação com a ESP. Verifique o endereço '" + r.Status + "'", Android.Widget.ToastLength.Long).Show();
                        problema = true;
                    }
                }catch(Exception er)
                {
                    Android.Widget.Toast.MakeText(Application.Context, "ESP não encontrada. Verifique o IP  '" + IPStatus.Success + "'", Android.Widget.ToastLength.Long).Show();
                }

                
                if (button.Text == "Iniciar" && problema == false)
                {
                    WebRequest request = WebRequest.Create("http://" + ipAdress + "/H");
                    request.Method = "GET";
                    feets = false;
                    try
                    {
                        trfunc = true;
                        string serveraddress = "edivanproj.mysql.database.azure.com";
                        string conec = "SERVER=" + serveraddress + "; DATABASE=pexpress_db; UID=Luciano; PWD=rna102030#; PORT=3306";
                        MySqlConnection con = null;
                        con = new MySqlConnection(conec);
                        MySqlCommand Query = new MySqlCommand();
                        Query.Connection = con;
                        con.Open();

                        Query.CommandText = @"TRUNCATE TABLE tbl_sens;";
                        Query.ExecuteNonQuery();
                        con.Close();

                        WebResponse response = request.GetResponse();
                        button.Text = "Parar";
                        t.Start();
                        
                        timer = new Timer();
                        timer.Interval = 50;
                        timer.Elapsed += Timer_Elapsed;
                        timer.Start(); 
                        
                    }
                    catch (Exception er)
                    {
                        //Android.Widget.Toast.MakeText(Application.Context, "Não conectou a ESP '" + er + "'", Android.Widget.ToastLength.Long).Show();
                        WebRequest request2 = WebRequest.Create("http://" + ipAdress + "/sair");
                        request2.Method = "GET";
                        trfunc = true;
                        problema = false;
                        button.Text = "Parar";
                        t.Start();
                        
                        timer = new Timer();
                        timer.Interval = 50;
                        timer.Elapsed += Timer_Elapsed;
                        timer.Start();

                    }
                    
                }
                else
                {
                    if (button.Text == "Finalizar")
                    {
                        WebRequest request2 = WebRequest.Create("http://" + ipAdress + "/sair");
                        request2.Method = "GET";
                        button.Text = "Iniciar";
                        imagem.SetImageResource(Resource.Drawable.pes);
                        pass.Text = "0";
                        titulo.Text = "";
                        while (trfunc == true)
                        {
                            Android.Widget.Toast.MakeText(Application.Context, "Aguardando fim da Thread", Android.Widget.ToastLength.Long).Show();
                        }
                        t.Abort();
                    }
                    else
                    {
                        Android.Widget.Toast.MakeText(Application.Context, "Não encontrou a ESP. Verifique o endereço '" + ipAdress + "'", Android.Widget.ToastLength.Long).Show();
                        button.Text = "Iniciar";
                        //MAS PRECISA DE UMA VARIAVEL PARA FAZER FUNCIONAR O THREAD SLEEP DENTRO DA THREAD
                        //E FAZER UM WHILE PARA ESPERAR O THREADSLEEP PARA FAZER O THREAD ABORT
                        
                    }
                    
                    //con.Close();
                }
            }
           


        }

        public void IniciaESP()
        {
            
            while (true)
            {
                string serveraddress = "edivanproj.mysql.database.azure.com";
                string conec = "SERVER=" + serveraddress + "; DATABASE=pexpress_db; UID=Luciano; PWD=rna102030#; PORT=3306";
                MySqlConnection con = null;
                con = new MySqlConnection(conec);
                MySqlCommand Query = new MySqlCommand();
                Query.Connection = con;
                try
                {
                    con.Open();

                    Query.CommandText = @"SELECT * FROM tbl_sens ORDER BY id DESC LIMIT 1";
                    MySqlDataReader dtreader = Query.ExecuteReader();//Crie um objeto do tipo reader para ler os dados do banco
                    while (dtreader.Read())//Enquanto existir dados no select
                    {
                        passadas = Convert.ToInt32(dtreader["id"]);
                        sensor01 = dtreader["sens1"].ToString();
                        sensor02 = dtreader["sens2"].ToString();
                        sensor03 = dtreader["sens3"].ToString();
                        sensor04 = dtreader["sens4"].ToString();
                        sensor05 = dtreader["sens5"].ToString();
                        sensor06 = dtreader["sens6"].ToString();
                        sensor07 = dtreader["sens7"].ToString();
                        sensor08 = dtreader["sens8"].ToString();
                        sensor09 = dtreader["sens9"].ToString();
                        sensor10 = dtreader["sens10"].ToString();//Preencha objeto do tipo cliente com dados vindo do banco de dados
                        sensor11 = dtreader["sens11"].ToString();
                        sensor12 = dtreader["sens12"].ToString();
                        sensor13 = dtreader["sens13"].ToString();
                        sensor14 = dtreader["sens14"].ToString();
                        sensor15 = dtreader["sens15"].ToString();
                        sensor16 = dtreader["sens16"].ToString();
                        sensor17 = dtreader["sens17"].ToString();
                        sensor18 = dtreader["sens18"].ToString();

                    }
                    con.Close();
                    if (passadas >= Convert.ToInt32(passos))
                    {
                        feets = true;
                        trfunc = false;
                        Thread.Sleep(Timeout.Infinite);
                        
                    }
                }
                catch(Exception er)
                {
                    erro = "Erro de: " + er;
                }

                if(trfunc == false)
                {
                    Thread.Sleep(Timeout.Infinite);
                    
                }
                
            }
            
        }
        private void Timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            
            Android.Widget.TextView sen01 = FindViewById<Android.Widget.TextView>(Resource.Id.textS1);
            Android.Widget.TextView sen02 = FindViewById<Android.Widget.TextView>(Resource.Id.textS2);
            Android.Widget.TextView sen03 = FindViewById<Android.Widget.TextView>(Resource.Id.textS3);
            Android.Widget.TextView sen04 = FindViewById<Android.Widget.TextView>(Resource.Id.textS4);
            Android.Widget.TextView sen05 = FindViewById<Android.Widget.TextView>(Resource.Id.textS5);
            Android.Widget.TextView sen06 = FindViewById<Android.Widget.TextView>(Resource.Id.textS6);
            Android.Widget.TextView sen07 = FindViewById<Android.Widget.TextView>(Resource.Id.textS7);
            Android.Widget.TextView sen08 = FindViewById<Android.Widget.TextView>(Resource.Id.textS8);
            Android.Widget.TextView sen09 = FindViewById<Android.Widget.TextView>(Resource.Id.textS9);
            Android.Widget.TextView sen10 = FindViewById<Android.Widget.TextView>(Resource.Id.textS10);
            Android.Widget.TextView sen11 = FindViewById<Android.Widget.TextView>(Resource.Id.textS11);
            Android.Widget.TextView sen12 = FindViewById<Android.Widget.TextView>(Resource.Id.textS12);
            Android.Widget.TextView sen13 = FindViewById<Android.Widget.TextView>(Resource.Id.textS13);
            Android.Widget.TextView sen14 = FindViewById<Android.Widget.TextView>(Resource.Id.textS14);
            Android.Widget.TextView sen15 = FindViewById<Android.Widget.TextView>(Resource.Id.textS15);
            Android.Widget.TextView sen16 = FindViewById<Android.Widget.TextView>(Resource.Id.textS16);
            Android.Widget.TextView sen17 = FindViewById<Android.Widget.TextView>(Resource.Id.textS17);
            Android.Widget.TextView sen18 = FindViewById<Android.Widget.TextView>(Resource.Id.textS18);
            Android.Widget.TextView pass = FindViewById<Android.Widget.TextView>(Resource.Id.Passos);
            
                sen01.Text = sensor01;
                sen02.Text = sensor02;
                sen03.Text = sensor03;
                sen04.Text = sensor04;
                sen05.Text = sensor05;
                sen06.Text = sensor06;
                sen07.Text = sensor07;
                sen08.Text = sensor08;
                sen09.Text = sensor09;
                sen10.Text = sensor10;//Preencha objeto do tipo cliente com dados vindo do banco de dados
                sen11.Text = sensor11;
                sen12.Text = sensor12;
                sen13.Text = sensor13;
                sen14.Text = sensor14;
                sen15.Text = sensor15;
                sen16.Text = sensor16;
                sen17.Text = sensor17;
                sen18.Text = sensor18;
                pass.Text = passadas.ToString();

            

            if(feets == true)
            {
                timer.Stop();
                timer.Dispose();
                timer.Enabled = false;
                MostraResultado();
            }

            if(erro.Length > 1)
            {
                Android.Widget.Toast.MakeText(Application.Context, erro, Android.Widget.ToastLength.Long).Show();
            }
            
           
            
            //sen11.Text = Convert.ToString(sens02);

            //sen11.Text = Convert.ToString(sens01);

            //con.Close();
        }

        public void MostraResultado()
        {
            AppCompatButton button = FindViewById<AppCompatButton>(Resource.Id.button1);
            Android.Widget.TextView titulo = FindViewById<Android.Widget.TextView>(Resource.Id.textView54);
            Android.Widget.ImageView imagem = FindViewById<Android.Widget.ImageView>(Resource.Id.imageView1);

            button.Text = "Finalizar";

            string serveraddress = "edivanproj.mysql.database.azure.com";
            string conec = "SERVER=" + serveraddress + "; DATABASE=pexpress_db; UID=Luciano; PWD=rna102030#; PORT=3306";
            MySqlConnection con = null;
            con = new MySqlConnection(conec);
            MySqlCommand Query = new MySqlCommand();
            Query.Connection = con;
            try
            {
                con.Open();

                Query.CommandText = @"SELECT * FROM tbl_sens ORDER BY id DESC LIMIT 1";
                MySqlDataReader dtreader = Query.ExecuteReader();//Crie um objeto do tipo reader para ler os dados do banco
                while (dtreader.Read())//Enquanto existir dados no select
                {
                    passadas = Convert.ToInt32(dtreader["id"]);
                    sensor01 = dtreader["sens1"].ToString();
                    sensor02 = dtreader["sens2"].ToString();
                    sensor03 = dtreader["sens3"].ToString();
                    sensor04 = dtreader["sens4"].ToString();
                    sensor05 = dtreader["sens5"].ToString();
                    sensor06 = dtreader["sens6"].ToString();
                    sensor07 = dtreader["sens7"].ToString();
                    sensor08 = dtreader["sens8"].ToString();
                    sensor09 = dtreader["sens9"].ToString();
                    sensor10 = dtreader["sens10"].ToString();//Preencha objeto do tipo cliente com dados vindo do banco de dados
                    sensor11 = dtreader["sens11"].ToString();
                    sensor12 = dtreader["sens12"].ToString();
                    sensor13 = dtreader["sens13"].ToString();
                    sensor14 = dtreader["sens14"].ToString();
                    sensor15 = dtreader["sens15"].ToString();
                    sensor16 = dtreader["sens16"].ToString();
                    sensor17 = dtreader["sens17"].ToString();
                    sensor18 = dtreader["sens18"].ToString();

                }
                con.Close();


                
            }
            catch(Exception er)
            {

            }
            if (Convert.ToInt32(peso) > 80 && Convert.ToInt32(peso) <= 85)
            {
                if (peso == "81")
                {

                    titulo.Text = "Pé Supinado";

                    imagem.SetImageResource(Resource.Drawable.esupinado);
                }

                if (peso == "82")
                {

                    titulo.Text = "Pé Chato";
                    imagem.SetImageResource(Resource.Drawable.echato);
                }

                if (peso == "83")
                {
                    titulo.Text = "Pé Cavo";

                    imagem.SetImageResource(Resource.Drawable.ecavo);
                }
                if (peso == "84")
                {
                    titulo.Text = "Pé Normal";

                    imagem.SetImageResource(Resource.Drawable.enormal);
                }
                if (peso == "85")
                {
                    titulo.Text = "Pé Pronado";

                    imagem.SetImageResource(Resource.Drawable.epronado);
                }
            }
            else
            {
                if (sensor14 == "0")
                {

                    titulo.Text = "Pé Supinado";

                    imagem.SetImageResource(Resource.Drawable.esupinado);
                }

                if (sensor14 == "1,5")
                {

                    titulo.Text = "Pé Chato";
                    imagem.SetImageResource(Resource.Drawable.echato);
                }

                if (sensor14 == "0,5")
                {
                    titulo.Text = "Pé Cavo";

                    imagem.SetImageResource(Resource.Drawable.ecavo);
                }
                if (sensor14 == "1")
                {
                    titulo.Text = "Pé Normal";

                    imagem.SetImageResource(Resource.Drawable.enormal);
                }
                if (sensor14 == "1,8")
                {
                    titulo.Text = "Pé Pronado";

                    imagem.SetImageResource(Resource.Drawable.epronado);
                }
            }
            

        }
       

        public override bool OnCreateOptionsMenu(IMenu menu)
        {
            MenuInflater.Inflate(Resource.Menu.menu_main, menu);

            return true;
        }

        

        public override bool OnOptionsItemSelected(IMenuItem item)
        {
            int id = item.ItemId;
            if (id == Resource.Id.action_settings)
            {


                var opcoes = new Intent(this, typeof(Opcoes));
                StartActivity(opcoes);
                return true;
            }

            return base.OnOptionsItemSelected(item);
        }


        public override void OnRequestPermissionsResult(int requestCode, string[] permissions, [GeneratedEnum] Android.Content.PM.Permission[] grantResults)
        {
            Xamarin.Essentials.Platform.OnRequestPermissionsResult(requestCode, permissions, grantResults);

            base.OnRequestPermissionsResult(requestCode, permissions, grantResults);
        }
	}
}
