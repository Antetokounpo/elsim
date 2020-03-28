#include "graph.hpp"

#include<vector>

GraphMatrix Graph::get_comatrix(GraphMatrix matrix_graph)
{
    /*
        La matrice complémentaire d'une matrice associé à un graphe s'obtient en
        remplaçant par 1 tous les coefficients 0 et par 0 tous les coefficients 1
    */

    int n = matrix_graph.rows();
    int m = matrix_graph.cols();

    matrix_graph -= Eigen::MatrixXi::Ones(n, m);
    
    return matrix_graph.cwiseAbs();
}

GraphMatrix Graph::get_spanning_tree(GraphMatrix matrix_graph)
{
    GraphMatrix a = matrix_graph;
    int n = a.rows();
    std::vector<int> c (n, 0);
    c[0] = 1;
    GraphMatrix b(n, n);
    b.fill(0);

    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            if(a(i, j) && c[i] && !c[j])
            {
                b(i, j) = 1;
                b(j, i) = 1;
                c[j] = 1;
            }

            if(a(i, j) && !c[i] && c[j])
            {
                b(i, j) = 1;
                b(j, i) = 1;
                c[i] = 1;
            }
        }
    }

    return b;
}

bool Graph::is_graph_antisymmetric(GraphMatrix matrix_graph)
{
    /*
        Pour qu'un graphe soit anti-symétrique, il faut que A <= (A')*, où:
            A' est la matrice complémentaire et
            A* est la matrice transposée.
        Une matrice B est plus grande ou égale à une matrice A si A-B est une
        matrice positive, i.e lorsque tous ses éléments sont des réels positifs.
        Une autre façon de l'écrire est: A-B >= 0.
    */

    GraphMatrix m = get_comatrix(matrix_graph).transpose() - matrix_graph;

    return m == m.cwiseAbs();
}

int Graph::count_cycles(GraphMatrix matrix_graph)
{
    
}