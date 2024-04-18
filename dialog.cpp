#include "dialog.h"
#include "ui_dialog.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief main
/// \param argc
/// \param argv
/// \return 
///
#include <fstream>
#include <iostream>
using namespace std;
#include <QProcess>
#include <QFile>
#include <QDateTime>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Dialog::Dialog
/// \param parent
///
Dialog::Dialog(QWidget *parent)
     : QDialog(parent)
     , ui(new Ui::Dialog)
     {
          ui->setupUi(this);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// загрузка синапсов из файла в вектор ////////////////////////////////////////////////////////////////////////////////////////// 
   std::ifstream is2("/home/viktor/my_projects_qt_2/kartinki_iz_shriftov/papka-fonts-sort/obrez_snizu/polniy_obrez/black-white/spisok.txt");  
     std::istream_iterator<std::string> start2(is2), end2;  
     std::vector<std::string> list_of_fonts(start2, end2);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   QString stroka1=
   "magick compare -metric MAE \"/home/viktor/my_projects_qt_2/kartinki_iz_shriftov/papka-fonts-sort/obrez_snizu/polniy_obrez/black-white/";
//list_of_fonts[0]; 
QString stroka2="\" \"/home/viktor/my_projects_qt_2/kartinki_iz_shriftov/papka-fonts-sort/obrez_snizu/polniy_obrez/black-white/";
//list_of_fonts[1] ;
QString stroka3="\" null: 2>&1"; 
bool file_stiort=false;
QProcess process;
QString  stroka_vsia;
int chislo_sravneniy=0;
     long long int nachalo;
     long long int konets;
     long long int dlitelynosty;
    for (int y=0;y<1616 ; y++)  
     for (int x=y+1;x<1617 ; x++) 
    //  chislo_sravneniy++;

        {
        nachalo=QDateTime::currentMSecsSinceEpoch();
               stroka_vsia=stroka1+list_of_fonts[y].c_str()+stroka2+list_of_fonts[x].c_str()  +stroka3;
             
             
             process.start(stroka_vsia.toStdString().c_str());
    process.waitForFinished(-1); // will wait forever until finished
             QString stderr = process.readAllStandardError();
        

 std::cout << stderr.toStdString().c_str()  << std::endl; 

 if (stderr=="0 (0)")   
             {
// std::cout << "!!!!!!"<< std::endl ; // TODO: стереть файл второй
QString name_of_file="/home/viktor/my_projects_qt_2/kartinki_iz_shriftov/papka-fonts-sort/obrez_snizu/polniy_obrez/black-white/"
+QString::fromStdString(list_of_fonts[x]); // QString::fromStdString(str);
 file_stiort=QFile::remove(name_of_file);
            if (file_stiort ==true)
            std::cout << "файл "+list_of_fonts[x]+" стёрт"<< std::endl ; // TODO: стереть файл второй;
            else 
            std::cout << "файл "+list_of_fonts[x]+" не стёрт"<< std::endl ;
            
             }
             konets=QDateTime::currentMSecsSinceEpoch();
             dlitelynosty=konets-nachalo;
             std::cout << "число сравнений = "<<chislo_sravneniy<<"; длительность = "<< dlitelynosty<< std::endl ;
             
           exit(0);
          }
          
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// надо посчитать количество сравнений

     }

Dialog::~Dialog()
     {
          delete ui;
     }

