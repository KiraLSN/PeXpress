using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;

namespace PeXPress
{
    class Conexao
    {
        public static string serveraddress = "edivanproj.mysql.database.azure.com";
        public string conec = "SERVER=" + serveraddress + "; DATABASE=pexpress_db; UID=Luciano; PWD=rna102030#; PORT=3306";
        public MySqlConnection con = null;
        private DataSet conexaoDataset;
        public string[] vetor;
        

        public void AbrirConexao()
        {
            try
            {
                con = new MySqlConnection(conec);
                con.Open();
                Toast.MakeText(Application.Context, "Conectado com sucesso", ToastLength.Long).Show();
            }
            catch (Exception er)
            {
                Toast.MakeText(Application.Context, "Erro ao conectar" + er, ToastLength.Long).Show();
                Console.WriteLine(er);
                //throw;
            }
        }

        public void FecharConexao()
        {
            try
            {
                con = new MySqlConnection(conec);
                con.Close();
            }
            catch (Exception er)
            {
                Toast.MakeText(Application.Context, "Erro ao fechar" + er, ToastLength.Long).Show();
                //throw;
            }
        }

        public object SelectSensors()
        {
            Sensores sensores = new Sensores();
            //MySqlConnection Conexao = new MySqlConnection(conec);
            MySqlCommand Query = new MySqlCommand();
            //Query.Connection = con;
            try
            {
                Query.CommandText = @"SELECT * FROM tbl_sens ORDER BY id DESC LIMIT 1";
                MySqlDataReader dtreader = Query.ExecuteReader();//Crie um objeto do tipo reader para ler os dados do banco
                while (dtreader.Read())//Enquanto existir dados no select
                {
                    sensores.sensor1 = dtreader["sens1"].ToString();//Preencha objeto do tipo cliente com dados vindo do banco de dados
                    sensores.sensor2 = dtreader["sens2"].ToString();
                    sensores.sensor3 = dtreader["sens3"].ToString();
                    sensores.sensor4 = dtreader["sens4"].ToString();
                    sensores.sensor5 = dtreader["sens5"].ToString();
                    sensores.sensor6 = dtreader["sens6"].ToString();
                    sensores.sensor7 = dtreader["sens7"].ToString();
                    sensores.sensor8 = dtreader["sens8"].ToString();
                    sensores.sensor9 = dtreader["sens9"].ToString();
                    sensores.sensor10 = dtreader["sens10"].ToString();
                    sensores.sensor11 = dtreader["sens11"].ToString();
                    sensores.sensor12 = dtreader["sens12"].ToString();
                    sensores.sensor13 = dtreader["sens13"].ToString();
                    sensores.sensor14 = dtreader["sens14"].ToString();
                    sensores.sensor15 = dtreader["sens15"].ToString();
                    sensores.sensor16 = dtreader["sens16"].ToString();
                    sensores.sensor17 = dtreader["sens17"].ToString();
                    sensores.sensor18 = dtreader["sens18"].ToString();
                }
                Toast.MakeText(Application.Context, sensores.sensor1, ToastLength.Long).Show();
            }
            catch(Exception er)
            {
                Toast.MakeText(Application.Context, "Erro: " +er, ToastLength.Long).Show();
            }
            

            

            
            

            return sensores;
        }
    }

    
}