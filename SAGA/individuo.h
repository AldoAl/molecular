#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

class individuo
{
    public:
        vector <string> cromosoma;
        int tam_max;
        int apt;
        void aptitud();
        individuo();
        individuo(vector <string> cadenas, int tam);
        void mutacion();
        void mostrar_ind();
};

individuo::individuo()
{
}

individuo::individuo(vector <string> cadenas, int tam)
{
    cromosoma = cadenas;
    tam_max = tam;//mejorar condicion

    //for(int i=0;i<cromosoma.size();i++)
    //    cout<<cromosoma[i]<<endl;

    for(int i=0;i<cromosoma.size();i++)
    {
        while(cromosoma[i].size() < tam_max)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % cromosoma[i].size();

            cromosoma[i].insert(aleatorio,"_");
        }
    }

    aptitud();
    //ctor
}

void individuo::aptitud()
{
    apt=0;

	for(int i=0;i<tam_max;i++)
	{
        int cont2 = 0;
		for(int j=0;j<cromosoma.size();j++)
        {
            for(int k=j;k<cromosoma.size();k++)
            {
                if(j != k)
                {
                    if(cromosoma[j][i] == '_' || cromosoma[k][i] == '_')
                    {
                        cont2 += 0;//espacio en blanco
                    }
                    else
                    {
                        if(cromosoma[j][i] == cromosoma[k][i])
                        {
                            cont2 += 3;//match
                        }
                        else
                        {
                            cont2 += 1;//missmatch
                        }
                    }
                }

            }
        }
        apt += cont2;
	}
}

void individuo::mutacion()
{
    for(int i=0;i<cromosoma.size();i++)
    {
        for(int j=cromosoma[i].size()-1;j>=0;j--)
        {
            if(cromosoma[i][j] == '_')
            {
                cromosoma[i].erase(j,1);
            }
        }
    }

    for(int i=0;i<cromosoma.size();i++)
    {
        while(cromosoma[i].size() < tam_max)
        {
            srand(time(NULL)+rand());
        	int aleatorio = rand() % cromosoma[i].size();

            cromosoma[i].insert(aleatorio,"_");
        }
    }

    aptitud();
}

void individuo::mostrar_ind()
{
    for(int i=0;i<cromosoma.size();i++)
        cout<<cromosoma[i]<<endl;

    cout<<"Aptitud : "<<apt<<endl;
}

#endif // INDIVIDUO_H
