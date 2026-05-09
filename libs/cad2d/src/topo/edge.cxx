/**
* @file edge.cxx
 * @brief Translation unit for topo::Edge.
 *
 * The Edge type is intentionally lightweight and almost entirely inline in the
 * header. This source file exists to give the module a dedicated implementation
 * unit, preserve library structure symmetry, and provide a future home for any
 * non-trivial edge operations should they be introduced later.
 */
#include <tonb/cad2d/topo/edge.hxx>