// Pour imprimer les composantes d'un vecteur de Double
void printVecteurDouble(double* v , int N)
{
	std::cout<<"\n";
	for (int i=0;i<N;i++)
    {
    	std::cout<<" "<<v[i];
    }
}
// Pour imprimer les composantes d'un vecteur de Integer
void printVecteurInt(int* v , int N)
{
	std::cout<<"\n";
	for (int i=0;i<N;i++)
    {
    	std::cout<<" "<<v[i];
    }
}
// Pour imprimer les composantes d'un vecteur de Bool
void printVecteurBool(bool* v , int N)
{
    std::cout<<"\n";
    for (int i=0;i<N;i++)
    {
        std::cout<<" "<<v[i];
    }
}
// Pour imprimer les composantes d'un vecteur de Bool
void printVecteurBoolJusteLesUn(bool* v , int N)
{
    std::cout<<"\n";
    for (int i=0;i<N;i++)
    {
        if(v[i]==1)
        {
            std::cout<<" "<<v[i];
        }
        else
        {
            std::cout<<"  ";
        }
    }
}
// Pour imprimer les composantes d'une matrice de Double
void printMatriceDouble(double* A , int M, int N)
{
	std::cout<<"\n";
	for (int i=0;i<M;i++)
    {
    	std::cout<<"\n";
    	for (int j=0;j<N;j++)
    	{
    		std::cout<<" "<<A[i+M*j];
    	}
    }
}
// Pour imprimer les composantes d'une matrice d'Integer
void printMatriceInt(int* A , int M, int N)
{
	std::cout<<"\n";
	for (int i=0;i<M;i++)
    {
    	std::cout<<"\n";
    	for (int j=0;j<N;j++)
    	{
    		std::cout<<" "<<A[i+M*j];
    	}
    }
}
// Pour imprimer les composantes d'une matrice de Bool
void printMatriceBool(bool* A , int M, int N)
{
    std::cout<<"\n";
    for (int i=0;i<M;i++)
    {
        std::cout<<"\n";
        for (int j=0;j<N;j++)
        {
            std::cout<<" "<<A[i+M*j];
        }
    }
}
// Pour imprimer juste les 1 d'une matrice de Bool
void printMatriceBoolJusteLesUn(bool* A , int M, int N)
{
    std::cout<<"\n";
    for (int i=0;i<M;i++)
    {
        std::cout<<"\n";
        for (int j=0;j<N;j++)
        {
            if(A[i+M*j]==1)
            {
                std::cout<<" "<<A[i+M*j];   
            }
            else
            {
                std::cout<<"  ";
            }
        }
    }
}
// Pour nombres aléatoires de type Double
double fRand(double fMin, double fMax)
{
    double f = (double)rand()/RAND_MAX;
    return fMin + f*(fMax-fMin);
}
// pour générer un nombre alétoire entre 0 et 1 si la probabilité d'avoir 1 est donnée
bool boolAleatoireSelonProbabiliteEntre0et1(double probabilite)
{
    double nombreAleatoireDouble_temp = fRand(0,1);
    if (nombreAleatoireDouble_temp > probabilite)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int NombreDelementsNonNulsVecteurBool(bool* v, int N)
{
    int k = 0;
    for (int i=0;i<N;i++)
    {
        if (v[i]==1)
        {
            k=k+1;
        }
    }
    return k;
}