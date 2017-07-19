#ifndef POBLACION_H
#define POBLACION_H

#include "individuo.h"
#include <utility>
//#include <algorithm>

class poblacion
{
    public:
        int tam_pob;
        int tam_max_cadena;
        int cant_cadenas;
        int cant_it;
        int prob_cruz;
        int prob_mut;
        int mejor_individuo;
        vector <individuo> pob;
        pair<individuo,individuo> cruzamiento(int p1, int p2);
        friend bool comparacion(individuo a, individuo b);
        void encontrar_mejor();
    public:
        poblacion(int tama, int tam_crom, float cruz, float muta);
        void cargar_cadenas(string archivo);
        int ruleta();
        void seleccion();
        individuo busquedaEscala(individuo  &mutado);
        void ejecucion(int ite);
        void mostrar_poblacion();
};

poblacion::poblacion(int tama, int tam_cad, float cruz, float muta)
{
    tam_pob=tama;
    pob.resize(tam_pob);

    tam_max_cadena=tam_cad;
    prob_cruz=100*cruz;
    prob_mut=100*muta;
    mejor_individuo=0;
    //ctor
}

void poblacion::encontrar_mejor()
{
    int mejor=0;
    for(int i=1;i<pob.size();i++)
    {
        if(pob[i].apt > pob[mejor].apt)
        {
            mejor = i;
        }
    }
    mejor_individuo=mejor;
}

void poblacion::cargar_cadenas(string archivo)
{
    char * nombre = new char [archivo.length()+1];
    strcpy (nombre, archivo.c_str());
    ifstream Entrada(nombre);

    vector<string> cadenas;

    string cad;

    while(!Entrada.eof())
    {
        Entrada>>cad;
        cadenas.push_back(cad);
    }
    cadenas.pop_back();

    cant_cadenas=cadenas.size();

    for(int i=0;i<pob.size();i++)
    {
        pob[i] = individuo(cadenas,tam_max_cadena);
    }

    encontrar_mejor();
    //cout<<"Mejor Individuo : "<<mejor_individuo<<endl;

    Entrada.close();
}


individuo poblacion::busquedaEscala(individuo &mutado)
{
    
    int posMejor;
    int H = 6;
    vector<individuo> hijos;
    hijos.resize(H);
    int altura = 0;
    while(1)
    {
        /*cout << "\naltura: " <<altura++ << " ";

        cout << "aptitud: " <<mutado.apt << endl;*/
        for(int i = 0 ; i < H; ++i)
            hijos[i] = mutado;

        for(int i = 0 ; i < H; ++i)
        {
            srand(time(NULL)+rand());
            hijos[i].mutacion();
        }
            

        posMejor = 0;
        for(int i = 1 ; i < H; ++i)
        {
            if(hijos[i].apt > hijos[posMejor].apt)
                posMejor = i;
        }

        if(hijos[posMejor].apt < mutado.apt) break;

        mutado = hijos[posMejor];
    }
    return mutado;
}

/*pair<individuo,individuo> poblacion::cruzamiento(int p1, int p2)
{
    //cout<<"Cruzamiento"<<endl;
    pair<individuo,individuo> hijos;

    srand(time(NULL)+rand());
	int punto_cruz1 = rand() % tam_max_cadena-1;

    while(punto_cruz1 < 1)
    {
        srand(time(NULL)+rand());
    	punto_cruz1 = rand() % tam_max_cadena-1;
    }

    //cout<<"punto_cruz1 "<<punto_cruz1<<endl<<endl;

    vector<string> hijo1;
    vector<string> hijo2;

    for(int i=0;i<cant_cadenas;i++)
    {
        int letras=0;

        string h1 = pob[p1].cromosoma[i].substr(0,punto_cruz1);
        //cout<<"h1 "<<h1<<endl;

        for(int j=0;j<h1.size();j++)
        {
            if(h1[j] != '_')
            {
                letras++;
            }
        }
        //cout<<"letras "<<letras<<endl;

        int punto_cruz2=0;
        int cont=0;

        while(cont < letras)
        {
            if(pob[p2].cromosoma[i][punto_cruz2] != '_')
            {
                cont++;
            }
            punto_cruz2++;
        }
        //cout<<"punto_cruz2 "<<punto_cruz2<<endl;

        string h2 = pob[p2].cromosoma[i].substr(0,punto_cruz2);
        //cout<<"h2 "<<h2<<endl;

        h1 = h1 + pob[p2].cromosoma[i].substr(punto_cruz2,tam_max_cadena);
        h2 = h2 + pob[p1].cromosoma[i].substr(punto_cruz1,tam_max_cadena);

        while(h1.size() < tam_max_cadena)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % h1.size()-1;
            while(aleatorio < 0)
            {
                srand(time(NULL)+rand());
            	aleatorio = rand() % h1.size()-1;
            }

            h1.insert(aleatorio,"_");
        }
        while(h1.size() > tam_max_cadena)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % h1.size()-1;
            while(aleatorio < 0)
            {
                srand(time(NULL)+rand());
            	aleatorio = rand() % h1.size()-1;
            }

            if(h1[aleatorio == '_'])
            {
                h1.erase(aleatorio,1);
            }
        }

        while(h2.size() < tam_max_cadena)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % h2.size()-1;
            while(aleatorio < 0)
            {
                srand(time(NULL)+rand());
            	aleatorio = rand() % h2.size()-1;
            }

            h2.insert(aleatorio,"_");
        }
        while(h2.size() > tam_max_cadena)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % h2.size()-1;
            while(aleatorio < 0)
            {
                srand(time(NULL)+rand());
            	aleatorio = rand() % h2.size()-1;
            }

            if(h2[aleatorio == '_'])
            {
                h2.erase(aleatorio,1);
            }
        }

        //cout<<"Corregido"<<endl;
        //cout<<h1<<endl;
        //cout<<h2<<endl;
        hijo1.push_back(h1);
        hijo2.push_back(h2);

        //cout<<"----------"<<endl;
    }

    hijos.first = individuo(hijo1,tam_max_cadena);
    hijos.second = individuo(hijo2,tam_max_cadena);

    srand(time(NULL)+rand());
    int mut1 = rand() % 100;

    if(mut1 <= prob_mut)
    {
        hijos.first.mutacion();
    }

    srand(time(NULL)+rand());
    int mut2 = rand() % 100;

    if(mut2 <= prob_mut)
    {
        hijos.second.mutacion();
        hijos.second = busquedaEscala(hijos.second);
    }

    //cout<<"Hijos"<<endl<<endl;
    //hijos.first.mostrar_ind();
    //cout<<endl;
    //hijos.second.mostrar_ind();

    return hijos;
}
*/
pair<individuo,individuo> poblacion::cruzamiento(int p1, int p2)
{
    //cout<<"Cruzamiento"<<endl;
    pair<individuo,individuo> hijos;

    hijos.first = pob[p1];
    hijos.second = pob[p2];

    for(int i=0;i<cant_cadenas;i++)
    {
        if(i%2 == 0)
        {
            string aux = pob[p1].cromosoma[i];
            pob[p1].cromosoma[i] = pob[p2].cromosoma[i];
            pob[p2].cromosoma[i] = aux;
        }
    }

    srand(time(NULL)+rand());
    int mut1 = rand() % 100;

    if(mut1 <= prob_mut)
    {
        hijos.first.mutacion();
        hijos.first = busquedaEscala(hijos.first);
    }

    srand(time(NULL)+rand());
    int mut2 = rand() % 100;

    if(mut2 <= prob_mut)
    {
        hijos.second.mutacion();
        hijos.second = busquedaEscala(hijos.second);
    }

    //cout<<"Hijos"<<endl<<endl;
    //hijos.first.mostrar_ind();
    //cout<<endl;
    //hijos.second.mostrar_ind();

    return hijos;
}

int poblacion::ruleta()
{
    int aptitud_total=0;

    for(int i=0;i<pob.size();i++)
    {
        aptitud_total+=pob[i].apt;
    }

    vector <float> porcentajes(pob.size());
    for(int i=0;i<pob.size();i++)
    {
        porcentajes[i]=( (float)pob[i].apt / aptitud_total )*100;
    }
    for(int i=1;i<pob.size();i++)
    {
        porcentajes[i]+=porcentajes[i-1];
    }

    srand(time(NULL)+rand());
	int aleatorio = rand() % 100;

    int pos=0;

    while(porcentajes[pos] < aleatorio)
    {
        pos++;
    }

    return pos;
}

bool comparacion(individuo a, individuo b)
{
	return a.apt > b.apt;
}

void poblacion::seleccion()
{
	sort(pob.begin(),pob.end(),comparacion);
	pob.erase(pob.begin()+4,pob.end());
}

void poblacion::ejecucion(int ite)
{
    cant_it=ite;
    for(int i=0;i<cant_it;i++)
    {
        //cout<<"Iteracion N° "<<i<<endl;

        int padre1 = ruleta();
        int padre2 = ruleta();

        while(padre1 == padre2)
        {
            padre2 = ruleta();
        }

        pair<individuo,individuo> cruz1 = cruzamiento(padre1,padre2);

        int padre3 = ruleta();
        int padre4 = ruleta();

        while(padre3 == padre4)
        {
            padre4 = ruleta();
        }

        pair<individuo,individuo> cruz2 = cruzamiento(padre3,padre4);

        srand(time(NULL)+rand());
    	int prob_cruz1 = rand() % 100;

        if(prob_cruz1 <= prob_cruz)
        {
            pob.push_back(cruz1.first);
            pob.push_back(cruz1.second);
        }

        srand(time(NULL)+rand());
    	int prob_cruz2 = rand() % 100;

        if(prob_cruz2 <= prob_cruz)
        {
            pob.push_back(cruz2.first);
            pob.push_back(cruz2.second);
        }

        seleccion();
        encontrar_mejor();
        //cout<<"Mejor Individuo : "<<mejor_individuo<<endl;
    }

    //cout<<"Nueva Poblacion"<<endl<<endl;
    //mostrar_poblacion();
    cout<<"Mejor Individuo"<<endl;
    pob[mejor_individuo].mostrar_ind();
    cout<<"Aptitud del Mejor Individuo: "<<pob[mejor_individuo].apt<<endl;
}

void poblacion::mostrar_poblacion()
{
    for(int i=0;i<pob.size();i++)
    {
        pob[i].mostrar_ind();
        cout<<endl;
    }
}

#endif // POBLACION_H
