#include "graph.hpp"

#include<iostream> // temp

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

GraphMatrix Graph::dfs(const GraphMatrix& matrix_graph, GraphMatrix& tree, std::vector<bool>& discovered, unsigned int v)
{
    discovered[v] = true;
    for(int i = 0; i<matrix_graph.rows(); ++i)
    {
        if(matrix_graph(v, i) == 1 && !discovered[i])
        {
            tree(v, i) = 1;
            tree(i, v) = 1;
            dfs(matrix_graph, tree, discovered, i);
        }
    }

    return tree;
}

GraphMatrix Graph::get_spanning_tree(GraphMatrix matrix_graph)
{
    /*
        Algorithme pour obtenir un arbre couvrant
    */

    int n = matrix_graph.rows();
    GraphMatrix tree(n, n);
    tree.fill(0);
    std::vector<bool> discovered(n, false);
    auto[i, j] = find_root_node(matrix_graph);

    return dfs(matrix_graph, tree, discovered, i);
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

GraphMatrix Graph::prune(GraphMatrix matrix_graph)
{
    /*
        On enlève les branches du graphe pour n'y laisser que les sommets
        faisant partie du cycle. On l'élague.
    */

    int n = matrix_graph.rows();

    for(int k = 0; k<n; ++k)
    {
        for(int i = 0; i<n; ++i)
        {
            for(int j = 0; j<n; ++j)
            {
                if(matrix_graph(i, j) == 1 && (matrix_graph.rowwise().sum()(i) == 1 || matrix_graph.colwise().sum()(j) == 1))
                {
                    matrix_graph(i, j) = 0;
                    matrix_graph(j, i) = 0;
                }
            }
        }
    }

    return matrix_graph;
}

std::pair<int, int> Graph::find_root_node(GraphMatrix g)
{
    int n = g.rows();
    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            if(g(i, j))
            {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1); // In case the graph is empty
}

std::vector<GraphMatrix> Graph::orient_cycles(std::vector<GraphMatrix> cycles)
{
    for(auto& c : cycles)
    {
        const int n = c.rows();
        const int m = c.sum()/2;

        auto[i, j] = find_root_node(c);

        int k = 0;
        while(k<m)
        {
            c(i, j) = 0;
            ++k;

            for(int l = (i+1) % n;; l = (l+1) % n)
            {
                if(c(j, l))
                {
                    i = j;
                    j = l;
                    break;
                }
            }
        }
    }

    return cycles;
}

std::vector<GraphMatrix> Graph::get_fundamental_set_of_cycles(GraphMatrix a)
{
    int n = a.rows();
    GraphMatrix b = get_spanning_tree(a);
    GraphMatrix c = a - b;
    GraphMatrix d = b;

    std::vector<GraphMatrix> cycles;

    for(int i = 0; i<n-1; ++i)
    {
        for(int j = i+1; j<n; ++j)
        {
            if(c(i, j) == 1)
            {
                GraphMatrix dk = d;
                dk(i, j) = 1;
                dk(j, i) = 1;
                cycles.push_back(prune(dk));
            }
        }
    }

    return orient_cycles(cycles);
}
