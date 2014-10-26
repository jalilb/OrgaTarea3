#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Archivo{
public:
    string nombre_de_archivo;
    Archivo(string nombre_de_archivo){
        this->nombre_de_archivo=nombre_de_archivo;
    }
};

list<Archivo*>archivos;

void menu(){
    cout<<"\tMenu\n"
    <<"1) Crea un archivo\n"
    <<"creararchivo nombre_de_archivo\n\n"
    <<"2) Lista todos los archivos creados\n"
    <<"listararchivos\n\n"
    <<"3) Modicar el contenido de un archivo\n"
    <<"modificararchivo  nombre_de_archivo 'contenido'\n\n"
    <<"4) Muestra el contenido de un archivo\n"
    <<"verarchivo nombre_de_archivo\n\n"
    <<"5) help\n\n"
    <<"6) exit\n\n";
}

void leer_lista_en_archivo(){
    ifstream in("lista_de_archivos");
    string nombre_de_archivo;
    while(in>>nombre_de_archivo){
        archivos.push_back(new Archivo(nombre_de_archivo));
    }
}

void escribir_lista_en_archivo(){
    ofstream out("lista_de_archivos");
    for(list<Archivo*>::iterator i = archivos.begin(); i!=archivos.end(); i++){
        out<<(*i)->nombre_de_archivo<<" ";
    }
    out.close();
}

bool existe(string nombre_de_archivo){
    for(list<Archivo*>::iterator i = archivos.begin(); i!=archivos.end(); i++){
        if(nombre_de_archivo==(*i)->nombre_de_archivo){
            return true;
        }
    }
    return false;
}

void creararchivo(string nombre_de_archivo){
    if(!existe(nombre_de_archivo)){
        ofstream out(nombre_de_archivo.c_str());
        archivos.push_back(new Archivo(nombre_de_archivo));
        escribir_lista_en_archivo();
    }else{
        cout<<"Error: El archivo ya existe, usa un nuevo nombre :("<<endl;
    }
}

void listararchivos(){
    for(list<Archivo*>::iterator i = archivos.begin(); i!=archivos.end(); i++){
        cout<<(*i)->nombre_de_archivo<<endl;
    }
}

void modificararchivo(string nombre_de_archivo, string contenido){
    ofstream out(nombre_de_archivo.c_str());
    if(!out.is_open()){
        cout<<"Error: El archivo "<<nombre_de_archivo<<" no existe :("<<endl;
    }
    int tam=contenido.size();
    out.write(contenido.c_str(),tam);
    out.close();
}

void verarchivo(string nombre_de_archivo){
    ifstream in(nombre_de_archivo.c_str());
    if(!in.is_open()){
        cout<<"Error: El archivo "<<nombre_de_archivo<<" no existe :("<<endl;
    }else{
        in.seekg(0,in.end);
        int tam = in.tellg();
        if(tam>0){
            in.seekg(0);
            char contenido[tam];
            in.read(contenido,tam);
            cout<<contenido<<endl;
        }else{
            cout<<"Error: El archivo esta vacio :( modificalo para que tenga informacion :D"<<endl;
        }
    }
}

bool iniciar(){
    string comando;
    cout<<"> ";
    cin>>comando;
    if(comando=="creararchivo"){
        string nombre_de_archivo;
        cin>>nombre_de_archivo;
        creararchivo(nombre_de_archivo);
        return true;
    }
    if(comando=="listararchivos"){
        listararchivos();
        return true;
    }
    if(comando=="modificararchivo"){
        string nombre_de_archivo;
        string contenido;
        cin>>nombre_de_archivo;
        getline(cin, contenido);
        modificararchivo(nombre_de_archivo,contenido);
        return true;
    }
    if(comando=="verarchivo"){
        string nombre_de_archivo;
        cin>>nombre_de_archivo;
        verarchivo(nombre_de_archivo);
        return true;
    }
    if(comando=="help"){
        menu();
        return true;
    }
    if(comando=="exit"){
        return false;
    }
    cout<<"Error: Comando no reconocido  :("<<endl;
    return true;
}

int main()
{
    leer_lista_en_archivo();
    menu();
    while(iniciar());
    return 0;
}
