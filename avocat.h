#ifndef AVOCAT_H
#define AVOCAT_H
#include<QString>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Avocat
{private : QString nom,prenom,id;
public:
    QString  getnom(){return  nom;}
   QString  getprenom(){return  prenom;}
   QString  getid(){return  id;}
   Avocat();
   Avocat(QString,QString,QString);
   void setnom(QString nom){this->nom=nom; }
   void setprenom(QString prenom){this->prenom=prenom; }
   void setid(QString id){this->id=id; }
   bool ajouter();
   QSqlQueryModel * afficher();
   bool supprimer(QString);

};

#endif // AVOCAT_H