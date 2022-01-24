<?php

if(isset($_GET["sensor"])) {
   $sensores = $_GET["sensor"]; 
   $vetsen = explode(",", $sensores);
   echo $sensores;
   $servername = "*******";
   $username = "******";
   $password = "********";
   $dbname = "pexpress_db";

   $certpath = "C:\\xampp\htdocs\\testesp\\DigiCertGlobalRootCA.crt";
   // Create connection
   $conn = mysqli_init();
   mysqli_ssl_set($conn, NULL, NULL, $certpath, NULL,NULL);
   //$conn = new mysqli($servername, $username, $password, $dbname,$dbport);
   // Check connection
   
   mysqli_real_connect($conn, $servername, $username, $password, $dbname,3306, NULL, MYSQLI_CLIENT_SSL);
   if (mysqli_connect_errno())
{
    die('Failed to connect to MySQL: '.mysqli_connect_error());
}
   

   $sql = "INSERT INTO tbl_sens(sens1, sens2, sens3, sens4, sens5, sens6, sens7, sens8, sens9, sens10, sens11, sens12, sens13, sens14, sens15, sens16, sens17, sens18) VALUES ($vetsen[0], $vetsen[1], $vetsen[2], $vetsen[3], $vetsen[4], $vetsen[5], $vetsen[6], $vetsen[7], $vetsen[8], $vetsen[9], $vetsen[10], $vetsen[11], $vetsen[12], $vetsen[13], $vetsen[14], $vetsen[15], $vetsen[16], $vetsen[17])";

   if ($conn->query($sql) === TRUE) {
      echo "Nova inserção no banco de dados";
   } else {
      echo "Error: " . $sql . " => " . $conn->error;
   }

   $conn->close();
} else {
   echo "Sensores não foram setados";
}
?>
