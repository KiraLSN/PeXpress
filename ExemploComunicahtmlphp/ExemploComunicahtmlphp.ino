#include <WiFi.h>
#include <HTTPClient.h>
#include "heltec.h"

const int pinoSinal = 12; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal2 = 27; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal3 = 25; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal4 = 33; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal5 = 32; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal6 = 39; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal7 = 38; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal8 = 37; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
const int pinoSinal9 = 36; //PINO ANALÓGICO UTILIZADO PELO MÓDULO
int maps1, maps2, maps3, maps4, maps5, maps6, maps7, maps8, maps9;

//PARA O PÉ CHATO
String sens[] = {
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.50,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.50,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.50,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.50,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.50,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.50,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.50,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.50,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.50,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.50,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.50,0.00,0.17,-0.12,1.09",
  };
// PARA O PÉ NORMAL
  String sens2[] = {
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.00,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.00,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.00,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.00,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.00,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.00,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.00,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.00,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.00,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.00,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.00,0.00,0.17,-0.12,1.09",
  };
// PARA O PÉ PRONADO
  String sens3[] = {
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.80,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.80,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.80,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.80,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.80,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,1.80,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,1.80,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,1.80,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.80,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,1.80,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,1.80,0.00,0.17,-0.12,1.09",
  };
//PARA O PÉ SUPINADO
  String sens4[] = {
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,0.00,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,0.00,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,0.00,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.00,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.00,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,0.00,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,0.00,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,0.00,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.00,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.00,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.00,0.00,0.17,-0.12,1.09",
  };
// PARA O PÉ CAVO
  String sens5[] = {
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,0.50,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,0.50,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,0.50,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.50,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.50,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,2.59,2.88,2.00,0.00,0.50,0.00,0.43,0.70,2.23",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.63,1.81,1.51,0.59,0.50,0.00,0.17,-0.12,1.08",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.42,1.71,0.50,0.44,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.50,0.45,-0.23,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.54,0.43,1.71,0.50,0.44,-0.24,0.27,1.11",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.79,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  "?sensor=0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,1.62,1.80,1.51,0.59,0.50,0.00,0.17,-0.12,1.09",
  };

//int pinoPOT = 37;
int brilho;

const int freq = 5000;


WiFiServer server(80);
const String WIFI = "CLARO_2G663E5C";
const char WIFI_SSID[] = "CLARO_2G663E5C";
const char WIFI_PASSWORD[] = "7D663E5C";



String HOST_NAME = "http://192.168.0.222"; // Vai ser o IP do servidor de PHP
String PATH_NAME   = "/testesp/insert_temp.php"; //Caminho do arquivo que irá guardar as informações no banco de dados
String queryString = "?temperature=29.1"; // String que vai passar todos os dados coletados na ESP32 para o banco de dados

String IPAddress2String(IPAddress address)
{
 return String(address[0]) + "." + 
        String(address[1]) + "." + 
        String(address[2]) + "." + 
        String(address[3]);
}

void setup() {
  pinMode(pinoSinal, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal2, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal3, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal4, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal5, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal6, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal7, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal8, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoSinal9, INPUT); //DEFINE O PINO COMO ENTRADA
  Serial.begin(115200);
  //pinMode(pinoPOT, INPUT);
  Heltec.begin(true, false, true);
   Heltec.display->setContrast(255);

   /************************COMEÇA CONEXÃO WIFI ************/
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    if(WiFi.status() == 4 || WiFi.status() == 6){
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
    delay(500);
    Serial.print(".");
    
    Heltec.display->clear();
    WiFi.status();
    Serial.println(WiFi.status());
    Serial.println(WL_CONNECTED);
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0, 0, "Desconectado");
    
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0, 25, "Tentando");
    
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(0, 45, WIFI);
   
    Heltec.display->display();
  }
/*****************************FINAL DO PROCEDIMENTO DE CONEXÃO WIFI**************/

  String ipAddress = IPAddress2String(WiFi.localIP());
  Heltec.display->clear();
  
  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(0, 0, "Conectado");
  
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 25, "IP");
  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 45, ipAddress);
 
  Heltec.display->display();
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
/*****************************INSTANCIA OBJETO DE REQUISIÇÃO HTTP****************/
  
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  server.begin(); //Iniciando o Servidor
}

void startDisplay(){
  Heltec.display->clear();
  
  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(0, 25, "Iniciado");
  
  Heltec.display->display();
}

void beginDisplay(){
  String ipAddress = IPAddress2String(WiFi.localIP());
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_24);
  Heltec.display->drawString(0, 0, "Conectado");
  
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, 25, "IP");
  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 45, ipAddress);
 
  Heltec.display->display();
}

void sendSensor(String sensores){ //MÉTODO QUE ENVIA OS SENSORES
  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + sensores); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void ReadSensor(){ //Vamos passar o indice do vetor o qual ira informar o que deve ser lido
  maps1 = map(analogRead(pinoSinal),0,4095,0,255);
  maps2 = map(analogRead(pinoSinal2),0,4095,0,255);
  maps3 = map(analogRead(pinoSinal3),0,4095,0,255);
  maps4 = map(analogRead(pinoSinal4),0,4095,0,255);
  maps5 = map(analogRead(pinoSinal5),0,4095,0,255);
  maps6 = map(analogRead(pinoSinal6),0,4095,0,255);
  maps7 = map(analogRead(pinoSinal7),0,4095,0,255);
  maps8 = map(analogRead(pinoSinal8),0,4095,0,255);
  maps9 = map(analogRead(pinoSinal9),0,4095,0,255);

  Serial.print("S01: ");
  Serial.print(maps1);
  Serial.print(" | S02: ");
  Serial.print(maps2);
  Serial.print(" | S03: ");
  Serial.print(maps3);
  Serial.print(" | S04: ");
  Serial.print(maps4);
  Serial.print(" | S05: ");
  Serial.print(maps5);
  Serial.print(" | S06: ");
  Serial.print(maps6);
  Serial.print(" | S07: ");
  Serial.print(maps7);
  Serial.print(" | S08: ");
  Serial.print(maps8);
  Serial.print(" | S09: ");
  Serial.println(maps9);
}



void loop() {
  ReadSensor();
  //Serial.println("Tentando LEr");
  beginDisplay();
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    String currentLine2 = "";
    
    while (client.connected()) {
      Serial.println(client);
      if (client.available()) {
        char c = client.read();
        
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/H\">here</a> Pe Chato<br>");
            client.print("Click <a href=\"/S\">here</a> Supinado.<br>");
            client.print("Click <a href=\"/pronado\">here</a> Pronado.<br>");
            client.print("Click <a href=\"/cavo\">here</a> cavo.<br>");
            client.print("Click <a href=\"/normal\">here</a> Normal.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          startDisplay();
          
          int cont = 0;
          //ACREDITO QUE PRECISAMOS FAZER UMA FUNÇÃO DE CALIBRAÇÃO PARA PEGAR O MAIOR VALOR MEDIDO EM CADA SENSOR E O MENOR VALOR
          //ISSO VAI SERVIR PARA PODER TIRAR UM VALOR MEDIO QUE PODE SERVIR COMO CONDICAO DE ACIONAMENTO DA FUNÇÃO QUE ESCREVE NO BANCO DE DADOS
          //DEPOIS DE CALIBRADO, MEDIR TODOS OS SENSORES INDEPENDETE E QUANDO TODOS OS SENSORES DE UM PÉ TIVEREM PASSADO POR ACIONAMENTO
          //PEGAR TODOS OS VALORES MAXIMOS MEDIDOS NO DECORRER E ENVIAR USANDO ESSA FUNÇAO DE REQUISIÇÃO HTML
          while(cont <= 20 ) { //AO INVES DE SER UM ENQUANTO, PODE SER UM IF COM O CONJUNTO DE SENSORES ACIONADOS

            ReadSensor();
            if(maps6 > 100 ){ // pé chato 14 
              cont++;
              Serial.println(sens5[(rand()%19)]);
              sendSensor(sens[(rand()%19)]);
              client.println();
              client.stop();
              
            }
            if(maps9 > 100 ){ // Pé cavo 11 
              cont++;
              Serial.println(sens5[(rand()%19)]);
              sendSensor(sens5[(rand()%19)]);
              client.println();
              client.stop();
              
            }
            if(maps4 > 100 ){ // Pé NORMAL 13
              cont++;
              Serial.println(sens2[(rand()%19)]);
              sendSensor(sens2[(rand()%19)]);
              client.println();
              client.stop();
              
            }
            if(maps8 > 100 ){ // Pé SUPINADO 17 
              cont++;
              Serial.println(sens4[(rand()%19)]);
              sendSensor(sens4[(rand()%19)]);
              client.println();
              client.stop();
              
            }
            if(maps7 > 100 ){ // Pé PRONADO 16
              cont++;
              Serial.println(sens3[(rand()%19)]);
              sendSensor(sens3[(rand()%19)]);
              client.println();
              client.stop();
              
            }
            
            
            //queryString = "?sensor="+si1+";"+si2+";"+si3+";"+si4+";"+si5+";"+si6+";"+si7+";"+si8+";"+si9+";"+si10+";"+si11+";"+si12+";"+si13+";"+si14+";"+si15+";"+si16+";"+si17+";"+si18;
            
            
            
          }
      }
    }
    }
    client.stop();
    Serial.println("Client Disconnected.");
    
  }
}
