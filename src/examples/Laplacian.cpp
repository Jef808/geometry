/// -*- c++ -*-
///
// We first compute the Laplacian assuming an ideal setting:
// There is no boundary and the surface is orientable.
//
// Q: In this setting, if moreover the change in lenght of edges
// is very slow, is there a big difference between using the cotangent
// weights and simply using
//
//     $\Delta v = \frac{1}{\#N(v)} \sum_{v_j \in N(v)} w_{j} (v - v_j)
//
#include <iostream>
#include <fstream>

#include "DG/Types.h"
#include "CGAL/Polygon_mesh_processing/triangulate_faces.h"
#include "CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h"
#include "CGAL/Weights.h"

#include "CGAL/boost/graph/helpers.h"

using namespace DG;
namespace PMP = CGAL::Polygon_mesh_processing;


/// First step is to compute dot products and
/// cross products of vectors in R^3 to use
///   cotan(\theta) = <u, v> / ||u x v ||
///
/// This will be done in renormalized coordinates, so we start by
/// constructing a class for the 1-ring of a vertex.
///
/// If we assume a lower bound on each angle, we get an upper bound on
/// the size of the 1-rings so we safely template for that and store the
/// localized points in arrays
template<size_t N>
class Cluster {
public:


private:

};




int main(int argc, char *argv[]) {

    const char* mesh_fn = argc > 1 ? argv[1] : "data/meshes/elephant.off";
    Mesh mesh;

    if (not PMP::IO::read_polygon_mesh(mesh_fn, mesh)) {
        std::cerr << "Could not open file: " << mesh_fn << std::endl;
    }

    bool is_triangle = CGAL::is_triangle_mesh(mesh);
    std::cout << "Mesh is " << (is_triangle ? "" : "NOT ") << "a triangle mesh" << std::endl;

    if (not is_triangle)
    {
        PMP::triangulate_faces(mesh);
        is_triangle = CGAL::is_triangle_mesh(mesh);
        std::cout << "After call to triangulate faces:" << std::endl;
        std::cout << "Mesh is " << (is_triangle ? "" : "NOT ") << "a triangle mesh" << std::endl;
    }

    auto pmap = get(CGAL::vertex_point, mesh);
    auto imap = get(CGAL::halfedge_index, mesh);
    mesh.add_property_map<Mesh::Halfedge_index, vertex_descriptor>("weight_map");

    CGAL::Weights::Edge_cotangent_weight weight_computation(mesh, pmap);

    for (auto he : halfedges(mesh)) {

    }

    return 0;
}
