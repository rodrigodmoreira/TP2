#include <cmath>
#include "gaav.h"

using namespace std;

/// multiplica um Vetor por um escalar
/// este é um exemplo entregue pronto pra você ;)
Vetor multiplicaPorEscalar(Vetor v, double alpha)
{
    Vetor resultado = Vetor
    (
        v.x * alpha,
        v.y * alpha,
        v.z * alpha,
        v.w * alpha
    );
    return resultado;
}

Vetor somaVetorComVetor(Vetor v, Vetor u)
{
    //TODO: implementar
    Vetor resultado = Vetor
    (
        v.x + u.x,
        v.y + u.y,
        v.z + u.z,
        v.w + u.w
    );
    return resultado;
}

Vetor diferencaVetorComVetor(Vetor v, Vetor u)
{
    //TODO: implementar
    Vetor resultado = Vetor
    (
        v.x - u.x,
        v.y - u.y,
        v.z - u.z,
        v.w - u.w
    );
    return resultado;
}

Vetor diferencaEntrePontos(Ponto p, Ponto q)
{
    //TODO: implementar
    Vetor resultado = Vetor
    (
        p.x-q.x,
        p.y-q.y,
        p.z-q.z,
        p.w-q.w
    );
    return resultado;
}

Ponto somaPontoComVetor(Ponto p, Vetor v)
{
    //TODO: implementar
    Ponto resultado = Ponto
    (
        v.x + p.x,
        v.y + p.y,
        v.z + p.z,
        v.w + p.w
    );
    return resultado;
}

double normaDoVetor(Vetor v)
{
    //TODO: implementar
    double resultado = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return resultado;
}

Vetor normalizado(Vetor v)
{
    //TODO: implementar
    double modulo = normaDoVetor(v);
    Vetor resultado = Vetor
    (
        v.x/modulo,
        v.y/modulo,
        v.z/modulo,
        v.w/modulo
    );
    return resultado;
}

double distanciaEntrePontos(Ponto p, Ponto q)
{
    //TODO: implementar
    Vetor distancia = diferencaEntrePontos(p,q);
    double resultado = normaDoVetor(distancia);
    return resultado;
}

double produtoEscalar(Vetor v, Vetor u)
{
    //TODO: implementar
    double resultado = v.x * u.x + v.y * u.y + v.z * u.z;
    return resultado;
}

Vetor produtoVetorial(Vetor v, Vetor u)
{
    //TODO: implementar
    // Produto Vetorial só faz sentido em 3D
    // Ignorar a componente "w" de "v" e "u"
    // Como o resultado é um Vetor, o "w" dele deve ser 0
    Vetor resultado = Vetor
    (
        v.y*u.z-v.z*u.y,
        v.z*u.x-v.x*u.z,
        v.x*u.y-v.y*u.x,
        0
    );
    return resultado;
}

///
/// Referências: http://localhost:8080/classes/geometry/#30
double anguloEntreVetores(Vetor v, Vetor u)
{
    //TODO: implementar
    double resultado = acos(produtoEscalar(v,u)/(normaDoVetor(v)*normaDoVetor(u)));
    return resultado;
}

///
/// Referências: http://localhost:8080/classes/geometry/#22
Ponto combinacaoAfim2Pontos(Ponto p, Ponto q, double alpha)
{
    //TODO: implementar
    Vetor v = diferencaEntrePontos(p,q);
    Ponto resultado = somaPontoComVetor(q,multiplicaPorEscalar(v,(1-alpha)));
    return resultado;
}

Vetor converterVetorRotacionadoXZ(Vetor v, double theta)
{
    theta *= M_PI/180;
    Vetor resultado = Vetor
    (
        (v.x*cos(theta) - v.z*sin(theta)), 
        v.y, (v.x*sin(theta) + v.z*cos(theta)),
        0
    );
    return resultado;
}
