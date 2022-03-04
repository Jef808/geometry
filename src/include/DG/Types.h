#ifndef TYPES_H_
#define TYPES_H_

#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Surface_mesh.h"

namespace DG {

    using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
    using FT = Kernel::FT;
    using Point = Kernel::Point_3;

    using Mesh = CGAL::Surface_mesh<Point>;
    using vertex_descriptor = boost::graph_traits<Mesh>::vertex_descriptor;
    using halfedge_descriptor = boost::graph_traits<Mesh>::vertex_descriptor;

} // namespace DG

#endif // TYPES_H_
