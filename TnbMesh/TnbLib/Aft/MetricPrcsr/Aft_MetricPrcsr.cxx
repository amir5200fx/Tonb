#include <Aft_MetricPrcsr.hxx>

#include <Entity2d_Eigen.hxx>

namespace tnbLib
{
	TnbMesh_EXPORT std::shared_ptr<Entity2d_Eigen> mesh2d_aft_metric_prcsr_eigen_calculator =
		std::make_shared<Entity2d_Eigen>();
}