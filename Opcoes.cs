using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AndroidX.AppCompat.Widget;
using AndroidX.AppCompat.App;
using Google.Android.Material.FloatingActionButton;
using Google.Android.Material.Snackbar;
using Android.Content;
using Java.IO;
using AndroidX.Core.Content;
using Environment = Android.OS.Environment;
using System.IO;

namespace PeXPress
{
    //[Activity(Label = "Opcoes")]
    [Activity(Label = "Opções", Theme = "@style/AppTheme.NoActionBar", MainLauncher = false)]
    public class Opcoes : Activity
    {
        string[] configuracoes;
        string ipAdress;
        string passos;
        string peso;

        [Obsolete]
        protected override void OnCreate(Bundle savedInstanceState)
        {
            
            base.OnCreate(savedInstanceState);
            
            SetContentView(Resource.Layout.opcoes);

            // Create your application here
            //AppCompatButton button2 = FindViewById<AppCompatButton>(Resource.Id.button);
            //Button btnSalvar = FindViewById<AppCompatButton>(Resource.Id.button1);
            //button2.Click += Button_Click; 
            AppCompatButton button = FindViewById<AppCompatButton>(Resource.Id.appCompatButton1);
             button = FindViewById<AppCompatButton>(Resource.Id.appCompatButton1);
            button.Click += Button_Click;

            AutoCompleteTextView textBox1 = FindViewById<AutoCompleteTextView>(Resource.Id.autoCompleteTextView1);
            AutoCompleteTextView textBox3 = FindViewById<AutoCompleteTextView>(Resource.Id.autoCompleteTextView2);
            MultiAutoCompleteTextView textBox2 = FindViewById<MultiAutoCompleteTextView>(Resource.Id.multiAutoCompleteTextView1);

            try
            {
                string pasta = Environment.ExternalStorageDirectory.AbsolutePath;
                string localizacao = Path.Combine(pasta, "Documents/config.txt");

                StreamReader arquivo = new StreamReader(localizacao);
                string config = arquivo.ReadLine();
                configuracoes = config.Split(";");
                ipAdress = configuracoes[0];
                passos = configuracoes[1];
                peso = configuracoes[2];
                textBox1.Text = ipAdress;
                textBox2.Text = passos;
                textBox3.Text = peso;

                arquivo.Dispose();
                //QUALQUER COISA APAGA ESSA LINHA AQUI EM BAIXO
                Android.Widget.Toast.MakeText(this, "Lido no arquivo " + config, Android.Widget.ToastLength.Short).Show();
            }
            catch (Exception er)
            {
                Android.Widget.Toast.MakeText(this, "Necessário configurar o IP da ESP", Android.Widget.ToastLength.Short).Show();
            }

        }

        [Obsolete]
        private void Button_Click(object sender, EventArgs e)
        {

            AutoCompleteTextView textView1 = FindViewById<AutoCompleteTextView>(Resource.Id.autoCompleteTextView1);
            MultiAutoCompleteTextView textView2 = FindViewById<MultiAutoCompleteTextView>(Resource.Id.multiAutoCompleteTextView1);
            AutoCompleteTextView textView3 = FindViewById<AutoCompleteTextView>(Resource.Id.autoCompleteTextView2);
            var sdCardPath = Android.OS.Environment.ExternalStorageDirectory.Path;
            var arquivoPath = System.IO.Path.Combine(sdCardPath, "Documents/config.txt");
            if (!System.IO.File.Exists(arquivoPath))
            {
                if (textView1.Text.Length > 8 && textView2.Text.Length>0 && textView3.Text.Length>0)
                {

                    string ip = textView1.Text;
                    string passos = textView2.Text;
                    string peso = textView3.Text;

                    string pasta = Environment.ExternalStorageDirectory.AbsolutePath;
                    string localizacao = Path.Combine(pasta, "Documents/config.txt");

                    Toast.MakeText(this, "Configurações Salvas Com Sucesso " , ToastLength.Short).Show();
                    StreamWriter folder = new StreamWriter(localizacao, false);
                    folder.WriteLine(ip+";"+passos+";"+peso);
                    folder.Dispose();
                    OnBackPressed();
                }
                else
                {
                    Toast.MakeText(this, "Favor preencher todos os campos devidamente", ToastLength.Short).Show();
                }
                
                //using (System.IO.StreamWriter writer = new System.IO.StreamWriter(arquivoPath, true))
                //{
                //  writer.Write("Teste");
                // Toast.MakeText(this, "Arquivo " + arquivoPath.ToString() + " gerado com sucesso.", ToastLength.Short).Show();
                //}
            }
            else
            {
                if (textView1.Text.Length > 8 && textView2.Text.Length > 0 && textView3.Text.Length > 0)
                {
                    string pasta = Environment.ExternalStorageDirectory.AbsolutePath;
                    string localizacao = Path.Combine(pasta, "Documents/config.txt");



                    string ip = textView1.Text;
                    string passos = textView2.Text;
                    string peso = textView3.Text;

                    Toast.MakeText(this, "Arquivo " + pasta + " Salvo com sucesso.", ToastLength.Short).Show();
                    StreamWriter folder = new StreamWriter(localizacao, false);
                    folder.WriteLine(ip + ";" + passos + ";" + peso);
                    folder.Dispose();
                }
                else
                {
                    Toast.MakeText(this, "Favor preencher todos os campos devidamente", ToastLength.Short).Show();
                }
            }
        }
    }
}