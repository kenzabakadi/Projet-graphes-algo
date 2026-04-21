#include "kruskal.h"
#include <algorithm>
#include <stdexcept>

// Constructeur

Kruskal::Kruskal(Graphe& graphe) : Algorithme(graphe) {}

// Construction et tri des arêtes

std::vector<Kruskal::Arete> Kruskal::construireAretes() const
{
    std::vector<Arete> aretes;

    for (const Arc& a : g.retournerArcs()) {
        int s = a.retournerSommetDepart().retournerId();
        int t = a.retournerSommetArrivee().retournerId();
        if (s < t)
            aretes.push_back({ s, t, static_cast<double>(a.retournerPoids()) });
    }

    return aretes;
}

void Kruskal::trier(std::vector<Arete>& aretes) const
{
    std::sort(aretes.begin(), aretes.end(),
              [](const Arete& a, const Arete& b) {
                  if (a.poids != b.poids) return a.poids < b.poids;
                  int minA = std::min(a.s, a.t), minB = std::min(b.s, b.t);
                  if (minA != minB) return minA < minB;
                  return std::max(a.s, a.t) < std::max(b.s, b.t);
              });
}

// Gestion des composantes connexes

void Kruskal::initialiserComposantes(int n)
{
    m_prem.resize(n + 1);
    m_pilch.resize(n + 1, 0);
    m_cfc.resize(n + 1);
    m_nbElem.resize(n + 1, 1);

    for (int i = 1; i <= n; ++i) {
        m_prem[i] = i;
        m_cfc[i]  = i;
    }
    m_pilch[0] = 0;
}

void Kruskal::fusionner(int i, int j)
{
    if (m_nbElem[j] > m_nbElem[i] ||
        (m_nbElem[j] == m_nbElem[i] && j < i))
    {
        std::swap(i, j);
    }
    int s = m_prem[j];
    m_cfc[s] = i;
    while (m_pilch[s] != 0) {
        s = m_pilch[s];
        m_cfc[s] = i;
    }

    m_pilch[s]  = m_prem[i];
    m_prem[i]   = m_prem[j];
    m_nbElem[i] += m_nbElem[j];
}

// Algorithme de Kruskal

void Kruskal::kruskal(std::vector<Arete>& aretes, int n)
{
    m_arbre.clear();
    m_arbre.reserve(n - 1);

    int i = 0;
    int j = 0;

    while (j < n - 1) {
        if (i >= static_cast<int>(aretes.size()))
            throw std::runtime_error(
                "Kruskal : graphe non connexe, impossible de construire l'arbre couvrant.");

        const Arete& a = aretes[i];
        int x = m_cfc[a.s];
        int y = m_cfc[a.t];

        if (x != y) {
            m_arbre.push_back(a);
            fusionner(x, y);
            ++j;
        }
        ++i;
    }
}

void Kruskal::executer()
{
    int n = static_cast<int>(g.retournerSommets().size());

    if (n < 2)
        throw std::runtime_error("Kruskal : le graphe doit avoir au moins 2 sommets.");

    std::vector<Arete> aretes = construireAretes();

    if (aretes.empty())
        throw std::runtime_error("Kruskal : aucune arête dans le graphe.");

    trier(aretes);
    initialiserComposantes(n);
    kruskal(aretes, n);
}

// Accès aux résultats

const std::vector<Kruskal::Arete>& Kruskal::retournerArbre() const
{
    return m_arbre;
}

int Kruskal::retournerPoidsTotal() const
{
    int total = 0;
    for (const Arete& a : m_arbre)
        total += static_cast<int>(a.poids);
    return total;
}
