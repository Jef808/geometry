#include "Types.h"

namespace DG {

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
template<std::size_t N>
class Cluster {
public:


private:

};


} // namespace DG
